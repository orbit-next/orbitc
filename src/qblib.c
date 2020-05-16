#include <assert.h>
#include <sys/select.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>


#include "qb.h"

#define MIN2(a, b) ((a) < (b) ? (a) : (b))

// Some items below are copies of routines in the freebasic runtime library
// licensed under LGPLv2 or later.

/**
  * Serial Output Format Reference:
  * This program outputs commands in a serialized format to the output file
  *
  * Consumers of this output can then act on this output in any desired way.
  *
  * Everything described below is little-endian for now
  *
  * The output is a sequence of "messages", each beginning with a 1 byte opcode.
  * The types of messages are described below.
  *
  * End program:
  * "00"
  *
  * Print to output:
  * "10" <u8 align> <u64 length> <`length` bytes of data>
  *
  * Start input reading mode:
  * "20" <u8 wrap> <u8 question>
  * note: keystrokes are always sent via the input file. this only serves to notify the
  *   consumer that a string input is occurring so an appropriate interface can be shown
  *
  * End input reading mode:
  * "21"
  *
  * Set screen mode:
  * "80" <i32 mode>
  *
  * Set color of palette item:
  * "81" <i32 slot> <i32 color>
  *
  * Set current palette color:
  * "82" <i32 index>
  *
  * Set cursor location:
  * "83" <i32 row> <i32 col>
  *
  * Clear screen:
  * "84"
  *
  * Beep:
  * "85"
  *
  * Draw a line:
  * "90" <i32 x1> <i32 y1> <i32 x2> <i32 y2> <i32 color> <i32 boxfill>
  * boxfill is the type of fill to apply: 0 is no fill, 1 is box, 2 is box fill
  *
  * Draw a circle:
  * "91" <i32 center x> <i32 center y> <i32 radius> <i32 color>
  *
  * Set a point color:
  * "92" <i32 x> <i32 y> <i32 color>
  *
  * Re-set a point color:
  * "93" <i32 x> <i32 y> <i32 color>
  * the difference between this and the one above is not clear to me
  *
  * Flood fill a region:
  * "94" <i32 x> <i32 y> <i32 paint color> <i32 border color>
  */

QBENV *_qb_create_env(FILE *input, FILE *output, int32_t *err_ptr, int32_t *erl_ptr) {
  #ifndef humanreadable
  char *io_buf = malloc(16384);
  setvbuf(output, io_buf, _IOFBF, 16384);
  #endif
  QBENV *env = (QBENV *)malloc(sizeof(QBENV));
  env->stack_top = NULL;
  env->err_ptr = err_ptr;
  env->erl_ptr = erl_ptr;
  env->gfx_env = NULL;

  env->input = input;
  env->output = output;

  return env;
}

// important note for all string-related functions:
// NULL is an acceptable value for the string data pointer if the size
// of the string is 0

// destroys a string
void _qb_empty_str(QBSTR *str) {
  if (str->data != NULL) {
    free(str->data);
    str->data = NULL;
  }
  str->size = 0;
}

void _qb_empty_str_direct(QBSTR *str) {
  str->data = NULL;
  str->size = 0;
}

// setting strings is by value in qb
void _qb_set_str(QBSTR *dst, QBSTR src) {
  if (src.size == 0) {
    _qb_empty_str(dst);
    return;
  }
  assert(src.data != NULL);

  _qb_empty_str(dst);
  dst->data = (char *)malloc(src.size);
  memcpy(dst->data, src.data, src.size);
  dst->size = src.size;
}

// not exposed for now
static void _qb_set_str_direct(QBSTR *dst, QBSTR src) {
  if (src.size == 0) {
    _qb_empty_str(dst);
    return;
  }
  assert(src.data != NULL);

  dst->data = (char *)malloc(src.size);
  memcpy(dst->data, src.data, src.size);
  dst->size = src.size;
}

void _qb_set_str_const(QBSTR *str, char *text, size_t size) {
  _qb_empty_str(str);
  if (size == 0) {
    // no allocation required
    return;
  }
  _qb_set_str_const_direct(str, text, size);
}

void _qb_set_str_const_direct(QBSTR *str, char *text, size_t size) {
  if (size == 0) {
    _qb_empty_str(str);
    return;
  }
  str->data = (char *)malloc(size);
  memcpy(str->data, text, size);
  str->size = size;
}

int32_t _qb_str_equals(QBSTR a, QBSTR b) {
  if (b.size == 0) {
    return a.size == 0;
  }
  assert(b.data != NULL);

  return _qb_str_equals_const(a, b.data, b.size);
}

int32_t _qb_str_equals_const(QBSTR a, char *b, size_t bsize) {
  if (a.size == 0) {
    return bsize == 0;
  }
  assert(a.data != NULL);

  if (a.size != bsize) {
    return FALSE;
  }

  return memcmp(a.data, b, bsize) == 0;
}

int32_t _qb_str_nequals(QBSTR a, QBSTR b) {
  if (b.size == 0) {
    return a.size != 0;
  }
  assert(b.data != NULL);

  return _qb_str_nequals_const(a, b.data, b.size);
}

int32_t _qb_str_nequals_const(QBSTR a, char *b, size_t bsize) {
  if (a.size == 0) {
    return bsize != 0;
  }
  assert(a.data != NULL);

  if (a.size == bsize) {
    return memcmp(a.data, b, bsize) != 0;
  }

  return TRUE;
}

int32_t _qb_str_lessthan_const(QBSTR a, char *b, size_t bsize) {
  // the empty string is less than everything but another empty string
  if (a.size == 0) {
    return bsize != 0;
  }
  assert(a.data != NULL);

  size_t minsize = MIN2(a.size, bsize);

  int cmp = memcmp(a.data, b, minsize);
  if (cmp == 0) {
    return a.size < bsize;
  }
  return cmp < 0;
}

int32_t _qb_str_greaterthan_const(QBSTR a, char *b, size_t bsize) {
  // the empty string cannot be greater than anything
  if (a.size == 0) {
    return FALSE;
  }
  assert(a.data != NULL);

  size_t minsize = MIN2(a.size, bsize);

  int cmp = memcmp(a.data, b, minsize);
  if (cmp == 0) {
    return a.size > bsize;
  }
  return cmp > 0;
}

void _qb_free_str(QBSTR *str) {
  assert(str->size == 0 || str->data != NULL);

  _qb_empty_str(str);
}

void _qb_str_concat(QBSTR *dst, QBSTR a, QBSTR b) {
  assert(a.size == 0 || a.data != NULL);
  assert(b.size == 0 || b.data != NULL);

  size_t newsize = a.size + b.size;
  if (newsize == 0) {
    // no allocation required
    _qb_empty_str(dst);
    return;
  }
  char *data = (char *)malloc(newsize);
  memcpy(data, a.data, a.size);
  memcpy(data + a.size, b.data, b.size);
  _qb_empty_str(dst);
  dst->size = newsize;
  dst->data = data;
}

// TODO: not sure if i should remove these _direct functions
// they aren't very useful right now
void _qb_str_concat_direct(QBSTR *dst, QBSTR a, QBSTR b) {
  assert(a.size == 0 || a.data != NULL);
  assert(b.size == 0 || b.data != NULL);

  size_t newsize = a.size + b.size;
  if (newsize == 0) {
    // no allocation required
    return;
  }
  dst->size = newsize;
  dst->data = (char *)malloc(newsize);
  memcpy(dst->data, a.data, a.size);
  memcpy(dst->data + a.size, b.data, b.size);
}

void qbf_left_str(QBSTR *dst, QBSTR src, int32_t n) {
  assert(src.size == 0 || src.data != NULL);
  assert(n >= 0);

  _qb_empty_str(dst);
  size_t newsize = MIN2(src.size, (size_t)n);
  if (newsize == 0) {
    // no allocation required
    return;
  }
  dst->size = newsize;
  dst->data = (char *)malloc(newsize);
  memcpy(dst->data, src.data, newsize);
}

void qbf_left_str_direct(QBSTR *dst, QBSTR src, int32_t n) {
  assert(src.size == 0 || src.data != NULL);
  assert(n >= 0);

  size_t newsize = MIN2(src.size, (size_t)n);
  if (newsize == 0) {
    // no allocation required
    return;
  }
  dst->size = newsize;
  dst->data = (char *)malloc(newsize);
  memcpy(dst->data, src.data, newsize);
}

void qbf_right_str(QBSTR *dst, QBSTR src, int32_t n) {
  assert(src.size == 0 || src.data != NULL);
  assert(n >= 0);

  _qb_empty_str(dst);
  size_t newsize = MIN2(src.size, (size_t)n);
  if (newsize == 0) {
    // no allocation required
    return;
  }
  dst->size = newsize;
  dst->data = (char *)malloc(newsize);
  memcpy(dst->data, src.data + src.size - newsize, newsize);
}

void qbf_right_str_direct(QBSTR *dst, QBSTR src, int32_t n) {
  assert(src.size == 0 || src.data != NULL);
  assert(n >= 0);

  size_t newsize = MIN2(src.size, (size_t)n);
  if (newsize == 0) {
    // no allocation required
    return;
  }
  dst->size = newsize;
  dst->data = (char *)malloc(newsize);
  memcpy(dst->data, src.data + src.size - newsize, newsize);
}

void qbf_mid_str(QBSTR *dst, QBSTR src, int32_t start, int32_t length) {
  assert(src.size == 0 || src.data != NULL);
  start--; // start is 1 based
  assert(start >= 0);
  assert(length >= 0);

  _qb_empty_str(dst);
  size_t actualstart = start;
  actualstart = MIN2(actualstart, src.size);
  size_t newsize = MIN2(src.size - actualstart, (size_t)length);
  if (newsize == 0) {
    // no allocation required
    return;
  }

  dst->size = newsize;
  dst->data = (char *)malloc(newsize);
  memcpy(dst->data, src.data + actualstart, newsize);
}

void qbf_mid_str_direct(QBSTR *dst, QBSTR src, int32_t start, int32_t length) {
  assert(src.size == 0 || src.data != NULL);
  start--; // start is 1 based
  assert(start >= 0);
  assert(length >= 0);

  size_t actualstart = start;
  actualstart = MIN2(actualstart, src.size);
  size_t newsize = MIN2(src.size - actualstart, (size_t)length);
  if (newsize == 0) {
    // no allocation required
    return;
  }

  dst->size = newsize;
  dst->data = (char *)malloc(newsize);
  memcpy(dst->data, src.data + actualstart, newsize);
}

void __qbstr_to_ucase(QBSTR *str) {
  char *data = str->data;
  size_t size = str->size;
  for (size_t i = 0; i < size; i++) {
    if (data[i] >= 'a' && data[i] <= 'z') {
      data[i] -= 0x20;
    }
  }
}

void qbf_ucase_str(QBSTR *dst, QBSTR src) {
  _qb_set_str(dst, src);
  __qbstr_to_ucase(dst);
}

void qbf_ucase_str_direct(QBSTR *dst, QBSTR src) {
  _qb_set_str_direct(dst, src);
  __qbstr_to_ucase(dst);
}

void qbf_space_str(QBSTR *dst, int32_t n) {
  assert(n >= 0);

  _qb_empty_str(dst);
  if (n == 0) {
    // no allocation required
    return;
  }
  dst->data = (char *)malloc(n);
  memset(dst->data, ' ', n);
  dst->size = n;
}

void qbf_space_str_direct(QBSTR *dst, int32_t n) {
  assert(n >= 0);

  dst->data = (char *)malloc(n);
  memset(dst->data, ' ', n);
  dst->size = n;
}

void qbf_chr_str(QBSTR *dst, int32_t n) {
  _qb_empty_str(dst);
  dst->data = (char *)malloc(1);
  dst->data[0] = (char)n;
  dst->size = 1;
}

void qbf_chr_str_direct(QBSTR *dst, int32_t n) {
  dst->data = (char *)malloc(1);
  dst->data[0] = (char)n;
  dst->size = 1;
}

// this mutates the string bytes in place, inside the string bounds
void _qb_mid_str_set(QBSTR *dst, int32_t start, int32_t length, QBSTR src) {
  assert(src.size == 0 || src.data != NULL);
  assert(dst->size == 0 || dst->data != NULL);
  start--; // start is 1 based
  assert(start >= 0);
  assert(length >= 0);

  _qb_empty_str(dst);
  size_t actualstart = start;
  actualstart = MIN2(actualstart, dst->size);
  size_t changelength = MIN2(dst->size - actualstart, (size_t)length);
  changelength = MIN2(changelength, src.size);

  memcpy(dst->data + actualstart, src.data, changelength);

}

// TODO: is unaligned access going to be a problem
// on supported architectures? What about endianness
// (not mentioned in freebasic docs)?
float qbf_cvs(QBSTR src) {
  assert(src.size >= 4);
  return *((float *)(src.data));
}

int16_t qbf_cvi(QBSTR src) {
  assert(src.size >= 2);
  return *((int16_t *)(src.data));
}

double qbf_cvd(QBSTR src) {
  assert(src.size >= 8);
  return *((double *)(src.data));
}

int32_t qbf_cvl(QBSTR src) {
  assert(src.size >= 4);
  return *((int32_t *)(src.data));
}

void qbf_mks_str(QBSTR *dst, float n) {
  _qb_empty_str(dst);
  dst->data = (char *)malloc(4);
  *((float *)(dst->data)) = n;
  dst->size = 4;
}

void qbf_mki_str(QBSTR *dst, int16_t n) {
  _qb_empty_str(dst);
  dst->data = (char *)malloc(2);
  *((int16_t *)(dst->data)) = n;
  dst->size = 2;
}

void qbf_mkd_str(QBSTR *dst, double n) {
  _qb_empty_str(dst);
  dst->data = (char *)malloc(8);
  *((double *)(dst->data)) = n;
  dst->size = 8;
}

void qbf_mkl_str(QBSTR *dst, int32_t n) {
  _qb_empty_str(dst);
  dst->data = (char *)malloc(4);
  *((int32_t *)(dst->data)) = n;
  dst->size = 4;
}


int16_t qbf_cint(double n) {
  return (int16_t)n;
}

int32_t qbf_asc(QBSTR str) {
  assert(str.size > 0);
  return (unsigned char)(str.data[0]);
}

int32_t qbf_len(QBSTR str) {
  return str.size;
}

void qbf_inkey_str(QBENV *env, QBSTR *dst) {
  _qb_empty_str(dst);
  fflush(env->output);
  // TODO: support win32
  fd_set r;
  struct timeval timeout;
  timeout.tv_sec = 0;
  timeout.tv_usec = 2500;
  int filenum = fileno(env->input);

  FD_ZERO(&r);
  FD_SET(filenum, &r);

  if (select(filenum + 1, &r, NULL, NULL, &timeout)) {
    int c = fgetc(env->input);
    if (c == EOF) {
      fprintf(stderr, "EOF on inkey\n");
      qb_end(env);
    }
    // read extended key
    if (c == '\0') {
      dst->data = (char *)malloc(2);
      dst->data[0] = c;
      dst->data[1] = fgetc(env->input);
      dst->size = 2;
    } else {
      dst->data = (char *)malloc(1);
      dst->data[0] = c;
      dst->size = 1;
    }
  }
}

void qbf_input_str(QBENV *env, QBSTR *dst, int32_t n) {
  assert(n >= 0);
  _qb_empty_str(dst);
  if (n == 0) {
    return;
  }
  char *buf = (char *)malloc(n);

  for (int32_t i = 0; i < n;) {
    int c;
    c = fgetc(env->input);
    // According to freebasic docs: extended keys are not read by this function
    // extended keys are 2 character sequences where the first character is '\0'
    // we skip them when encountered
    if (c == 0) {
      fgetc(env->input);
    } else {
      buf[i] = c;
      i++;
    }
  }

  dst->size = n;
  dst->data = buf;
}

inline double qbf_sgn(double x) {
    if (x > 0) {
        return 1;
    }
    if (x < 0) {
        return -1;
    }
    return x; // 0, -0 and NaN
}

inline double qbf_fix(double x) {
    if (x > 0) {
        return floor(x);
    }
    if (x < 0) {
        return ceil(x);
    }
    return x; // 0, -0 and NaN
}


double qbf_timer() {
  // TODO: use different implementations for unix and win32
  // copied from freebasic
  struct timeval tv;
	gettimeofday(&tv, NULL);
	return (((double)tv.tv_sec * 1000000.0) + (double)tv.tv_usec) * 0.000001;
}

static int32_t __qb_rnd_iseed = 327680;

double qbf_rnd() {
  // copied from freebasic

  // a seed value, not used for now
  // defaults to 1
  float n = 1;

  union {
    float f;
    uint32_t i;
  } ftoi;

  if(n != 0.0) {
    if(n < 0.0) {
      ftoi.f = n;
      uint32_t s = ftoi.i;
      __qb_rnd_iseed = s + (s >> 24);
    }
    __qb_rnd_iseed = ((__qb_rnd_iseed * 0xfd43fd) + 0xc39ec3) & 0xffffff;
  }
  return (float)__qb_rnd_iseed / (float)0x1000000;
}

QBFILE *qb_open_cstr(QBENV *env, char *path, char *mode) {
  return qb_open_reclen_cstr(env, path, mode, 1);
}

QBFILE *qb_open(QBENV *env, QBSTR path, char *mode) {
  return qb_open_reclen(env, path, mode, 1);
}

QBFILE *qb_open_reclen_cstr(QBENV *env, char *path, char *mode, int32_t reclen) {
   char *cmode;
   int32_t flags;
   assert(mode[1] == '\0');
   switch (mode[0]) {
     case 'R':
       cmode = "r+";
       flags = QB_FILE_READABLE | QB_FILE_WRITABLE | QB_FILE_SEEKABLE;
       break;
     case 'I':
       cmode = "r";
       flags = QB_FILE_READABLE;
       break;
     case 'O':
       cmode = "w";
       flags = QB_FILE_WRITABLE;
       break;
     default:
       assert(FALSE);
   }
   FILE *cfile = fopen(path, cmode);
#ifdef nooutput
#elif humanreadable
   if (cfile == NULL) {
     fprintf(stderr, "Failed to open file \"%s\"\n", path);
   }
#endif
   assert(cfile != NULL);

   QBFILE *f = (QBFILE *)malloc(sizeof(QBFILE));
   f->file = cfile;
   f->flags = flags;
   f->reclen = reclen;

   return f;
}

QBFILE *qb_open_reclen(QBENV *env, QBSTR path, char *mode, int32_t reclen) {
  char *path_cstr = malloc(path.size + 1);
  memcpy(path_cstr, path.data, path.size);
  path_cstr[path.size] = '\0';
  QBFILE *ret = qb_open_reclen_cstr(env, path_cstr, mode, reclen);
  free(path_cstr);
  return ret;
}

void qb_close(QBFILE *file) {
  assert(file->file != NULL);
  fclose(file->file);
  free(file);
}

int32_t qbf_eof(QBFILE *file) {
  assert(file->file != NULL);
  return feof(file->file);
}

int32_t qbf_lof(QBFILE *file) {
  FILE *cfile = file->file;
  long current = ftell(cfile);
  fseek(cfile, 0, SEEK_END);
  long size = ftell(cfile);
  fseek(cfile, current, SEEK_SET);
  return (int32_t) size;
}

// note recnum is 1 based
void qb_fget(QBFILE *file, int32_t recnum, QBSTR *output) {
  assert(file->flags & QB_FILE_SEEKABLE);
  assert(recnum > 0);

  _qb_empty_str(output);

  size_t reclen = file->reclen;
  char *buffer = (char *)malloc(reclen);
  fseek(file->file, reclen * (recnum - 1), SEEK_SET);
  size_t bytesread = fread(buffer, 1, reclen, file->file);

  // we assert if the buffer is not filled
  // the freebasic docs don't mention this
  // but we do it for now
  assert(bytesread == reclen);
  output->data = buffer;
  output->size = reclen;
}

void qb_fprint_str(QBFILE *file, QBSTR str) {
  assert(str.size == 0 || str.data != NULL);
  assert(QB_FILE_WRITABLE & file->flags);
  if (str.size == 0) {
    return;
  }

  fwrite(str.data, 1, str.size, file->file);
}

void qb_fput(QBFILE *file, int32_t recnum, QBSTR data) {
  assert(
    (file->flags & QB_FILE_SEEKABLE) &&
    (file->flags & QB_FILE_WRITABLE)
  );
  assert(recnum > 0);
  // TODO: should we require this?
  assert(data.size == file->reclen);

  fseek(file->file, file->reclen * (recnum - 1), SEEK_SET);
  fwrite(data.data, 1, file->reclen, file->file);
}

// TODO: implement all these functions with side effects
void qb_stdinput_str(
  QBENV *env,
  QBSTR prompt,
  QBSTR *output,
  int32_t wrap,
  int32_t question
) {
  assert(prompt.size == 0 || prompt.data != NULL);
  qb_stdinput_str_const(env, prompt.data, prompt.size, output, wrap, question);
}

void qb_stdinput_str_const(
  QBENV *env,
  char *prompt_text,
  size_t prompt_size,
  QBSTR *output,
  int32_t wrap,
  int32_t question
) {
  // this version is less fancy than the freebasic input, supporting only backspace
  // unsupported characters are silently ignored

  // for now we require the client to keep a copy of the
  // input state for display purposes
  // maybe we will find a better way
  qb_stdprint_str_const(env, prompt_text, prompt_size, FALSE);
#ifdef nooutput
#elif humanreadable
  fprintf(
    env->output,
    "Enter input mode, wrap = %d, question = %d, prompt bytes = %lu, content = \"",
    wrap,
    question,
    prompt_size
  );
  fwrite(prompt_text, 1, prompt_size, env->output);
  fprintf(env->output, "\"\n");
#else
  fputc(0x20, env->output);
  fputc(wrap ? TRUE : FALSE, env->output);
  fputc(question ? TRUE : FALSE, env->output);
#endif
  // since this function blocks, we need to make sure all the output is flushed
  fflush(env->output);

  int32_t c;
  size_t capacity = 16;
  char *buffer = (char *)malloc(capacity);
  size_t size = 0;
  while (1) {
    c = fgetc(env->input);
    if (c == EOF) {
      qb_end(env);
    } else if (c == '\r' || c == '\n') {
      // works when size is 0
      buffer = realloc(buffer, size);
      output->size = size;
      output->data = buffer;
#ifdef nooutput
#elif humanreadable
      fprintf(env->output, "End input mode\n");
#else
      fputc(0x21, env->output);
#endif
      return;
    } else if (c == '\b') {
      if (size > 0) { size--; }
    } else if (c >= 0x20 && c <= 0x7e) {
      if (size == capacity) {
        buffer = realloc(buffer, capacity * 2);
      }
      buffer[size] = c;
      size++;
    }
  }
}

void qb_stdprint_str(QBENV *env, QBSTR str, int32_t align_columns) {
  qb_stdprint_str_const(env, str.data, str.size, align_columns);
}

void qb_stdprint_str_const(QBENV *env, char *text, size_t size, int32_t align_columns) {
#ifdef nooutput
#elif humanreadable
  fprintf(
    env->output,
    "Print string, do align = %d, bytes = %lu, content = \"",
    align_columns,
    size
  );
  fwrite(text, 1, size, env->output);
  fprintf(env->output, "\"\n");
#else
  fputc(0x10, env->output);
  fputc(align_columns ? TRUE : FALSE, env->output);
  fwrite((char *)(&size), 1, 8, env->output);
  fwrite(text, 1, size, env->output);
#endif
}

void qb_stdprint_i32(QBENV *env, int32_t n, int32_t align_columns) {

}

QBPUI *_qb_get_pu_ctx() {
  return NULL;
}

QBPUI *_qb_pu_add_float(QBPUI *top, float n, int32_t align_columns) {
  QBPUI *ctx = (QBPUI *)malloc(sizeof(QBPUI));
  ctx->next = top;
  ctx->type = QB_PRINTUSING_TYPE_FLOAT;
  ctx->align_columns = align_columns;
  ctx->data.f32 = n;

  return ctx;
}

QBPUI *_qb_pu_add_double(QBPUI *top, double n, int32_t align_columns) {
  QBPUI *ctx = (QBPUI *)malloc(sizeof(QBPUI));
  ctx->next = top;
  ctx->type = QB_PRINTUSING_TYPE_DOUBLE;
  ctx->align_columns = align_columns;
  ctx->data.f64 = n;

  return ctx;
}

void qb_run(QBENV *env, QBSTR path) {
  qb_run_const(env, path.data, path.size);
}

void qb_run_const(QBENV *env, char *text, size_t size) {
  // TODO: noop for now
  fprintf(stderr, "Trying to run program \"");
  fwrite(text, 1, size, stderr);
  fprintf(stderr, "\"\n");
}

void qb_screen(QBENV *env, int32_t mode) {
  // only mode 12 is supported for now
  assert(mode == 12);
  env->gfx_env = (QB_GFX_ENV *)malloc(sizeof(QB_GFX_ENV));
  env->gfx_env->screen_mode = mode;
  // the graphics cursor starts in the center
  env->gfx_env->line_pos.x = 640 / 2;
  env->gfx_env->line_pos.y = 480 / 2;
#ifdef nooutput
#elif humanreadable
  fprintf(env->output, "Set screen mode, mode = %d\n", mode);
#else
  fputc(0x80, env->output);
  fwrite((void *)(&mode), 1, 4, env->output);
#endif
}

void qb_palette(QBENV *env, int32_t slot, int32_t color) {
  assert(slot >= 0 && slot <= 15);
#ifdef nooutput
#elif humanreadable
  fprintf(env->output, "Set palette item, slot = %d, color = %x\n", slot, color);
#else
  fputc(0x81, env->output);
  fwrite((void *)(&slot), 1, 4, env->output);
  fwrite((void *)(&color), 1, 4, env->output);
#endif
}

void qb_color(QBENV *env, int32_t index) {
  assert(index >= 0 && index <= 15);
#ifdef nooutput
#elif humanreadable
  fprintf(env->output, "Set current palette color, index = %d\n", index);
#else
  fputc(0x82, env->output);
  fwrite((void *)(&index), 1, 4, env->output);
#endif
}

void qb_locate(QBENV *env, int32_t row, int32_t col) {
#ifdef nooutput
#elif humanreadable
  fprintf(env->output, "Set cursor location: row = %d, col = %d\n", row, col);
#else
  fputc(0x83, env->output);
  fwrite((void *)(&row), 1, 4, env->output);
  fwrite((void *)(&col), 1, 4, env->output);
#endif
}

void qb_cls(QBENV *env) {
#ifdef nooutput
#elif humanreadable
  fprintf(env->output, "Clear screen\n");
#else
  fputc(0x84, env->output);
#endif
}

void qb_beep(QBENV *env) {
#ifdef nooutput
#elif humanreadable
  fprintf(env->output, "Beep\n");
#else
  fputc(0x85, env->output);
#endif
}

void __qb_line(QBENV *env, int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t color, int32_t box) {
  assert(color >= 0 && color <= 15);
  assert(box >= 0 && box <= 2);
  env->gfx_env->line_pos.x = x2;
  env->gfx_env->line_pos.y = y2;

#ifdef nooutput
#elif humanreadable
  fprintf(
    env->output,
    "Draw line, from (%d, %d), to (%d, %d), color = %d, box mode = %d\n",
    x1,
    y1,
    x2,
    y2,
    color,
    box
  );
#else
  fputc(0x90, env->output);
  fwrite((void *)(&x1), 1, 4, env->output);
  fwrite((void *)(&y1), 1, 4, env->output);
  fwrite((void *)(&x2), 1, 4, env->output);
  fwrite((void *)(&y2), 1, 4, env->output);
  fwrite((void *)(&color), 1, 4, env->output);
  fwrite((void *)(&box), 1, 4, env->output);
#endif
}

void __qb_lineto(QBENV *env, int32_t x2, int32_t y2, int32_t color, int32_t box) {
  __qb_line(env, env->gfx_env->line_pos.x, env->gfx_env->line_pos.y, x2, y2, color, box);
}

void qb_circle(QBENV *env, int32_t x, int32_t y, int32_t r, int32_t color) {
  assert(color >= 0 && color <= 15);
  env->gfx_env->line_pos.x = x;
  env->gfx_env->line_pos.y = y;
#ifdef nooutput
#elif humanreadable
  fprintf(
    env->output,
    "Draw circle, center (%d, %d), radius = %d, color = %d\n",
    x,
    y,
    r,
    color
  );
#else
  fputc(0x91, env->output);
  fwrite((void *)(&x), 1, 4, env->output);
  fwrite((void *)(&y), 1, 4, env->output);
  fwrite((void *)(&r), 1, 4, env->output);
  fwrite((void *)(&color), 1, 4, env->output);
#endif
}

void qb_pset(QBENV *env, int32_t x, int32_t y, int32_t color) {
  assert(color >= 0 && color <= 15);
  env->gfx_env->line_pos.x = x;
  env->gfx_env->line_pos.y = y;
#ifdef nooutput
#elif humanreadable
  fprintf(env->output, "Set point color, at (%d, %d), color = %d\n", x, y, color);
#else
  fputc(0x92, env->output);
  fwrite((void *)(&x), 1, 4, env->output);
  fwrite((void *)(&y), 1, 4, env->output);
  fwrite((void *)(&color), 1, 4, env->output);
#endif
}

void qb_preset(QBENV *env, int32_t x, int32_t y, int32_t color) {
  assert(color >= 0 && color <= 15);
  env->gfx_env->line_pos.x = x;
  env->gfx_env->line_pos.y = y;
#ifdef nooutput
#elif humanreadable
  fprintf(env->output, "Re-set point color, at (%d, %d), color = %d\n", x, y, color);
#else
  fputc(0x93, env->output);
  fwrite((void *)(&x), 1, 4, env->output);
  fwrite((void *)(&y), 1, 4, env->output);
  fwrite((void *)(&color), 1, 4, env->output);
#endif
}

void qb_paint(QBENV *env, int32_t x, int32_t y, int32_t paint_color, int32_t border_color) {
  assert(paint_color >= 0 && paint_color <= 15);
  assert(border_color >= 0 && border_color <= 15);
  env->gfx_env->line_pos.x = x;
  env->gfx_env->line_pos.y = y;
#ifdef nooutput
#elif humanreadable
  fprintf(
    env->output,
    "Flood fill region, start at (%d, %d), paint color = %d, border color = %d\n",
    x,
    y,
    paint_color,
    border_color
  );
#else
  fputc(0x94, env->output);
  fwrite((void *)(&y), 1, 4, env->output);
  fwrite((void *)(&y), 1, 4, env->output);
  fwrite((void *)(&paint_color), 1, 4, env->output);
  fwrite((void *)(&border_color), 1, 4, env->output);
#endif
}

void qb_end(QBENV *env) {
#ifdef nooutput
#elif humanreadable
  fprintf(env->output, "Exit program\n");
#else
  fputc(0x0, env->output);
#endif
  exit(0);
}

void *_qb_gosub_push(QBENV *env) {
  QB_STACK_FRAME *frame = (QB_STACK_FRAME *)malloc(sizeof(QB_STACK_FRAME));
  frame->prev = env->stack_top;
  env->stack_top = frame;
  return &(frame->buf);
}

void _qb_gosub_return(QBENV *env) {
  assert(env->stack_top != NULL);
  jmp_buf tmpbuf;
  memcpy(tmpbuf, env->stack_top->buf, sizeof(jmp_buf));
  QB_STACK_FRAME *prev = env->stack_top->prev;
  free(env->stack_top);
  env->stack_top = prev;
  longjmp(tmpbuf, 1);
}

void _qb_gosub_pop(QBENV *env) {
  assert(env->stack_top != NULL);
  QB_STACK_FRAME *prev = env->stack_top->prev;
  free(env->stack_top);
  env->stack_top = prev;
}
