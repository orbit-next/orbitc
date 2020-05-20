#include "../include/qb.h"
#include <math.h>
#include <assert.h>

#define BUFFERLEN 2048

#define VAL_IS_NEG 0x1
#define VAL_IS_INF 0x2
#define VAL_IS_IND 0x4
#define VAL_IS_NAN 0x8

#define VAL_IS_FLOAT 0x10
#define VAL_IS_SINGLE 0x20

struct decimal {
  uint64_t digits;
  int32_t exponent;
  int32_t flags;
};

#define DOUBLE_MAX_DIGITS 16

// these are arbitrary limits, subject to change
#define MAX_FMT 1024
#define MAX_OUT 2048

static int32_t i32_pow_10(int32_t n) {

#ifdef debug
  assert(n >= 0 && n <= 9);
#endif

  int32_t ret = 1, a = 10;
  while (n > 0) {
    if (n & 1) ret *= a;
    a *= a;
    n >>= 1;
  }

  return ret;
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

static struct decimal scale_decimal_to_fill(struct decimal num) {
  if (num.digits == 0) {
    num.digits = 0;
    num.exponent = 0;
    return num;
  }

  int32_t num_digits = u64_num_digits(num.digits);
  if (num_digits > 19) {
    int32_t digit_diff = num_digits - 19;
    num.digits = u64_divide_by_pow10(num.digits, digit_diff);
    num.exponent += digit_diff;
  } else if (num_digits < 19) {
    int32_t digit_diff = 19 - num_digits;
    num.digits *= u64_pow_10(digit_diff);
    num.exponent -= digit_diff;
  }

  return num;
}

// a scaled number always has 19 digits
#define DIGIT_LENGTH 19
#define LARGEST_RELATIVE_EXPONENT (DIGIT_LENGTH - 1)

static size_t print_number(
  char *restrict buf,
  size_t maxlen,
  struct decimal num,
  int32_t before_dot,
  int32_t after_dot,
  int32_t exponent_length
) {
  assert(
    (before_dot >= 1 && before_dot <= DIGIT_LENGTH) &&
    (after_dot >= 0 && after_dot <= (DIGIT_LENGTH - 1)) &&
    (exponent_length == 0 || (exponent_length >= (2 + 1) && exponent_length <= (2 + 3)))
  );
  assert(before_dot + after_dot <= DIGIT_LENGTH);
  int32_t total_length = before_dot + (after_dot > 0 ? after_dot + 1 : 0) + exponent_length;
  assert(total_length <= maxlen);
  // if using exponential notation, 2 digits are necessary for the sign and
  // at least one digit before the decimal point
  assert(exponent_length == 0 || before_dot >= 2);

  // handle non-finite values
  // Note that the output for non-finite values is different from QB
  int32_t flags = num.flags;
  if (flags & VAL_IS_NAN) {
    assert(maxlen >= 4);
    memcpy(buf, "#nan", 4);
    return 4;
  } else if (flags & VAL_IS_IND) {
    assert(maxlen >= 4);
    memcpy(buf, "#ind", 4);
    return 4;
  } else if (flags & VAL_IS_INF) {
    assert(maxlen >= 5);
    if (flags & VAL_IS_NEG) {
      memcpy(buf, "#-inf", 5);
    } else {
      memcpy(buf, "#+inf", 5);
    }
    return 5;
  }

  size_t outlen = 0;
  struct decimal scaled_val = scale_decimal_to_fill(num);
  int32_t display_overflow = FALSE;
  uint64_t val_digits = scaled_val.digits;
  int32_t val_exponent = scaled_val.exponent;
  int32_t is_negative = scaled_val.flags & VAL_IS_NEG;

  // the characters of the digits
  char digit_buf[DIGIT_LENGTH];
  int32_t digit_buf_pos = DIGIT_LENGTH - 1;
  uint64_t digits_temp = val_digits;
  for (int32_t i = 0; i < DIGIT_LENGTH; i++) {
    digit_buf[i] = '0' + digits_temp % 10;
    digits_temp /= 10;
  }

  if (exponent_length) {
    // handle exponential notation

    // find the maximum displayable |exponent| with the number of
    // exponent digits available
    int32_t max_abs_exponent = i32_pow_10(exponent_length - 2) - 1;
    // this is the exponent to be displayed in the printed number
    // if there are extra more than 2 digits before the decimal point, the exponent is decreased
    // example: using format '##.##^^^^' to print 3.33333 results in ' 3.33E+00'
    //          using format '###.##^^^^' to print 3.33333 results in ' 33.33E-01'
    // the number 0 (regardless of sign) is treated as having an exponent of 0
    int32_t display_exponent = val_digits == 0
      ? 0
      :val_exponent + LARGEST_RELATIVE_EXPONENT - (before_dot - 2);

    // find if display_exponent fits
    if (display_exponent > max_abs_exponent || -display_exponent > max_abs_exponent) {
      display_overflow = TRUE;
    } else {
      // print the digits

      // the characters of the exponents, 3 characters is always enough
      // for an IEEE 754 double, even after moving the decimal point
      char exponent_buf[3];
      int32_t exponent_buf_pos = (exponent_length - 2) - 1;
      int32_t abs_display_exponent_temp = display_exponent < 0 ? -display_exponent : display_exponent;
      for (int32_t i = 0; i < 3; i++) {
        exponent_buf[i] = '0' + abs_display_exponent_temp % 10;
        abs_display_exponent_temp /= 10;
      }
      // print the number, starting with the sign
      int32_t integer_part_length = val_digits == 0 ? 1 : before_dot - 1;
      // extra spacing may be needed to print the number 0
      if (val_digits == 0) {
        for (int32_t i = 0; i < before_dot - 2; i++) {
          buf[outlen++] = ' ';
        }
      }
      buf[outlen++] = is_negative ? '-' : ' ';
      for (int32_t i = 0; i < integer_part_length; i++) {
        buf[outlen++] = digit_buf[digit_buf_pos--];
      }
      if (after_dot) {
        buf[outlen++] = '.';
        for (int32_t i = 0; i < after_dot; i++) {
          buf[outlen++] = digit_buf[digit_buf_pos--];
        }
      }
      buf[outlen++] = 'E';
      buf[outlen++] = display_exponent < 0 ? '-' : '+';
      for (int32_t i = 2; i < exponent_length; i++) {
        buf[outlen++] = exponent_buf[exponent_buf_pos--];
      }
    }
  } else {
    // handle non exponential notation

    // the integer part has at least one digit (possibly the single digit 0)
    // this also applies to the number 0
    int32_t integer_part_length = val_digits == 0 ? 1 : val_exponent + DIGIT_LENGTH;
    integer_part_length = integer_part_length < 1 ? 1 : integer_part_length;
    int32_t displayable_digit_length = is_negative ? before_dot - 1 : before_dot;

    if (integer_part_length > displayable_digit_length) {
      display_overflow = TRUE;
    } else {
      // the 3 parts printed below should always add up to `before_dot` characters
      int32_t leading_space_length = before_dot - (is_negative ? integer_part_length + 1 : integer_part_length);
      // the exponent of the most significant digit, this value is meaningless when the number is 0
      int32_t most_significant_exponent = val_exponent + LARGEST_RELATIVE_EXPONENT;

      // print leading spaces, if any
      for (int32_t i = 0; i < leading_space_length; i++) {
        buf[outlen++] = ' ';
      }
      // print the negative sign, if any
      if (is_negative) {
        buf[outlen++] = '-';
      }
      if (val_digits != 0 && most_significant_exponent >= 0) {
        for (int32_t i = 0; i < integer_part_length; i++) {
          buf[outlen++] = digit_buf[digit_buf_pos--];
        }
      } else {
        // here, the unclamped `integer_part_length` must have been < 1, or the number itself is 0
        buf[outlen++] = '0';
      }

      if (after_dot) {
        buf[outlen++] = '.';
        for (int32_t i = 0; i < after_dot; i++) {
          int32_t current_exponent = -i - 1;
          if (val_digits != 0 && current_exponent <= most_significant_exponent) {
            buf[outlen++] = digit_buf[digit_buf_pos--];
          } else {
            buf[outlen++] = '0';
          }
        }
      }
    }
  }

  if (display_overflow) {
    for (int32_t i = 0; i < before_dot; i++, buf[outlen++] = '#');
    if (after_dot) {
      buf[outlen++] = '.';
      for (int32_t i = 0; i < after_dot; i++, buf[outlen++] = '#');
    }
    for (int32_t i = 0; i < exponent_length; i++, buf[outlen++] = '^');
  }

  return outlen;
/*
  int32_t val_exponent = scaled_val.exponnent;
  int32_t val_highest_exponent = val_exponent + 18; // the exponent of the most significant digit of the value
  // check that the magnitude of the number is displayable. if not output in the format of '###.###'
  int32_t val_integer_digits = val_highest_exponent + 1;
  int32_t integer_digit_overflow = ((flags & VAL_IS_NEG) ? 1 : 0) + val_integer_digits > before_dot;
  // for exponential notation, the first digit is always left blank if the number is positive
  int32_t exponent_overflow = FALSE;
  int32_t display_exponent = 0;
  if (exponent_length > 0) {
    // the maximum allowable |exponent| with the number of exponent digits available
    int32_t max_abs_exponent = i32_pow_10(exponent_length - 2) - 1;
    display_exponent = val_highest_exponent - (before_dot - 1);
    if (display_exponent > max_abs_exponent || -display_exponent > max_abs_exponent) {
      exponent_overflow = TRUE;
    }
  }
  // if the digits overflow print this generic representation instead
  // this is different from QB
  if (integer_digit_overflow || exponent_overflow) {
    for (int32_t i = 0; i < before_dot; i++, buf[outlen++] = '#');
    if (after_dot > 0) {
      buf[outlen++] = '.';
      for (int32_t i = 0; i < after_dot; i++, buf[outlen++] = '#');
    }
    for (int32_t i = 0; i < exponent_length; i++, buf[outlen++] = '^');
    return outlen;
  }

  // the digits of the number to be printed (after scaling, it is always a 19 digit number)
  char digit_buf[19];
  uint64_t digits_temp = scaled_val.digits;
  for (int32_t i = 0; i < 19; i++) {
    digit_buf[i] = '0' + digits_temp % 10;
    digits_temp /= 10;
  }

  if (val_integer_digits > 0) {
    for (int32_t i = val_integer_digits; i < before_dot; i++) {
      int32_t current_exponent = before_dot - i - 1;
      int32_t digit_index = current_exponent - val_exponent;

#ifdef debug
      assert(digit_index >= 0); // overflow is supposed to be handled above
#endif

      buf[outlen++] = digit_index < 19
        ? digit_buf[digit_index]
        : ' ';
    }
  } else {
    for (int32_t i = 0; i < before_dot - 1; i++, buf[outlen++] = ' ');
    buf[outlen++] = '0'
  }
  if (after_dot > 0) {
    buf[outlen++] = '.';
    for (int32_t i = 0; i < after_dot; i++) {
      int32_t current_exponent = -i - 1;
      int32_t digit_index = current_exponent - val_exponent;
      buf[outlen++] = (digit_index >= 0 && digit_index < 19)
        ? digit_buf[digit_index]
        : '0';
    }
  }

  // the decimal digits of the exponent. 3 digits is always enough for a IEEE 754 double
  char exponent_buf[3];
  int32_t display_exponent_temp = display_exponent;
  for (int32_t i = 0; i < 3; i++) {
    exponent_buf[i] = '0' + display_exponent_temp % 10;
    display_exponent_temp /= 10;
  }
  buf[outlen++] = 'E';
  buf[outlen++] = display_exponent > 0 ? '+' : '-';
  for (int i = 0; i < exponent_length - 2; i++) {
    int32_t digit_index = (exponent_length - 2) - 1 - i;
    buf[outlen++] = exponent_buf[digit_index];
  }

  return outlen; */
}

static size_t print_formatted_number(char *restrict scratch, char *restrict fmt, size_t fmt_size, struct decimal num) {
  int32_t escaped = FALSE; // whether this character is to be escaped because of a preceding '_'
  int32_t after_digit = FALSE; // whether the previous character was a '#' that was part of a number
  int32_t after_dot = FALSE; // whether the previous character was a '.' that was part of a number
  int32_t fractional = FALSE; // whether we are currently parsing the part of the format string after the decimal point
  int32_t in_number = FALSE; // whether we are currently parsing a number
  int32_t after_number = FALSE; // whether a number has already been parsed in the format string
  int32_t skip = FALSE; // whether to skip the current character when printing
  int32_t exponent_length = 0; // the length of the exponent part, 0 is no exponent, otherwise 4 is the minimum
  int32_t before_dot_digits = 0; // the number of digits before the decimal point
  int32_t after_dot_digits = 0; // tre number of digits after the decimal point
  assert(fmt_size < MAX_FMT);

  size_t outlen = 0;

  for (size_t i = 0; i < fmt_size; i++) {
    if (!in_number && !after_number) {
      if (fmt[i] == '#') {
        in_number = TRUE;
      }
    }
    if (in_number) {
      if (fmt[i] == '#') {
        if (after_dot) {
          fractional = TRUE;
        }
        after_dot = FALSE;
        after_digit = TRUE;
        if (fractional) {
          after_dot_digits++;
        } else {
          before_dot_digits++;
        }
      } else {
        if (fmt[i] == '.') {
          if (after_digit && !fractional && i + 1 < fmt_size && fmt[i + 1] == '#') {
            after_dot = TRUE;
          } else {
            in_number = FALSE;
            after_number = TRUE;
            outlen += print_number(scratch + outlen, MAX_OUT - outlen, num, before_dot_digits, after_dot_digits, exponent_length);
          }
        } else {
          if (fmt[i] == '^') {
            // 3 or more '^'s in a row means exponential
            int32_t j;
            for (j = 1; i + j < fmt_size && fmt[i + j] == '^'; j++);
            if (j >= 3) {
              exponent_length = j;
              i += j - 1;
              skip = TRUE; // we need to skip the last '^' when printing
            }
            in_number = FALSE;
            after_number = TRUE;
            outlen += print_number(scratch + outlen, MAX_OUT - outlen, num, before_dot_digits, after_dot_digits, exponent_length);
          } else {
            in_number = FALSE;
            after_number = TRUE;
            outlen += print_number(scratch + outlen, MAX_OUT - outlen, num, before_dot_digits, after_dot_digits, exponent_length);
          }
          after_dot = FALSE;
        }
        after_digit = FALSE;
      }
    }
    if (!in_number) {
      if (skip) {
        skip = FALSE;
      } else if (escaped) {
        escaped = FALSE;
        assert(outlen < MAX_OUT);
        scratch[outlen++] = fmt[i];
      } else if (fmt[i] == '_') {
        escaped = TRUE;
      } else {
        assert(outlen < MAX_OUT);
        scratch[outlen++] = fmt[i];
      }
    }
  }
  if (in_number) {
    // hasn't "flushed" a number
    outlen += print_number(scratch, MAX_OUT - outlen, num, before_dot_digits, after_dot_digits, exponent_length);
  }

  return outlen;
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

struct decimal double_to_decimal(double value) {
  int32_t flags;
  int32_t val_exp = 0;
  uint64_t val_u64 = 1;

  flags = VAL_IS_FLOAT;

  if (double_is_negative(value)) flags |= VAL_IS_NEG;

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
      assert(FALSE);
    }
  }

  struct decimal ret;
  ret.digits = val_u64;
  ret.exponent = val_exp;
  ret.flags = flags;
  return ret;
}

struct decimal single_to_decimal(float value_f) {
  int32_t flags;
  int32_t val_exp = 0;
  uint64_t val_u64 = 1;

  flags = VAL_IS_FLOAT | VAL_IS_SINGLE;

  if (double_is_negative(value_f)) flags |= VAL_IS_NEG;

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
      assert(FALSE);
    }
  }

  struct decimal ret;
  ret.digits = val_u64;
  ret.exponent = val_exp;
  ret.flags = flags;
  return ret;
}

void qb_stdprintusing(QBENV *env, QBSTR fmt, QBPUI *ctx) {
  qb_stdprintusing_const(env, fmt.data, fmt.size, ctx);
}

void qb_stdprintusing_const(QBENV *env, char *fmt_text, size_t fmt_size, QBPUI *ctx) {
  // reverse the QBPUI linked list
  QBPUI *print_order_ctx = NULL;
  while (ctx != NULL) {
    QBPUI *next = ctx->next;
    ctx->next = print_order_ctx;
    print_order_ctx = ctx;
    ctx = next;
  }

  while (print_order_ctx != NULL) {
    // TODO: implement printing logic
    QBPUI *next = print_order_ctx->next;
    int32_t type = print_order_ctx->type;
    char scratch[MAX_OUT];
    size_t outlen;
    if (type == QB_PRINTUSING_TYPE_FLOAT) {
      outlen = print_formatted_number(scratch, fmt_text, fmt_size, single_to_decimal(print_order_ctx->data.f32));
    } else if (type == QB_PRINTUSING_TYPE_DOUBLE) {
      outlen = print_formatted_number(scratch, fmt_text, fmt_size, double_to_decimal(print_order_ctx->data.f64));
    } else {
      assert(FALSE);
    }
    qb_stdprint_str_const(env, scratch, outlen, FALSE);
    free(print_order_ctx);
    print_order_ctx = next;
  }
}
