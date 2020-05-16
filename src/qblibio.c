#include "qb.h"
#include <sys/types.h>

// Most of this file is from the freebasic source
// https://github.com/freebasic/fbc

#define MAX_NUMERIC_LEN (2 + 64 + 1)
#define MAX_INT_LEN 9
#define MAX_LONG_LEN 18

static int skip_whitespace(FILE *f) {
  int32_t c;
  do {
    c = fgetc(f);
    if (c == EOF) { break; }
  } while ((c == ' ') || (c == '\t'));

  return c;
}


static void skip_delimiter(FILE *f, int32_t c) {
  /* skip white space */
  while ((c == ' ') || (c == '\t')) {
    c = fgetc(f);
  }

  switch (c) {
    case ',':
    case EOF:
      break;

    case '\n':
      break;

    case '\r':
      if ((c = fgetc(f)) != '\n') {
        ungetc(c, f);
      }
      break;

    default:
      ungetc(c, f);
      break;
  }
}

static int get_input_token(
  FILE *file,
  char *buffer,
  ssize_t max_chars,
  int32_t is_string,
  int32_t *isfp
) {
  /* max_chars does not include the null terminator, the buffer is
     assumed to be big enough to hold at least the null terminator */

  int32_t c, isquote, hasamp, skipdelim;
  ssize_t len;

  *isfp = FALSE;

  skipdelim = TRUE;
  isquote = FALSE;
  hasamp = FALSE;
  len = 0;

  c = skip_whitespace(file);

  while ((c != EOF) && (len < max_chars)) {
    switch (c) {
      case '\n':
        skipdelim = FALSE;
        goto exit;

      case '\r':
        if ((c = fgetc(file)) != '\n') {
          ungetc(c, file);
        }
        skipdelim = FALSE;
        goto exit;

      case '"':
        if (!isquote) {
          if (len == 0) {
            isquote = TRUE;
          }
          else {
            goto savechar;
          }
        }
        else
        {
          isquote = FALSE;
          if (is_string) {
            c = fgetc(file);
            goto exit;
          }
        }

        break;

      case ',':
        if (!isquote) {
          skipdelim = FALSE;
          goto exit;
        }

        goto savechar;

      case '&':
        hasamp = TRUE;
        goto savechar;

      case 'd':
      case 'D':
        /* NOTE: if exponent letter is d|D, and
         * is_string == FALSE, then convert the d|D
         * to an e|E. strtod() which
         * will later be used to convert the string
         * to float won't accept d|D anywhere but
         * on windows. (jeffm)
         */
        if (!hasamp && !is_string) {
          ++c;
        }
        /* fall through */

      case 'e':
      case 'E':
      case '.':
        if (!hasamp)
        {
          *isfp = TRUE;
        }
        goto savechar;

      case '\t':
      case ' ':
        if (!isquote) {
          if (!is_string) {
            goto exit;
          }
        }
        goto savechar;

      default:
  savechar:;
        *buffer++ = c;
        ++len;
        break;
    }

    c = fgetc(file);
  }

  exit:
  /* add the null-term */
  *buffer = '\0';

  /* skip comma or newline */
  if (skipdelim)
    skip_delimiter(file, c);

  return len;
}

char *str_skip_char(char *s, ssize_t len, int32_t c)
{
  char *p = s;
  if (s != NULL) {
    while ((--len >= 0) && ((int32_t)*p == c)) {
      ++p;
    }
  }
  return p;
}

int32_t str_radix_to_int(char *src, ssize_t len, int32_t radix) {
  int32_t c, v;
  v = 0;

  switch(radix) {
    /* hex */
    case 16:
      while (--len >= 0) {
        c = *src++;
        if ((c >= 97) && (c <= 102)) {
          c -= 87;
        }
        else if ((c >= 65) && (c <= 70)) {
          c -= 55;
        }
        else if ((c >= 48) && (c <= 57)) {
          c -= 48;
        }
        else
          break;

        v = (v * 16) + c;
      }
      break;

    /* oct */
    case 8:
      while (--len >= 0) {
        c = *src++;
        if ((c >= 48) && (c <= 55)) {
          v = (v * 8) + (c - 48);
        }
        else
          break;
      }
      break;

    /* bin */
    case 2:
      while (--len >= 0) {
        c = *src++;
        if ((c >= 48) && (c <= 49))  {
          v = (v * 2) + (c - 48);
        }
        else
          break;
      }
      break;

    default:
      break;
  }

  return v;
}

static int32_t str_to_int32(char *src, ssize_t len) {
  char *p;
  int32_t radix, skip;

  /* skip white spc */
  p = str_skip_char(src, len, 32);

  len -= (ssize_t)(p - src);
  if (len < 1) {
    return 0;
  }

  else if ((len >= 2) && (p[0] == '&')) {
    radix = 0;
    skip = 2;
    switch(p[1]) {
      case 'h':
      case 'H':
        radix = 16;
        break;
      case 'o':
      case 'O':
        radix = 8;
        break;
      case 'b':
      case 'B':
        radix = 2;
        break;

      default: /* assume octal */
        radix = 8;
        skip = 1;
        break;
    }

    if (radix != 0) {
      return str_radix_to_int(&p[skip], len - skip, radix);
    }
  }

  /* atoi() saturates values outside [-2^31, 2^31)
  so use strtoul() instead */
  return strtoul(p, NULL, 10);
}

static int64_t str_to_int64(char *src, ssize_t len) {
  char *p;
  int32_t radix, skip;

  /* skip white spc */
  p = str_skip_char(src, len, 32);

  len -= (ssize_t)(p - src);
  if (len < 1)
    return 0;

  radix = 10;
  if ((len >= 2) && (p[0] == '&')) {
    skip = 2;
    switch (p[1]) {
      case 'h':
      case 'H':
        radix = 16;
        break;
      case 'o':
      case 'O':
        radix = 8;
        break;
      case 'b':
      case 'B':
        radix = 2;
        break;

      default: /* assume octal */
        radix = 8;
        skip = 1;
        break;
    }

    if (radix != 10) {
      p += skip;
    }
  }

  /* strtoll() saturates values outside [-2^63, 2^63)
  so use strtoull() instead */
  return (int64_t)strtoull(p, NULL, radix);
}

void qb_finput_double(QBFILE *file, double *output) {
  char buffer[MAX_NUMERIC_LEN + 1];
  ssize_t len;
  int32_t isfp;

  len = get_input_token(file->file, buffer, MAX_NUMERIC_LEN, FALSE, &isfp);

  if (isfp == FALSE) {
    if (len <= MAX_INT_LEN) {
      *output = (double)str_to_int32(buffer, len);
    } else if (len <= MAX_LONG_LEN) {
      *output = (double)str_to_int64(buffer, len);
    } else {
      if (buffer[0] == '&') {
        *output = (double)str_to_int64(buffer, len);
      } else {
        *output = strtod(buffer, NULL);
      }
    }
  }
  else {
    *output = strtod(buffer, NULL);
  }
}

void qb_finput_float(QBFILE *file, float *output) {
  char buffer[MAX_NUMERIC_LEN + 1];
  ssize_t len;
  int32_t isfp;

  len = get_input_token(file->file, buffer, MAX_NUMERIC_LEN, FALSE, &isfp);

  if (isfp == FALSE) {
    if (len <= MAX_INT_LEN) {
      *output = (float)str_to_int32(buffer, len);
    } else if (len <= MAX_LONG_LEN) {
      *output = (float)str_to_int64(buffer, len);
    } else {
      if (buffer[0] == '&') {
        *output = (float)str_to_int64(buffer, len);
      } else {
        *output = strtof(buffer, NULL);
      }
    }
  }
  else {
    *output = strtof(buffer, NULL);
  }
}

#define MAX_STRING_LEN 4096

void qb_finput_str(QBFILE *file, QBSTR *output) {
  _qb_empty_str(output);
  char buffer[MAX_STRING_LEN + 1];
  int32_t isfp;
  get_input_token(file->file, buffer, MAX_STRING_LEN, TRUE, &isfp);
  size_t length = strlen(buffer);
  if (length > 0) {
    output->data = (char *)malloc(length);
    memcpy(output->data, buffer, length);
  }
  output->size = length;
}

