#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <setjmp.h>
#include <math.h>

#define FALSE 0
#define TRUE 1

typedef struct {
  char *data;
  size_t size;
} QBSTR;

typedef struct {
  int32_t x;
  int32_t y;
} QB_I32_VEC;

typedef struct {
  int32_t screen_mode;
  QB_I32_VEC line_pos;
} QB_GFX_ENV;

typedef struct _QB_STACK_FRAME {
  struct _QB_STACK_FRAME *prev;
  jmp_buf buf;
} QB_STACK_FRAME;

typedef struct {
  QB_STACK_FRAME *stack_top;
  int32_t *err_ptr;
  int32_t *erl_ptr;
  QB_GFX_ENV *gfx_env;
  FILE *input;
  FILE *output;
} QBENV;

QBENV *_qb_create_env(FILE *input, FILE *output, int32_t *err_ptr, int32_t *erl_ptr);

void _qb_empty_str(QBSTR *str);
void _qb_empty_str_direct(QBSTR *str);

void _qb_set_str(QBSTR *dst, QBSTR src);

void _qb_set_str_const(QBSTR *str, char *text, size_t size);
void _qb_set_str_const_direct(QBSTR *str, char *text, size_t size);

int32_t _qb_str_equals(QBSTR a, QBSTR b);
int32_t _qb_str_equals_const(QBSTR a, char *b, size_t size);
int32_t _qb_str_nequals(QBSTR a, QBSTR b);
int32_t _qb_str_nequals_const(QBSTR a, char *b, size_t size);
int32_t _qb_str_lessthan_const(QBSTR a, char *b, size_t size);
int32_t _qb_str_greaterthan_const(QBSTR a, char *b, size_t size);

void _qb_free_str(QBSTR *str);

void _qb_str_concat(QBSTR *dst, QBSTR a, QBSTR b);
void _qb_str_concat_direct(QBSTR *dst, QBSTR a, QBSTR b);

void qbf_left_str(QBSTR *dst, QBSTR src, int32_t n);
void qbf_left_str_direct(QBSTR *dst, QBSTR src, int32_t n);
void qbf_right_str(QBSTR *dst, QBSTR src, int32_t n);
void qbf_right_str_direct(QBSTR *dst, QBSTR src, int32_t n);
void qbf_mid_str(QBSTR *dst, QBSTR src, int32_t start, int32_t length);
void qbf_mid_str_direct(QBSTR *dst, QBSTR src, int32_t start, int32_t length);
void qbf_ucase_str(QBSTR *dst, QBSTR src);
void qbf_ucase_str_direct(QBSTR *dst, QBSTR src);
void qbf_space_str(QBSTR *dst, int32_t n);
void qbf_space_str_direct(QBSTR *dst, int32_t n);
void qbf_chr_str(QBSTR *dst, int32_t n);
void qbf_chr_str_direct(QBSTR *dst, int32_t n);

void _qb_mid_str_set(QBSTR *dst, int32_t start, int32_t length, QBSTR src);

// byte string to single
float qbf_cvs(QBSTR src);
// byte string to int16
int16_t qbf_cvi(QBSTR src);
// byte string to double
double qbf_cvd(QBSTR src);
// byte string to int32
int32_t qbf_cvl(QBSTR src);

void qbf_mks_str(QBSTR *dest, float n);
void qbf_mki_str(QBSTR *dest, int16_t n);
void qbf_mkd_str(QBSTR *dest, double n);
void qbf_mkl_str(QBSTR *dest, int32_t n);

int16_t qbf_cint(double n);

int32_t qbf_asc(QBSTR str);
int32_t qbf_len(QBSTR str);

void qbf_inkey_str(QBENV *env, QBSTR *dst);
void qbf_input_str(QBENV *env, QBSTR *dst, int32_t n);

double qbf_timer();

// TODO: is this the best way?
// double qbf_sin(double x);
#define qbf_sin(x) (sin(x))
// double qbf_cos(double x);
#define qbf_cos(x) (cos(x))
// double qbf_atn(double x);
#define qbf_atn(x) (atan(x))
// double qbf_sqr(double x); // sqrt
#define qbf_sqr(x) (sqrt(x))
// double qbf_abs(double x);
#define qbf_abs(x) (fabs(x))
// double qbf_int(double x);
#define qbf_int(x) (floor(x))
// double _qbf_pow(double a, double b);
#define _qbf_pow(x, y) (pow(x, y))
double qbf_sgn(double x);
double qbf_fix(double x);

double qbf_timer();
double qbf_rnd();

#define QB_FILE_READABLE 0x1
#define QB_FILE_WRITABLE 0x2
#define QB_FILE_SEEKABLE 0x10

typedef struct {
    FILE *file;
    int32_t flags;
    size_t reclen;
} QBFILE;

QBFILE *qb_open_cstr(QBENV *env, char *path, char *mode);
QBFILE *qb_open(QBENV *env, QBSTR path, char *mode);
QBFILE *qb_open_reclen_cstr(QBENV *env, char *path, char *mode, int32_t reclen);
QBFILE *qb_open_reclen(QBENV *env, QBSTR path, char *mode, int32_t reclen);
void qb_close(QBFILE *file);

int32_t qbf_eof(QBFILE *file);
int32_t qbf_lof(QBFILE *file);

void qb_fget(QBFILE *file, int32_t recnum, QBSTR *output);

void qb_finput_double(QBFILE *file, double *output);
void qb_finput_float(QBFILE *file, float *output);
void qb_finput_str(QBFILE *file, QBSTR *output);

void qb_fprint_str(QBFILE *file, QBSTR str);
void qb_fput(QBFILE *file, int32_t recnum, QBSTR data);

void qb_stdinput_str(QBENV *env, QBSTR prompt, QBSTR *output, int32_t wrap, int32_t question);
void qb_stdinput_str_const(QBENV *env, char *text, size_t size, QBSTR *output, int32_t wrap, int32_t question);

void qb_stdprint_str(QBENV *env, QBSTR str, int32_t align_columns);
void qb_stdprint_str_const(QBENV *env, char *text, size_t size, int32_t align_columns);

void qb_stdprint_i32(QBENV *env, int32_t n, int32_t align_columns);

typedef union {
  float f32;
  double f64;
} QB_PRINT_UNION;

#define QB_PRINTUSING_TYPE_FLOAT (8)
#define QB_PRINTUSING_TYPE_DOUBLE (9)

// an item in a stack of things to print
typedef struct _QB_PRINTUSING_ITEM {
  struct _QB_PRINTUSING_ITEM *next;
  uint32_t type;
  int32_t align_columns;
  QB_PRINT_UNION data;
} QBPUI;

QBPUI *_qb_get_pu_ctx();

QBPUI *_qb_pu_add_float(QBPUI *top, float n, int32_t align_columns);
QBPUI *_qb_pu_add_double(QBPUI *top, double n, int32_t align_columns);

// ctx is no longer valid after calling these 2 functions
// this cleans up the ctx stack
void qb_stdprintusing(QBENV *env, QBSTR fmt, QBPUI *ctx);
void qb_stdprintusing_const(QBENV *env, char *fmt_text, size_t fmt_size, QBPUI *ctx);

#define QBM_std_pu_float(env, fmt, n, align_columns) { QBPUI *$ps = _qb_get_pu_ctx(); $ps = _qb_pu_add_float($ps, n, align_columns); qb_stdprintusing(env, fmt, $ps); }
#define QBM_std_pu_const_float(env, fmt_text, fmt_size, n, align_columns) { QBPUI *$ps = _qb_get_pu_ctx(); $ps = _qb_pu_add_double($ps, n, align_columns); qb_stdprintusing_const(env, fmt_text, fmt_size, $ps); }
#define QBM_std_pu_double(env, fmt, n, align_columns) { QBPUI *$ps = _qb_get_pu_ctx(); $ps = _qb_pu_add_float($ps, n, align_columns); qb_stdprintusing(env, fmt, $ps); }
#define QBM_std_pu_const_double(env, fmt_text, fmt_size, n, align_columns) { QBPUI *$ps = _qb_get_pu_ctx(); $ps = _qb_pu_add_double($ps, n, align_columns); qb_stdprintusing_const(env, fmt_text, fmt_size, $ps); }

void qb_run(QBENV *env, QBSTR path);
void qb_run_const(QBENV *env, char *text, size_t size);

void qb_screen(QBENV *env, int32_t mode);
void qb_palette(QBENV *env, int32_t slot, int32_t color);
void qb_color(QBENV *env, int32_t index);

void qb_locate(QBENV *env, int32_t row, int32_t col);
void qb_cls(QBENV *env);

void qb_beep(QBENV *env);

void __qb_line(QBENV *env, int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t color, int32_t box);
void __qb_lineto(QBENV *env, int32_t x2, int32_t y2, int32_t color, int32_t box);

#define QB_LINE_BOX_NONE 0
#define QB_LINE_BOX_B 1
#define QB_LINE_BOX_BF 2

#define qb_line(env, x1, y1, x2, y2, color) __qb_line(env, x1, y1, x2, y2, color, QB_LINE_BOX_NONE)
#define qb_lineto(env, x2, y2, color) __qb_lineto(env, x2, y2, color, QB_LINE_BOX_NONE)

#define qb_linebox(env, x1, y1, x2, y2, color, box) __qb_line(env, x1, y1, x2, y2, color, box)
#define qb_lineboxto(env, x2, y2, color, box) __qb_lineto(env, x2, y2, color, box)

void qb_circle(QBENV *env, int32_t x, int32_t y, int32_t r, int32_t color);
void qb_pset(QBENV *env, int32_t x, int32_t y, int32_t color);
void qb_preset(QBENV *env, int32_t x, int32_t y, int32_t color);
void qb_paint(QBENV *env, int32_t x, int32_t y, int32_t paint_color, int32_t border_color);

void qb_end();

// returns the pointer to the jump buffer
void *_qb_gosub_push(QBENV *env);
void _qb_gosub_return(QBENV *env);
void _qb_gosub_pop(QBENV *env);

#define QBM_new_str(name) QBSTR name = {0};
#define QBM_new_empty_str(name) QBSTR name; _qb_empty_str_direct(&name);
#define QBM_new_const_str(name, text, length) QBSTR name; _qb_set_str_const_direct(&name, text, length);

#define QBM_gosub(env, label) if (!setjmp(_qb_gosub_push(env))) {goto label;}

#define QBM_bidifor(var, start, end, step) for (var = start; end >= start ? var <= end : var >= end; var += step)
