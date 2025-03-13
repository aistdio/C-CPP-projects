#include "s21_decimal_test.h"

START_TEST(flt_to_dec_default) {
  float f = 123.456789;
  s21_decimal d;
  s21_decimal expect = {{1234568, 0, 0, 4 << 16}};

  ck_assert_int_eq(s21_from_float_to_decimal(f, &d), 0);
  ck_assert(s21_equals(expect, d));
}
END_TEST

START_TEST(flt_to_dec_negative_default) {
  float f = -123.456789;
  s21_decimal d;
  s21_decimal expect = {{1234568, 0, 0, (4 << 16) + (1 << 31)}};

  ck_assert_int_eq(s21_from_float_to_decimal(f, &d), 0);
  ck_assert(s21_equals(expect, d));
}
END_TEST

START_TEST(flt_to_dec_leading_zeroes) {
  float f = 0.00123456789;
  s21_decimal d;
  s21_decimal expect = {{1234568, 0, 0, 9 << 16}};

  ck_assert_int_eq(s21_from_float_to_decimal(f, &d), 0);

  ck_assert(s21_equals(expect, d));
}
END_TEST

START_TEST(flt_to_dec_negative_leading_zeroes) {
  float f = -0.00123456789;
  s21_decimal d;
  s21_decimal expect = {{1234568, 0, 0, (9 << 16) + (1 << 31)}};

  ck_assert_int_eq(s21_from_float_to_decimal(f, &d), 0);

  ck_assert(s21_equals(expect, d));
}
END_TEST

START_TEST(flt_to_dec_negative_leading_zeroes_too_small) {
  float f = -1.0 * 1e-28;
  s21_decimal d;
  s21_decimal expect = {{1, 0, 0, (28 << 16) + (1 << 31)}};

  ck_assert_int_eq(s21_from_float_to_decimal(f, &d), 0);

  ck_assert(s21_equals(expect, d));
}
END_TEST

START_TEST(flt_to_dec_negative_leading_zeroes_too_small_incorrect) {
  float f = -1.0 * 1e-29;
  s21_decimal d;
  s21_decimal expect = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_from_float_to_decimal(f, &d), 1);

  ck_assert(s21_equals(expect, d));
}
END_TEST

START_TEST(flt_to_dec_NaN_incorrect) {
  float float_NaN = 0.0f / 0.0f;
  s21_decimal d;

  ck_assert_int_eq(s21_from_float_to_decimal(float_NaN, &d), 1);
}
END_TEST

START_TEST(flt_to_dec_infinity_incorrect) {
  float f = INFINITY;
  s21_decimal d;

  ck_assert_int_eq(s21_from_float_to_decimal(f, &d), 1);
}
END_TEST

START_TEST(flt_to_dec_negative_infinity_incorrect) {
  float f = -(INFINITY);
  s21_decimal d;

  ck_assert_int_eq(s21_from_float_to_decimal(f, &d), 1);
}
END_TEST

START_TEST(flt_to_dec_float_too_big_incorrect) {
  float f = (float)792281625142643375935439503367.0;
  s21_decimal d;

  ck_assert_int_eq(s21_from_float_to_decimal(f, &d), 1);
}
END_TEST

START_TEST(test_from_decimal_to_int_null) {
  s21_decimal src = {0};
  int *dst = NULL;
  int result = s21_from_decimal_to_int(src, dst);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_from_decimal_to_int_positive) {
  s21_decimal src = {0};
  src.bits[0] = 12345;
  src.bits[3] = 0;
  int dst = 0;
  int result = s21_from_decimal_to_int(src, &dst);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(dst, 12345);
}
END_TEST

START_TEST(test_from_decimal_to_int_negative) {
  s21_decimal src = {0};
  src.bits[0] = 12345;
  src.bits[3] = 0x80000000;
  int dst = 0;
  int result = s21_from_decimal_to_int(src, &dst);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(dst, -12345);
}
END_TEST

START_TEST(test_from_decimal_to_int_overflow_positive) {
  s21_decimal src = {0};
  src.bits[0] = INT_MAX;
  src.bits[0] += 1;
  src.bits[3] = 0;
  int dst = 0;
  int result = s21_from_decimal_to_int(src, &dst);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(dst, INT_MAX);
}
END_TEST

START_TEST(test_from_decimal_to_int_overflow_negative) {
  s21_decimal src = {0};
  src.bits[0] = (unsigned int)INT_MAX + 1;
  src.bits[3] = 0x80000000;
  int dst = 0;
  int result = s21_from_decimal_to_int(src, &dst);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(dst, INT_MIN);
}
END_TEST

START_TEST(test_from_decimal_to_int_large_number) {
  s21_decimal src = {0};
  src.bits[0] = 123456789;
  src.bits[1] = 1;
  src.bits[3] = 0;
  int dst = 0;
  int result = s21_from_decimal_to_int(src, &dst);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(dst, INT_MAX);
}
END_TEST

START_TEST(test_from_int_to_decimal_null) {
  int src = 12345;
  s21_decimal *dst = NULL;
  int result = s21_from_int_to_decimal(src, dst);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_from_int_to_decimal_positive) {
  int src = 12345;
  s21_decimal dst = {0};
  int result = s21_from_int_to_decimal(src, &dst);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(dst.bits[0], 12345);
  ck_assert_int_eq(dst.bits[3], 0);
}
END_TEST

START_TEST(test_from_int_to_decimal_negative) {
  int src = -12345;
  s21_decimal dst = {0};
  int result = s21_from_int_to_decimal(src, &dst);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(dst.bits[0], 12345);
  ck_assert_uint_eq(dst.bits[3], 0x80000000);
}
END_TEST

START_TEST(test_from_int_to_decimal_zero) {
  int src = 0;
  s21_decimal dst = {0};
  int result = s21_from_int_to_decimal(src, &dst);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(dst.bits[0], 0);
  ck_assert_int_eq(dst.bits[3], 0);
}
END_TEST

START_TEST(test_from_int_to_decimal_int_max) {
  int src = INT_MAX;
  s21_decimal dst = {0};
  int result = s21_from_int_to_decimal(src, &dst);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(dst.bits[0], INT_MAX);
  ck_assert_int_eq(dst.bits[3], 0);
}
END_TEST

START_TEST(test_from_int_to_decimal_int_min) {
  int src = INT_MIN;
  s21_decimal dst = {0};
  int result = s21_from_int_to_decimal(src, &dst);
  ck_assert_int_eq(result, 0);
  ck_assert_uint_eq(dst.bits[0], (unsigned int)INT_MAX + 1);
  ck_assert_uint_eq(dst.bits[3], 0x80000000);
}
END_TEST

START_TEST(test_from_decimal_to_float_null) {
  s21_decimal src = {0};
  float *dst = NULL;
  int result = s21_from_decimal_to_float(src, dst);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_from_decimal_to_float_positive) {
  s21_decimal src = {0};
  src.bits[0] = 12345;
  src.bits[3] = 0;
  float dst = 0;
  int result = s21_from_decimal_to_float(src, &dst);
  ck_assert_int_eq(result, 0);

  ck_assert_float_eq(dst, 12345.0f);
}
END_TEST

START_TEST(test_from_decimal_to_float_negative) {
  s21_decimal src = {0};
  src.bits[0] = 12345;
  src.bits[3] = 0x80000000;
  float dst = 0;
  int result = s21_from_decimal_to_float(src, &dst);
  ck_assert_int_eq(result, 0);
  ck_assert_float_eq(dst, -12345.0f);
}
END_TEST

START_TEST(test_from_decimal_to_float_with_scale) {
  s21_decimal src = {0};
  src.bits[0] = 123456789;
  src.bits[3] = 2 << 16;
  float dst = 0;
  int result = s21_from_decimal_to_float(src, &dst);
  ck_assert_int_eq(result, 0);

  ck_assert_float_eq(dst, 1234568.0f);
}
END_TEST

START_TEST(test_from_decimal_to_float_large_number) {
  s21_decimal src = {0};
  src.bits[0] = 123456789;
  src.bits[1] = 1;
  src.bits[3] = 0;
  float dst = 0;
  float expected = (123456789.0f + pow(2, 32));
  int result = s21_from_decimal_to_float(src, &dst);
  ck_assert_int_eq(result, 0);

  dst /= 1000.0f;
  expected /= 1000.0f;

  dst = truncf(dst);
  expected = truncf(expected);

  ck_assert_float_eq(expected, dst);
}
END_TEST

START_TEST(test_from_decimal_to_float_invalid_scale) {
  s21_decimal src = {0};
  src.bits[0] = 12345;
  src.bits[3] = 29 << 16;
  float dst = 0;
  int result = s21_from_decimal_to_float(src, &dst);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(dec_to_flt_leading_zeroes) {
  float f;
  s21_decimal d = {{1234568, 0, 0, 9 << 16}};
  float expect = 0.001234568;

  ck_assert_int_eq(s21_from_decimal_to_float(d, &f), 0);

  ck_assert_float_eq(expect, f);
}
END_TEST

START_TEST(dec_to_flt_negative_leading_zeroes) {
  float f;
  s21_decimal d = {{1234568, 0, 0, (9 << 16) + (1 << 31)}};
  float expect = -0.001234568;

  ck_assert_int_eq(s21_from_decimal_to_float(d, &f), 0);
  ck_assert_float_eq(expect, f);
}
END_TEST

START_TEST(test_negate_positive) {
  s21_decimal value = {0};
  value.bits[0] = 12345;
  value.bits[3] = 0;
  s21_decimal result = {0};
  int error = s21_negate(value, &result);
  ck_assert_int_eq(error, 0);
  ck_assert_int_eq(result.bits[0], 12345);
  ck_assert_uint_eq(result.bits[3], 0x80000000);
}
END_TEST

START_TEST(test_negate_negative) {
  s21_decimal value = {0};
  value.bits[0] = 12345;
  value.bits[3] = 0x80000000;
  s21_decimal result = {0};
  int error = s21_negate(value, &result);
  ck_assert_int_eq(error, 0);
  ck_assert_int_eq(result.bits[0], 12345);
  ck_assert_uint_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_negate_zero) {
  s21_decimal value = {0};
  value.bits[0] = 0;
  value.bits[3] = 0;
  s21_decimal result = {0};
  int error = s21_negate(value, &result);
  ck_assert_int_eq(error, 0);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_uint_eq(result.bits[3], 0x80000000);
}
END_TEST

START_TEST(test_negate_null) {
  s21_decimal value = {0};
  value.bits[0] = 12345;
  value.bits[3] = 0;
  int error = s21_negate(value, NULL);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(test_negate_large_number) {
  s21_decimal value = {0};
  value.bits[0] = 123456789;
  value.bits[1] = 1;
  value.bits[3] = 0;
  s21_decimal result = {0};
  int error = s21_negate(value, &result);
  ck_assert_int_eq(error, 0);
  ck_assert_int_eq(result.bits[0], 123456789);
  ck_assert_int_eq(result.bits[1], 1);
  ck_assert_uint_eq(result.bits[3], 0x80000000);
}
END_TEST

START_TEST(truncate_null) {
  s21_decimal *d = NULL;
  s21_decimal expect = {{1234568, 0, 0, (9 << 16) + (1 << 31)}};

  ck_assert_int_eq(s21_truncate(expect, d), 1);
}
END_TEST

START_TEST(truncate_positive) {
  s21_decimal d = {{1234568, 0, 0, 4 << 16}};
  s21_decimal expect = {{123, 0, 0, 0}};

  ck_assert_int_eq(s21_truncate(d, &d), 0);

  ck_assert(s21_equals(expect, d));
}
END_TEST

START_TEST(truncate_negative) {
  s21_decimal d = {{1234568, 0, 0, (4 << 16) + (1 << 31)}};
  s21_decimal expect = {{123, 0, 0, 1 << 31}};

  ck_assert_int_eq(s21_truncate(d, &d), 0);
  ck_assert(s21_equals(expect, d));
}
END_TEST

START_TEST(leading_zeroes_negative) {
  s21_decimal d = {{1234568, 0, 0, (16 << 16) + (1 << 31)}};
  s21_decimal expect = {{0, 0, 0, 1 << 31}};

  ck_assert_int_eq(s21_truncate(d, &d), 0);
  ck_assert(s21_equals(expect, d));
}
END_TEST

Suite *conversion_suite(void) {
  Suite *s1 = suite_create("Conversion");
  TCase *tc1_1 = tcase_create("FloatToDecimal");
  TCase *tc1_2 = tcase_create("DecimalToFloat");
  TCase *tc1_3 = tcase_create("IntToDecimal");
  TCase *tc1_4 = tcase_create("DecimalToInt");
  TCase *tc1_5 = tcase_create("Negate");
  TCase *tc1_6 = tcase_create("Truncate");

  tcase_add_test(tc1_1, flt_to_dec_default);
  tcase_add_test(tc1_1, flt_to_dec_negative_default);
  tcase_add_test(tc1_1, flt_to_dec_leading_zeroes);
  tcase_add_test(tc1_1, flt_to_dec_negative_leading_zeroes);
  tcase_add_test(tc1_1, flt_to_dec_negative_leading_zeroes_too_small);
  tcase_add_test(tc1_1, flt_to_dec_negative_leading_zeroes_too_small_incorrect);
  tcase_add_test(tc1_1, flt_to_dec_NaN_incorrect);
  tcase_add_test(tc1_1, flt_to_dec_infinity_incorrect);
  tcase_add_test(tc1_1, flt_to_dec_negative_infinity_incorrect);
  tcase_add_test(tc1_1, flt_to_dec_float_too_big_incorrect);

  tcase_add_test(tc1_2, dec_to_flt_leading_zeroes);
  tcase_add_test(tc1_2, dec_to_flt_negative_leading_zeroes);
  tcase_add_test(tc1_2, test_from_decimal_to_float_null);
  tcase_add_test(tc1_2, test_from_decimal_to_float_positive);
  tcase_add_test(tc1_2, test_from_decimal_to_float_negative);
  tcase_add_test(tc1_2, test_from_decimal_to_float_with_scale);
  tcase_add_test(tc1_2, test_from_decimal_to_float_large_number);
  tcase_add_test(tc1_2, test_from_decimal_to_float_invalid_scale);

  tcase_add_test(tc1_3, test_from_int_to_decimal_null);
  tcase_add_test(tc1_3, test_from_int_to_decimal_positive);
  tcase_add_test(tc1_3, test_from_int_to_decimal_negative);
  tcase_add_test(tc1_3, test_from_int_to_decimal_zero);
  tcase_add_test(tc1_3, test_from_int_to_decimal_int_max);
  tcase_add_test(tc1_3, test_from_int_to_decimal_int_min);

  tcase_add_test(tc1_4, test_from_decimal_to_int_null);
  tcase_add_test(tc1_4, test_from_decimal_to_int_positive);
  tcase_add_test(tc1_4, test_from_decimal_to_int_negative);
  tcase_add_test(tc1_4, test_from_decimal_to_int_overflow_positive);
  tcase_add_test(tc1_4, test_from_decimal_to_int_overflow_negative);
  tcase_add_test(tc1_4, test_from_decimal_to_int_large_number);

  tcase_add_test(tc1_5, test_negate_positive);
  tcase_add_test(tc1_5, test_negate_negative);
  tcase_add_test(tc1_5, test_negate_zero);
  tcase_add_test(tc1_5, test_negate_null);
  tcase_add_test(tc1_5, test_negate_large_number);

  tcase_add_test(tc1_6, truncate_null);
  tcase_add_test(tc1_6, truncate_positive);
  tcase_add_test(tc1_6, truncate_negative);
  tcase_add_test(tc1_6, leading_zeroes_negative);

  suite_add_tcase(s1, tc1_1);
  suite_add_tcase(s1, tc1_2);
  suite_add_tcase(s1, tc1_3);
  suite_add_tcase(s1, tc1_4);
  suite_add_tcase(s1, tc1_4);
  suite_add_tcase(s1, tc1_5);
  suite_add_tcase(s1, tc1_6);

  return s1;
}
