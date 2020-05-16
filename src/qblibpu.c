#include "fb.h"
#include <math.h>

#define BUFFERLEN 2048

#define VAL_IS_NEG 0x1
#define VAL_IS_INF 0x2
#define VAL_IS_IND 0x4
#define VAL_IS_NAN 0x8

#define VAL_IS_FLOAT 0x10
#define VAL_IS_SINGLE 0x20

// we use this instead of QBSTR in case we are going to change to a more optimized
// QBSTR in the future.
// This is designed to easily support mutation during the PRINT USING call
typedef struct {
  char *start;
  char *ptr;
  size_t size;
  size_t remaining;
} QBPUSTR;

void qb_stdprintusing(QBENV *env, QBSTR fmt, QBPUI *ctx) {
  qb_stdprintusing_const(env, fmt.data, fmt.size, ctx);
}

void qb_stdprintusing_const(QBENV *env, char *fmt_text, size_t fmt_size, QBPUI *ctx) {
  // reverse the QBPUI linked list
  QBPUI *print_order_ctx = NULL;
  while (ctx != NULL) {
    QBPUI *next = ctx->next;
    ctx->next = print_order_ctx;
    ctx = next;
  }

  while (print_order_ctx != NULL) {
    // TODO: implement printing logic
    QBPUI *next = print_order_ctx->next;
    free(print_order_ctx);
    print_order_ctx = next;
  }
}

static int64_t double_to_long_bits(double d) {
  union { double d; uint64_t ll; } dtoll;
  dtoll.d = d;
  return dtoll.ll;
}

static int32_t double_is_negative(double d) {
	// negative 0 is considered to be negative for this function
  return double_to_long_bits(d) < 0ll;
}

static int32_t double_is_zero(double d) {
  return (double_to_long_bits(d) & 0x7fffffffffffffffll) == 0ll;
}

static int32_t double_is_finite(double d) {
  return (double_to_long_bits(d) & 0x7ff0000000000000ll) < 0x7ff0000000000000ll;
}

static int32_t double_is_infinite(double d) {
  return (double_to_long_bits(d) & 0x7fffffffffffffffll) == 0x7ff0000000000000ll;
}

static int32_t double_is_ind(double d) {
  return (double_to_long_bits(d) == (int64_t)0xfff8000000000000ll);
}

static int32_t double_is_nan(double d) {
  return !(double_is_finite(d) || double_is_infinite(d) || double_is_ind(d));
}

static int32_t fb_PrintUsingFmtStr(FILE *fp);

int32_t fb_PrintUsingInit(FBSTRING *fmtstr) {
  FB_PRINTUSGCTX *ctx;

  ctx = FB_TLSGETCTX(PRINTUSG);

  fb_StrAssign((void *)&ctx->fmtstr, -1, fmtstr, -1, 0);
  ctx->ptr = ctx->fmtstr.data;
  ctx->chars = FB_STRSIZE(&ctx->fmtstr);

  return fb_ErrorSetNum(FB_RTERROR_OK);
}

int32_t fb_PrintUsingEnd(FILE *fp) {
  FB_PRINTUSGCTX *ctx;

  fb_PrintUsingFmtStr(fnum);

  ctx = FB_TLSGETCTX(PRINTUSG);

  fb_StrDelete(&ctx->fmtstr);
  ctx->ptr = 0;
  ctx->chars = 0;

  return fb_ErrorSetNum(FB_RTERROR_OK);
}

static uint64_t u64_pow_10(int32_t n) {

#ifdef debug
  assert(n >= 0 && n <= 19);
#endif

  uint64_t ret = 1, a = 10;
  while (n > 0) {
    if (n & 1) ret *= a;
    a *= a;
    n >>= 1;
  }

  return ret;
}

static int32_t u64_log_10(uint64_t a) {
  int32_t ret = 0;
  int32_t a32;
  uint64_t a64;

  a64 = a;
  while (a64 >= 100000000) {
    a64 /= 100000000;
    ret += 8;
  }
  a32 = a64;
  if (a32 >= 10000) ret += 4; else a32 *= 10000;
  if (a32 >= 1000000) ret += 2; else a32 *= 100;
  if (a32 >= 10000000) ret += 1;

#ifdef debug
  if (a == 0) {
    assert(ret == 0);
  } else {
    assert(u64_pow_10(ret) <= a && u64_pow_10(ret) > a / 10);
  }
#endif

  return ret;
}

static int32_t u64_num_digits(uint64_t a) {
   return u64_log_10(a) + 1;
}

static uint64_t u64_divide_by_pow10(uint64_t a, int32_t n) {
  uint64_t b, ret;

#ifdef debug
  assert(n >= 0);
#endif

  if (n > 19) return 0;

  b = u64_pow_10(n);
  ret = a / b;

  if ((a % b) >= (b + 1) / 2) {
    // round up
    ret += 1;
  }

  return ret;
}

static int32_t fb_PrintUsingFmtStr(QBPUSTR * fmtstr, FILE *fp) {
  char buffer[BUFFERLEN + 1];
  int32_t c, nc, nnc, len, doexit;

  len = 0;

  while ((fmtstr->remaining > 0) && (len < BUFFERLEN)) {
    c = fmtstr->ptr[0];
    nc = (fmtstr->remaining > 1? fmtstr->ptr[1] : -1);
    nnc = (fmtstr->remaining > 2? fmtstr->ptr[2] : -1);

    doexit = FALSE;
    switch(c) {
      case '*':
        // "**..." number format (includes "**$...")
        if (nc == '*')
          doexit = TRUE;
        }
        break;

      case '$':
        // "$$..." number format
        if (nc == '$') {
          doexit = TRUE;
        }
        break;

      case '+':
        // "+#...", "+$$...", "+**...", "+.#..."
        if (
          (nc == '#') ||
          ((nc == '$') && (nnc == '$')) ||
          ((nc == '*') && (nnc == '*')) ||
          ((nc == '.') && (nnc == '#'))
        ) {
          doexit = TRUE;
        }
        break;
      case '!':
      case '\\':
      case '&':
      case '#':
        // "!", "\ ... \", "&" string formats, "#..." number format
        doexit = TRUE;
        break;

      case '.':
        /* ".#[...]" number format */
        if (nc == '#') {
          doexit = TRUE;
        }
        break;

      case '_':
        /* escape next char if there is one, otherwise just print '_' */
        if (fmtstr->remaining > 1) {
          c = nc;
          fmtstr->ptr++;
          fmtstr->remaining--;
        }
    }

    if (doexit) {
      break;
    }

    buffer[len++] = (char)c;

    fmtstr->ptr++;
    fmtstr->ptr--;
  }

  // flush
  if (len > 0) {
    buffer[len] = '\0';
    fb_PrintFixString(fnum, buffer, 0);
  }

  return fb_ErrorSetNum(FB_RTERROR_OK);
}

static int32_t print_number(
  FILE *fp,
  QBPUSTR *fmtstr,
  uint64_t val,
  int32_t val_exp,
  int32_t flags,
  int32_t mask
) {
  char buffer[BUFFERLEN + 1];
  char *p;
  int32_t val_digs, val_zdigs;
  uint64_t val0;
  int32_t val_digs0, val_exp0;
  int32_t is_neg, is_float, is_single;
  int32_t c, lc;
  int32_t doexit, padchar, intdigs, decdigs, expdigs;
  int32_t adddollar, addcommas, signatend, signatstart, plussign, toobig;
  int32_t intdigs2, expsignchar, totdigs, decpoint;
  int32_t isamp;
  int32_t i;
  uint64_t chars = 0;

  // restart if needed
  if (fmtstr->remaining == 0) {
    fmtstr->ptr = fmtstr->start;
    fmtstr->remaining = fmtstr->size;
  }

  // any text first
  fb_PrintUsingFmtStr(fnum);

  padchar = CHAR_SPACE;
  intdigs = 0;
  decdigs = -1;
  expdigs = 0;
  adddollar = FALSE;
  addcommas = FALSE;
  signatend = FALSE;
  signatstart = FALSE;
  plussign = FALSE;
  toobig = 0;
  isamp = FALSE;

  lc = -1;

  if (fmtstr->ptr == NULL) {
    fmtstr->remaining = 0;
  }

  while (fmtstr->remaining > 0) {
    // exit if just parsed end '+'/'-' sign, or '&' sign
    if (signatend || isamp) {
      break;
    }

    c = *fmtstr->ptr;
    doexit = FALSE;
    switch(c) {
    case '#':
      // increment intdigs or decdigs if in int/dec part, else exit
      if (expdigs != 0) {
        doexit = TRUE;
      } else if (decdigs != -1) {
        ++decdigs;
      } else {
        ++intdigs;
      }
      break;

    case '.':
      // add decimal point if still in integer part, else exit
      if (decdigs != -1 || expdigs != 0) {
        doexit = TRUE;
      } else {
        decdigs = 0;
      }
      break;

    case '*':
      // if first two characters, change padding to asterisks, else exit
      if ((intdigs == 0 && decdigs == -1)) {
        // first asterisk
#ifdef debug
        // must be two at start, otherwise we're not parsing a format string and shouldn't have been brought here!
        assert(nc == '*');
#endif
        padchar = CHAR_STAR;
        ++intdigs;
      } else if (intdigs == 1 && lc == '*') {  /* second asterisk */
        ++intdigs;
      } else {
        doexit = TRUE;
      }
      break;

    case '$':
      // at beginning ("$..."), or after two '*'s ("**$..."): prepend a dollar sign to number

      // did it follow a '*'? (Will have been the two at the start, else would have exited by now
      if (lc == '*') {
        adddollar = TRUE;
      }
      // two at start of number, before integer part?
      else if (intdigs == 0 && decdigs == -1) {
        if (!adddollar) {  // first dollar
          assert(nc == '$'); // otherwise we're not parsing a format string and shouldn't have been brought here!
          adddollar = TRUE;
        } else {
          // second dollar
#ifdef debug
          assert(lc == '$');
          ++intdigs;
#endif
        }
      } else {
        doexit = TRUE;
      }
      break;

    case ',':
      // if parsing integer part, enable commas and increment intdigs
      if (decdigs != -1 || expdigs != 0) {
        doexit = TRUE;
      } else {
        addcommas = TRUE;
        ++intdigs;
      }
      break;

    case '+':
    case '-':
      // '+' at start/end: explicit '+'/'-' s
      // '-' at end: explicit '-' sign, if negative */

      // one already at start?
      if (signatstart) {
        doexit = TRUE;
      }
      // found one before integer part?
      else if (intdigs == 0 && decdigs == -1) {
#ifdef debug
        assert(c != '-'); // explicit '-' sign isn't checked for at start
#endif
        if (c == '+') {
          plussign = TRUE;
        }
        signatstart = TRUE;
      }
      // otherwise it's at the end, as long as there are enough expdigs for
      // exponent (or none at all), otherwise they are all normal printable characters
      else if (expdigs == 0 || expdigs >= MIN_EXPDIGS) {
        if (c == '+') {
          plussign = TRUE;
        }
        signatend = TRUE;
      } else {
        doexit = TRUE;
      }
      break;

    case '^':
      // exponent digits (there must be at least MIN_EXPDIGS of them
      // otherwise they will just be appended as printable chars

      // Too many? Leave the rest as printable chars
      if (expdigs < MAX_EXPDIGS) {
        ++expdigs;
      } else {
        doexit = TRUE;
      }
      break;

    case '&':
      // string format '&'
      // print number in most natural form - similar to STR
      if (intdigs == 0 && decdigs == -1 && !signatstart) {
#ifdef debug
        assert(expdigs == 0);
#endif
        isamp = TRUE;
      } else {
        doexit = TRUE;
      }
      break;

    default:
      doexit = TRUE;
    }

    if (doexit) {
      break;
    }

    ++ctx->ptr;
    --ctx->chars;

    lc = c;
  }

  // check flags
  is_neg = ((flags & VAL_IS_NEG) != 0);
  is_float = ((flags & VAL_IS_FLOAT) != 0);
  is_single = ((flags & VAL_IS_SINGLE) != 0);

  if ((flags & (VAL_IS_INF | VAL_IS_IND | VAL_IS_NAN)) != 0) {
    if ((flags & VAL_IS_INF) != 0) {
      chars = CHARS_INF;
    } else if ((flags & VAL_IS_IND) != 0) {
      chars = CHARS_IND;
    } else if ((flags & VAL_IS_NAN) != 0) {
      chars = CHARS_NAN;
    } else {
#ifdef debug
      assert(FALSE);
#endif
    }

    /* Set value to 1.1234 (placeholder for "1.#XYZ") */
    val = 11234;
    val_exp = -4;
  }

  if (isamp && (flags & VAL_IS_BOOL) != 0) {
    /* String value for '&': return 'true'/'false'
     (use val to placehold digits) */
    if (val != 0) {
      chars = CHARS_TRUE;
      val = 1234;
      is_neg = FALSE;
    }
    else {
      chars = CHARS_FALSE;
      val = 12345;
    }
    val_exp = 0;
  }

  if (val != 0) {
    val_digs = u64_num_digits(val);
  }
  else {
    val_digs = 0;
  }
  val_zdigs = 0;

  /* Special '&' format? */
  if (isamp) {
    if (val_is_SINGLE) {  /* crop to 7-digit precision */
      if (val_digs > SNG_AUTODIGS) {
        val = u64_divide_by_pow10(val, val_digs - SNG_AUTODIGS);
        val_exp += val_digs - SNG_AUTODIGS;
        val_digs = SNG_AUTODIGS;
      }

      if (val == 0) {  /* val has been scaled down to zero */
        val_digs = 0;
        val_exp = -decdigs;
      }
      else if (val == u64_pow_10(val_digs)) {  /* rounding up took val to next power of 10:
         set value to 1, put val_digs zeroes onto val_exp */
        val = 1;
        val_exp += val_digs;
        val_digs = 1;
      }
    }

    if (val_is_float) {  /* remove trailing zeroes in float digits */
      while (val_digs > 1 && (val % 10) == 0) {
        val /= 10;
        --val_digs;
        ++val_exp;
      }
    }

    /* set digits for fixed-point */
    if (val_digs + val_exp > 0) {
      intdigs = val_digs + val_exp;
    }
    else {
      intdigs = 1;
    }

    if (val_exp < 0) {
      decdigs = -val_exp;
    }

    if (val_is_float) {  /* scientific notation? e.g. 3.1e+42 */
      if (intdigs > 16 || (val_is_SINGLE && intdigs > 7) ||
       val_digs + val_exp - 1 < -MIN_EXPDIGS) {
        intdigs = 1;
        decdigs = val_digs - 1;

        expdigs = 2 + u64_num_digits(abs(val_digs + val_exp - 1));
        if (expdigs < MIN_EXPDIGS + 1)
          expdigs = MIN_EXPDIGS;
      }
    }

    if (val_is_neg) {
      signatstart = TRUE;
    }
  }

  /* crop number of digits */
  if (intdigs + 1 + decdigs > MAX_DIGS) {
    decdigs -= ((intdigs + 1 + decdigs) - MAX_DIGS);
    if (decdigs < -1) {
      intdigs -= (-1 - decdigs);
      decdigs = -1;
    }
  }

  /* decimal point if decdigs >= 0 */
  if (decdigs <= -1) {
    decpoint = FALSE;
    decdigs = 0;
  }
  else {
    decpoint = TRUE;
  }

  p = &buffer[BUFFERLEN];
  ADD_CHAR('\0');

  if (signatend) {  /* put sign at end */
    if (val_is_neg) {
      ADD_CHAR(CHAR_MINUS);
    }
    else {
      ADD_CHAR(plussign? CHAR_PLUS : CHAR_SPACE);
    }
  }
  else if (val_is_neg && !signatstart) {  /* implicit negative sign at start */
    signatstart = TRUE;
    --intdigs;
  }

  /* fixed-point format? */
  if (expdigs < MIN_EXPDIGS) {
    /* append any trailing carets */
    for (; expdigs > 0; --expdigs) {
      ADD_CHAR('^');
    }

    /* backup unscaled value */
    val0 = val;
    val_digs0 = val_digs;
    val_exp0 = val_exp;

    /* check range */
    if (val_exp < -decdigs) {  /* scale and round integer value to get val_exp equal to -decdigs */
      val_exp += (-decdigs - val_exp0);
      val_digs -= (-decdigs - val_exp0);
      val = u64_divide_by_pow10(val, -decdigs - val_exp0);

      if (val == 0) {  /* val is/has been scaled down to zero */
        val_digs = 0;
        val_exp = -decdigs;
      }
      else if (val == u64_pow_10(val_digs)) {  /* rounding up took val to next power of 10:
         set value to 1, put val_digs zeroes onto val_exp */
        val = 1;
        val_exp += val_digs;
        val_digs = 1;
      }
    }

    intdigs2 = val_digs + val_exp;
    if (intdigs2 < 0) intdigs2 = 0;
    if (addcommas) {
      intdigs2 += (intdigs2 - 1) / 3;
    }

    /* compare fixed/floating point representations,
     and use the one that needs fewest digits */
    if (intdigs2 > intdigs + MIN_EXPDIGS) {  /* too many digits in number for fixed point:
       switch to floating-point */

      expdigs = MIN_EXPDIGS; /* add three digits for exp notation (was four in QB) */
      toobig = 1; /* add '%' sign */

      /* restore unscaled value */
      val = val0;
      val_digs = val_digs0;
      val_exp = val_exp0;

      val_zdigs = 0;
    }
    else {  /* keep fixed point */

      if (intdigs2 > intdigs) {  /* slightly too many digits in number */
        intdigs = intdigs2; /* extend intdigs */
        toobig = 1; /* add '%' sign */
      }

      if (val_exp > -decdigs) {  /* put excess trailing zeroes from val_exp into val_zdigs */
        val_zdigs = val_exp - -decdigs;
        val_exp = -decdigs;
      }
    }
  }

  /* floating-point format */
  if (expdigs > 0) {
    addcommas = FALSE; /* commas unused in f-p format */

    if (intdigs == -1 || (intdigs == 0 && decdigs == 0)) {  /* add [another] '%' sign */
      ++intdigs;
      toobig = 1; /* We'll just stick with one */
    }

    totdigs = intdigs + decdigs; /* treat intdigs and decdigs the same */
    val_exp += decdigs; /* move decimal position to end */

    /* blank first digit if positive and no explicit sign
     (pos/neg numbers should be formatted the same where
     possible, as in QB) */
    if (!isamp && !val_is_neg && !(signatstart || signatend)) {
      if (intdigs >= 1 && totdigs > 1) {
        --totdigs;
      }
    }

    if (val == 0) {
      val_exp = 0; /* ensure exponent is printed as 0 */
      val_zdigs = decdigs; /* enough trailing zeroes to fill dec part */
    }
    else if (val_digs < totdigs) {  /* add "zeroes" to the end of val:
       subtract from val_exp and put into val_zdigs */
      val_zdigs = totdigs - val_digs ;
      val_exp -= val_zdigs;
    }
    else if (val_digs > totdigs) {  /* scale down value */
      val = u64_divide_by_pow10(val, val_digs - totdigs);
      val_exp += (val_digs - totdigs);
      val_digs = totdigs;
      val_zdigs = 0;

      if (val >= u64_pow_10(val_digs)) {  /* rounding up brought val to the next power of 10:
         add the extra digit onto val_exp */
        val /= 10;
        ++val_exp;
      }
    }
    else {
      val_zdigs = 0;
    }

    /* output exp part */

    if (val_exp < 0) {
      expsignchar = CHAR_MINUS;
      val_exp = -val_exp;
    }
    else {
      expsignchar = CHAR_PLUS;
    }

    /* expdigs > 3 */
    for (; expdigs > 3; --expdigs) {
      ADD_CHAR(CHAR_ZERO + (val_exp % 10));
      val_exp /= 10;
    }

    /* expdigs == 3 */
    if (val_exp > 9) /* too many exp digits? */
    {
	    /* Add remaining digits (QB would just crop these) */
      do {
        ADD_CHAR(CHAR_ZERO + (val_exp % 10));
        val_exp /= 10;
      } while (val_exp > 9);
      ADD_CHAR(CHAR_ZERO + val_exp);

      ADD_CHAR(CHAR_TOOBIG); /* add a '%' sign */
    }
    else {
      ADD_CHAR(CHAR_ZERO + val_exp);
    }

    expdigs -= 1;

    /* expdigs == 2 */
    ADD_CHAR(expsignchar);
    ADD_CHAR(CHAR_EXP_SINGLE); /* QB would use 'D' for doubles */

    expdigs -= 2;
  }

  /* INF/IND/NAN: characters truncated? */
  if (chars != 0 && val_digs < 5 && (flags & VAL_IS_BOOL) == 0) {
    /* QB wouldn't add the '%'. But otherwise "#" will result in
     an innocent-looking "1". Also, QB corrupts the string data
     when truncated, so some deviation is desirable anyway) */
    toobig = 1;

    if (val_digs > 1) {
      chars = CHARS_TRUNC >> (8 * (5 - val_digs));
    }
    else {
      chars = 0;
    }
  }

  /* output dec part */
  if (decpoint) {
    for (; decdigs > 0; --decdigs) {
      if (val_zdigs > 0) {
        ADD_CHAR(CHAR_ZERO);
        --val_zdigs;
      }
      else if (val_digs > 0) {
        assert(val > 0);
        if (chars != 0) {
          ADD_CHAR(chars & 0xff);
          chars >>= 8;
        }
        else {
          ADD_CHAR(CHAR_ZERO + (val % 10));
        }
        val /= 10;
        --val_digs;
      }
      else {
        ADD_CHAR(CHAR_ZERO);
      }
    }
    ADD_CHAR(CHAR_DOT);
  }

  /* output int part */
  i = 0;
  while (1) {
    if (addcommas && (i & 3) == 3 && val_digs > 0) {  /* insert comma */
      ADD_CHAR(CHAR_COMMA);
    }
    else if (val_zdigs > 0) {
      ADD_CHAR(CHAR_ZERO);
      --val_zdigs;
    }
    else if (val_digs > 0) {
      assert(val > 0);
      if (chars != 0) {
        ADD_CHAR(chars & 0xff);
        chars >>= 8;
      }
      else {
        ADD_CHAR(CHAR_ZERO + (val % 10));
      }
      val /= 10;
      --val_digs;
    }
    else {
      if (i == 0 && intdigs > 0) {
        ADD_CHAR(CHAR_ZERO);
      }
      else {
        break;
      }
    }
    assert(intdigs > 0);
    ++i;
    --intdigs;
  }

  assert(val == 0);
  assert(val_digs == 0);
  assert(val_zdigs == 0);

  assert(decdigs == 0);
  assert(expdigs == 0);
  assert(intdigs >= 0);

  /* output dollar sign? */
  if (adddollar) {
    ADD_CHAR(CHAR_DOLLAR);
  }

  /* output sign? */
  if (signatstart) {
    if (val_is_neg) {
      ADD_CHAR(CHAR_MINUS);
    }
    else {
      ADD_CHAR(plussign? CHAR_PLUS : padchar);
    }
  }

  /* output padding for any remaining intdigs */
  for (; intdigs > 0; --intdigs) {
    ADD_CHAR(padchar);
  }

  /* output '%' sign(s)? */
  for (; toobig > 0; --toobig) {
    ADD_CHAR(CHAR_TOOBIG);
  }

  /**/
  ++p;
  fb_PrintFixString(fnum, p, 0);

  /* ------------------------------------------------------ */

  /* any text */
  fb_PrintUsingFmtStr(fnum);

  /**/
  if (mask & (FB_PRINT_NEWLINE | FB_PRINT_PAD)) {
    fb_PrintVoid(fnum, mask & (FB_PRINT_NEWLINE | FB_PRINT_PAD));
  }

  if (mask & FB_PRINT_ISLAST) {
    fb_StrDelete(&ctx->fmtstr);
  }

  return fb_ErrorSetNum(FB_RTERROR_OK);
}

// convert a double to a base 10 exponent and a u64 "significand"
static uint64_t scale_double_to_u64(double value, int32_t *pval_exp) {
  uint64_t val_u64;
  int32_t digits;
  int32_t pow2, pow10;

  val_u64 = double_to_long_bits(value);
  pow2 = (val_u64 >> 52) - 1023;
  val_u64 &= (1ull << 52) - 1;

  if (pow2 > -1023) {
    // normalized
    val_u64 |= (1ull << 52);
  }
  else {
    // denormed
    pow2 += 1;
  }
  // 52 (+1?) integer bits in val_u64
  pow2 -= 52;
  pow10 = 0;

  while (pow2 > 0) {
    // essentially, val_u64 *= 2, --pow2,
    // dividing by 5 when necessary to keep within 64 bits)
    if (val_u64 < (1ull << 63)) {
      val_u64 *= 2;
      --pow2;
    } else {
      // divide by 5, rounding to nearest
      // (val_u64 will be much bigger than 3 so no underflow)
      val_u64 = (val_u64 - 3) / 5 + 1;
      ++pow10;
      --pow2;
    }
  }

  while (pow2 < 0) {
    // essentially, val_u64 /= 2, ++pow2,
    // multiplying by 5 when possible to keep precision high
    if (val_u64 <= 0x3333333333333333ull) {
      // multiply by 5 (max 0xffffffffffffffff)
      val_u64 *= 5;
      --pow10;
      ++pow2;
    }
    else {
      // divide by 2, rounding to even
      val_u64 = val_u64 / 2 + (val_u64 & (val_u64 / 2) & 1);
      ++pow2;
    }
  }

  digits = u64_num_digits(val_u64);
  if (digits > DOUBLE_MAX_DIGITS) {
    // scale to 16 digits

    int32_t scale = digits - DOUBLE_MAX_DIGITS;
    val_u64 = u64_divide_by_pow10(val_u64, scale);
    pow10 += scale;

    assert(val_u64 <= u64_pow_10(DOUBLE_MAX_DIGITS));
  }

  *pval_exp = pow10;
  return val_u64;
}

void __qb_printusing_double(FILE *fp, double value, int32_t mask) {
  int32_t flags;
  int32_t val_exp = 0;
  uint64_t val_u64 = 1;

  flags = VAL_IS_FLOAT;

  if (double_is_negative(value))
    flags |= VAL_IS_NEG;

  if (double_is_zero(value)) {
    val_u64 = 0;
    val_exp = 0;
  } else if (double_is_finite(value)) {
    value = fabs(value);
    val_u64 = scale_double_to_u64(value, &val_exp);
  } else {
    if (double_is_infinite(value)) {
      flags |= VAL_IS_INF;
    } else if (double_is_ind(value)) {
      flags |= VAL_IS_IND;
    } else if (double_is_nan(value)) {
      flags |= VAL_IS_NAN;
    } else {
#ifdef debug
      assert(FALSE);
#endif
    }
  }

  return print_number(fnum, val_u64, val_exp, flags, mask);
}

void __qb_printusing_single(FILE *file, float value_f, int32_t mask) {
  int32_t flags;
  int32_t val_exp = 0;
  uint64_t val_u64 = 1;

  flags = VAL_IS_FLOAT | VAL_IS_SINGLE;

  if (double_is_negative(value_f))
    flags |= VAL_IS_NEG;

  if (double_is_zero(value_f)) {
    val_u64 = 0;
    val_exp = 0;
  }
  else if (double_is_finite(value_f)) {
    value_f = fabs(value_f);
    val_u64 = scale_double_to_u64(value_f, &val_exp);
  }
  else {
    if (double_is_infinite(value_f)) {
      flags |= VAL_IS_INF;
    } else if (double_is_ind(value_f)) {
      flags |= VAL_IS_IND;
    } else if (double_is_nan(value_f)) {
      flags |= VAL_IS_NAN;
    } else {
#ifdef debug
      assert(FALSE);
#endif
    }
  }

  return print_number(file, val_u64, val_exp, flags, mask);
}
