#include "../lib/qblibpu.c"

static void _test_i32_pow_10() {
  printf("Test i32_pow_10\n");
  assert(i32_pow_10(0) == 1);
  assert(i32_pow_10(1) == 10);
  assert(i32_pow_10(2) == 100);
  assert(i32_pow_10(3) == 1000);
  assert(i32_pow_10(5) == 100000);
  assert(i32_pow_10(8) == 100000000);
  assert(i32_pow_10(9) == 1000000000);
}

static void _test_u64_pow_10() {
  printf("Test u64_pow_10\n");
  assert(u64_pow_10(0) == 1);
  assert(u64_pow_10(1) == 10);
  assert(u64_pow_10(2) == 100);
  assert(u64_pow_10(3) == 1000);
  assert(u64_pow_10(5) == 100000);
  assert(u64_pow_10(8) == 100000000);
  assert(u64_pow_10(9) == 1000000000);
  assert(u64_pow_10(15) == 1000000000000000ull);
  assert(u64_pow_10(19) == 10000000000000000000ull);
}

static void _test_u64_log_10() {
  printf("Test u64_log_10\n");
  // this is an expected special case
  assert(u64_log_10(0) == 0);
  assert(u64_log_10(1) == 0);
  assert(u64_log_10(9) == 0);
  assert(u64_log_10(10) == 1);
  assert(u64_log_10(99) == 1);
  assert(u64_log_10(100) == 2);
  assert(u64_log_10(999) == 2);
  assert(u64_log_10(1000) == 3);
  assert(u64_log_10(9999) == 3);
  assert(u64_log_10(10000) == 4);
  assert(u64_log_10(99999) == 4);
  assert(u64_log_10(10000000) == 7);
  assert(u64_log_10(99999999) == 7);
  assert(u64_log_10(100000000) == 8);
  assert(u64_log_10(999999999) == 8);
  assert(u64_log_10(1000000000000000ull) == 15);
  assert(u64_log_10(9999999999999999ull) == 15);
  assert(u64_log_10(1000000000000000000ull) == 18);
  assert(u64_log_10(9999999999999999999ull) == 18);
  assert(u64_log_10(10000000000000000000ull) == 19);
}

static void _test_u64_num_digits() {
  printf("Test u64_num_digits\n");
  assert(u64_num_digits(0) == 1);
  assert(u64_num_digits(1) == 1);
  assert(u64_num_digits(9) == 1);
  assert(u64_num_digits(9999999999999999999ull) == 19);
  assert(u64_num_digits(10000000000000000000ull) == 20);
}


static void _test_u64_divide_by_pow10() {
  printf("Test u64_divide_by_pow10\n");
  // the function rounds up
  assert(u64_divide_by_pow10(1, 0) == 1);
  assert(u64_divide_by_pow10(9876543210987654321ull, 0) == 9876543210987654321ull);
  assert(u64_divide_by_pow10(1, 1) == 0);
  assert(u64_divide_by_pow10(4, 1) == 0);
  assert(u64_divide_by_pow10(5, 1) == 1);
  assert(u64_divide_by_pow10(10, 1) == 1);
  assert(u64_divide_by_pow10(9876543210ull, 1) == 987654321);
  assert(u64_divide_by_pow10(9876543210987654321ull, 18) == 10);
  assert(u64_divide_by_pow10(9876543210987654321ull, 19) == 1);
  assert(u64_divide_by_pow10(14999999999999999999ull, 19) == 1);
  assert(u64_divide_by_pow10(15000000000000000000ull, 19) == 2);
}

static struct decimal _make_decimal(int64_t digits, int32_t exponent, int32_t flags) {
    struct decimal num;
    num.digits = digits;
    num.exponent = exponent;
    num.flags = flags;

    return num;
}

// equals, including exponent and flags
static int32_t _decimal_exact_equals(struct decimal a, struct decimal b) {
    return a.digits == b.digits && a.exponent == b.exponent && a.flags == b.flags;
}

static void _test_scale_decimal_to_fill() {
  printf("Test scale_decimal_to_fill\n");
  assert(_decimal_exact_equals(
    scale_decimal_to_fill(_make_decimal(1, 0, 0)),
    _make_decimal(u64_pow_10(18), -18, 0)
  ));
  assert(_decimal_exact_equals(
    scale_decimal_to_fill(_make_decimal(4321, -2, 0)),
    _make_decimal(4321 * u64_pow_10(15), -17, 0)
  ));
  assert(_decimal_exact_equals(
    scale_decimal_to_fill(_make_decimal(u64_pow_10(19), 0, 0)),
    _make_decimal(u64_pow_10(18), 1, 0)
  ));
  assert(_decimal_exact_equals(
    scale_decimal_to_fill(_make_decimal(u64_pow_10(18) * 15, 0, 0)),
    _make_decimal(u64_pow_10(17) * 15, 1, 0)
  ));
  assert(_decimal_exact_equals(
    scale_decimal_to_fill(_make_decimal(1, 0, VAL_IS_NEG | VAL_IS_FLOAT)),
    _make_decimal(u64_pow_10(18), -18, VAL_IS_NEG | VAL_IS_FLOAT)
  ));
}

static void _test_print_number_item(
  struct decimal num,
  int32_t before_dot,
  int32_t after_dot,
  int32_t exponent_length,
  char *expected,
  size_t expected_length
) {
  char buf[expected_length + 1];
  buf[expected_length] = '\xff';
  size_t print_len = print_number(buf, expected_length, num, before_dot, after_dot, exponent_length);
  assert(print_len == expected_length);
  assert(buf[expected_length] == '\xff');
  assert(memcmp(buf, expected, expected_length) == 0);
}

static void _test_print_number_nonfinite() {
  _test_print_number_item(_make_decimal(0, 0, VAL_IS_INF), 1, 0, 0, "#+inf", 5);
  _test_print_number_item(_make_decimal(0, 0, VAL_IS_INF | VAL_IS_NEG), 1, 0, 0, "#-inf", 5);
  _test_print_number_item(_make_decimal(0, 0, VAL_IS_IND), 1, 0, 0, "#ind", 4);
  _test_print_number_item(_make_decimal(0, 0, VAL_IS_NAN), 1, 0, 0, "#nan", 4);
}

static void _test_print_number_zero() {
  _test_print_number_item(_make_decimal(0, 0, 0), 1, 0, 0, "0", 1);
  _test_print_number_item(_make_decimal(0, 0, 0), 1, 1, 0, "0.0", 3);
  _test_print_number_item(_make_decimal(0, 0, 0), 2, 2, 0, " 0.00", 5);
  _test_print_number_item(_make_decimal(0, 0, VAL_IS_NEG), 2, 2, 0, "-0.00", 5);
  _test_print_number_item(_make_decimal(0, 0, 0), 10, 9, 0, "         0.000000000", 20);
  _test_print_number_item(_make_decimal(0, 0, VAL_IS_NEG), 10, 9, 0, "        -0.000000000", 20);
  _test_print_number_item(_make_decimal(0, 0, 0), 19, 0, 0, "                  0", 19);
  _test_print_number_item(_make_decimal(0, 0, VAL_IS_NEG), 19, 0, 0, "                 -0", 19);
  _test_print_number_item(_make_decimal(0, 0, VAL_IS_NEG), 1, 2, 0, "#.##", 4);
}

static void _test_print_number_zero_exp() {
  _test_print_number_item(_make_decimal(0, 0, 0), 2, 0, 3, " 0E+0", 5);
  _test_print_number_item(_make_decimal(0, 0, 0), 2, 0, 4, " 0E+00", 6);
  _test_print_number_item(_make_decimal(0, 0, 0), 2, 0, 5, " 0E+000", 7);
  _test_print_number_item(_make_decimal(0, 0, 0), 2, 1, 3, " 0.0E+0", 7);
  _test_print_number_item(_make_decimal(0, 0, 0), 3, 2, 4, "  0.00E+00", 10);
  _test_print_number_item(_make_decimal(0, 0, 0), 5, 4, 4, "    0.0000E+00", 14);
  _test_print_number_item(_make_decimal(0, 0, 0), 10, 9, 5, "         0.000000000E+000", 25);
  _test_print_number_item(_make_decimal(0, 0, 0), 2, 17, 5, " 0.00000000000000000E+000", 25);
  _test_print_number_item(_make_decimal(0, 0, 0), 19, 0, 5, "                  0E+000", 24);

  _test_print_number_item(_make_decimal(0, 0, VAL_IS_NEG), 2, 0, 3, "-0E+0", 5);
  _test_print_number_item(_make_decimal(0, 0, VAL_IS_NEG), 2, 0, 4, "-0E+00", 6);
  _test_print_number_item(_make_decimal(0, 0, VAL_IS_NEG), 2, 0, 5, "-0E+000", 7);
  _test_print_number_item(_make_decimal(0, 0, VAL_IS_NEG), 2, 1, 3, "-0.0E+0", 7);
  _test_print_number_item(_make_decimal(0, 0, VAL_IS_NEG), 3, 2, 4, " -0.00E+00", 10);
  _test_print_number_item(_make_decimal(0, 0, VAL_IS_NEG), 5, 4, 4, "   -0.0000E+00", 14);
  _test_print_number_item(_make_decimal(0, 0, VAL_IS_NEG), 10, 9, 5, "        -0.000000000E+000", 25);
  _test_print_number_item(_make_decimal(0, 0, VAL_IS_NEG), 2, 17, 5, "-0.00000000000000000E+000", 25);
  _test_print_number_item(_make_decimal(0, 0, VAL_IS_NEG), 19, 0, 5, "                 -0E+000", 24);
}

static void _test_print_number_overflow() {
  _test_print_number_item(_make_decimal(10, 0, 0), 1, 0, 0, "#", 1);
  _test_print_number_item(_make_decimal(12345678, 0, 0), 1, 0, 0, "#", 1);
  _test_print_number_item(_make_decimal(10, 0, 0), 1, 1, 0, "#.#", 3);
  _test_print_number_item(_make_decimal(10, 0, 0), 1, 18, 0, "#.##################", 20);
  _test_print_number_item(_make_decimal(1, 18, 0), 18, 1, 0, "##################.#", 20);
  _test_print_number_item(_make_decimal(1, 19, 0), 19, 0, 0, "###################", 19);

  _test_print_number_item(_make_decimal(1, 0, VAL_IS_NEG), 1, 0, 0, "#", 1);
  _test_print_number_item(_make_decimal(10, 0, VAL_IS_NEG), 1, 0, 0, "#", 1);
  _test_print_number_item(_make_decimal(12345678, 0, VAL_IS_NEG), 1, 0, 0, "#", 1);
  _test_print_number_item(_make_decimal(1, 0, VAL_IS_NEG), 1, 1, 0, "#.#", 3);
  _test_print_number_item(_make_decimal(10, 0, VAL_IS_NEG), 1, 1, 0, "#.#", 3);
  _test_print_number_item(_make_decimal(1, 0, VAL_IS_NEG), 1, 18, 0, "#.##################", 20);
  _test_print_number_item(_make_decimal(1, 17, VAL_IS_NEG), 18, 1, 0, "##################.#", 20);
  _test_print_number_item(_make_decimal(1, 18, VAL_IS_NEG), 19, 0, 0, "###################", 19);
}

static void _test_print_number_overflow_exp() {
  _test_print_number_item(_make_decimal(1, 10, 0), 2, 0, 3, "##^^^", 5);
  _test_print_number_item(_make_decimal(1, 100, 0), 2, 0, 4, "##^^^^", 6);
  _test_print_number_item(_make_decimal(1, 10, 0), 2, 1, 3, "##.#^^^", 7);
  _test_print_number_item(_make_decimal(1, 100, 0), 2, 17, 4, "##.#################^^^^", 24);

  _test_print_number_item(_make_decimal(1, 10, VAL_IS_NEG), 2, 0, 3, "##^^^", 5);
  _test_print_number_item(_make_decimal(1, 100, VAL_IS_NEG), 2, 0, 4, "##^^^^", 6);

  _test_print_number_item(_make_decimal(1, 11, 0), 3, 0, 3, "###^^^", 6);
  _test_print_number_item(_make_decimal(1, 101, 0), 3, 0, 4, "###^^^^", 7);
  _test_print_number_item(_make_decimal(1, 101, 0), 3, 1, 3, "###.#^^^", 8);
  _test_print_number_item(_make_decimal(1, 101, 0), 3, 16, 4, "###.################^^^^", 24);
}

static void _test_print_number() {
  printf("Test print_number\n");
  _test_print_number_nonfinite();
  _test_print_number_zero();
  _test_print_number_zero_exp();
  _test_print_number_overflow();
  _test_print_number_overflow_exp();
}

int main() {
  _test_i32_pow_10();
  _test_u64_pow_10();
  _test_u64_log_10();
  _test_u64_num_digits();
  _test_u64_divide_by_pow10();
  _test_scale_decimal_to_fill();
  _test_print_number();
  return 0;
}
