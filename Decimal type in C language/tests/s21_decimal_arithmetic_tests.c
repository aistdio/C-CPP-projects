#include "s21_decimal_test.h"

// ADDITIONAL

START_TEST(add_when_sign_equal_and_first_value_scale_bigger) {
  s21_decimal dec1 = {{1, 1, 0, 0x00000}};
  s21_decimal dec2 = {{1, 1, 0, 0x10000}};
  s21_decimal expect = {{11, 11, 0, 0x10000}};
  s21_decimal result = {0};
  s21_add(dec1, dec2, &result);

  ck_assert(s21_equals(expect, result));
}
END_TEST

START_TEST(add_when_sign_equal_and_second_value_scale_bigger) {
  s21_decimal dec1 = {{1, 1, 0, 0x10000}};
  s21_decimal dec2 = {{1, 1, 0, 0x00000}};
  s21_decimal expect = {{11, 11, 0, 0x10000}};
  s21_decimal result = {0};
  s21_add(dec1, dec2, &result);

  ck_assert(s21_equals(expect, result));
}
END_TEST

START_TEST(add_when_sign_not_equal_first_value_bigger) {
  s21_decimal dec1 = {{119, 2, 0, 0x00000}};
  s21_decimal dec2 = {{21, 1, 0, MINUS}};
  s21_decimal expect = {{98, 1, 0, 0}};
  s21_decimal result = {0};
  s21_add(dec1, dec2, &result);

  ck_assert(s21_equals(expect, result));
}
END_TEST

START_TEST(add_when_sign_not_equal_second_value_bigger) {
  s21_decimal dec1 = {{21, 1, 0, 0x00000}};
  s21_decimal dec2 = {{119, 2, 0, MINUS}};
  s21_decimal expect = {{98, 1, 0, MINUS}};
  s21_decimal result = {0};
  s21_add(dec1, dec2, &result);

  ck_assert(s21_equals(expect, result));
}
END_TEST

// SUBTRACTOIN
START_TEST(sub_when_sign_equal_first_value_scale_bigger) {
  s21_decimal dec1 = {{1, 1, 1, 0}};
  s21_decimal dec2 = {{1, 1, 1, 0x10000}};
  s21_decimal expect = {{9, 9, 9, 0x10000}};
  s21_decimal result = {0};
  s21_sub(dec1, dec2, &result);

  ck_assert(s21_equals(expect, result));
}
END_TEST

START_TEST(sub_when_sign_equal_second_value_scale_bigger) {
  s21_decimal dec1 = {{1, 1, 1, 0x10000}};
  s21_decimal dec2 = {{8, 8, 8, 0}};
  s21_decimal expect = {{79, 79, 79, 0x80010000}};
  s21_decimal result = {0};
  s21_sub(dec1, dec2, &result);

  ck_assert(s21_equals(expect, result));
}
END_TEST

START_TEST(sub_when_sign_equal_first_value_bigger) {
  s21_decimal dec1 = {{1, BIT32, 1, 0}};
  s21_decimal dec2 = {{1, BIT32, 0, 0}};
  s21_decimal expect = {{0, 0, 1, 0}};
  s21_decimal result = {0};
  s21_sub(dec1, dec2, &result);

  ck_assert(s21_equals(expect, result));
}
END_TEST

START_TEST(sub_when_sign_equal_second_value_bigger) {
  s21_decimal dec1 = {{1, 0, 0, 0}};
  s21_decimal dec2 = {{0, 1, 0, 0}};
  s21_decimal expect = {{BIT32, 0, 0, 0x80000000}};
  s21_decimal result = {0};
  s21_sub(dec1, dec2, &result);

  ck_assert(s21_equals(expect, result));
}
END_TEST

START_TEST(sub_when_sign_dif) {
  s21_decimal dec1 = {{1, 0, 0, MINUS}};
  s21_decimal dec2 = {{BIT32, 1, 0, 0}};
  s21_decimal expect = {{0, 2, 0, MINUS}};
  s21_decimal result = {0};
  s21_sub(dec1, dec2, &result);

  ck_assert(s21_equals(expect, result));
}
END_TEST

// MULTIPLY
START_TEST(mul_one_equal_sign_equal_scale) {
  s21_decimal dec1 = {{1, 0, 0, 0x80000000}};
  s21_decimal dec2 = {{1, 0, 0, 0x80000000}};
  s21_decimal expect = {{1, 0, 0, 0}};
  s21_decimal result = {0};
  s21_mul(dec1, dec2, &result);

  ck_assert(s21_equals(expect, result));
}
END_TEST

START_TEST(mul_one_diff_sign_diff_scale) {
  s21_decimal dec1 = {{1, 0, 0, 0x30000}};
  s21_decimal dec2 = {{1, 0, 0, 0x80030000}};
  s21_decimal expect = {{1, 0, 0, 0x80060000}};
  s21_decimal result = {0};
  s21_mul(dec1, dec2, &result);

  ck_assert(s21_equals(expect, result));
}
END_TEST

START_TEST(mul_big_num_equal_sign_diff_scale) {
  s21_decimal dec1 = {{2147483648, 0, 0, 0x80000000}};
  s21_decimal dec2 = {{2, 0, 0, 0x80030000}};
  s21_decimal expect = {{0, 1, 0, 0x30000}};
  s21_decimal result = {0};
  s21_mul(dec1, dec2, &result);

  ck_assert(s21_equals(expect, result));
}
END_TEST

// DIVISOIN
START_TEST(div_one_equal_sign_equal_scale) {
  s21_decimal dec1 = {{1, 0, 0, 0}};
  s21_decimal dec2 = {{1, 0, 0, 0}};
  s21_decimal expect = {{1, 0, 0, 0}};
  s21_decimal result = {0};
  s21_div(dec1, dec2, &result);

  ck_assert(s21_equals(expect, result));
}
END_TEST

START_TEST(div_one_diff_sign_diff_scale) {
  s21_decimal dec1 = {{1, 0, 0, 0x80000000}};
  s21_decimal dec2 = {{1, 0, 0, 0x10000}};
  s21_decimal expect = {{10, 0, 0, 0x80000000}};
  s21_decimal result = {0};
  s21_div(dec1, dec2, &result);

  ck_assert(s21_equals(expect, result));
}
END_TEST

START_TEST(div_one_equal_sign_second_num_bigger) {
  s21_decimal dec1 = {{10, 0, 0, 0}};
  s21_decimal dec2 = {{100, 0, 0, 0}};
  s21_decimal expect = {{1, 0, 0, 0x10000}};
  s21_decimal result = {0};
  s21_div(dec1, dec2, &result);

  ck_assert(s21_equals(expect, result));
}
END_TEST

START_TEST(div_34_8) {
  s21_decimal dec1 = {{34, 0, 0, 0}};
  s21_decimal dec2 = {{8, 0, 0, 0}};
  s21_decimal expect = {{425, 0, 0, 0x20000}};
  s21_decimal result = {{0}};
  s21_div(dec1, dec2, &result);

  ck_assert(s21_equals(expect, result));
}
END_TEST

START_TEST(div_22_7) {
  s21_decimal dec1 = {{22, 0, 0, 0}};
  s21_decimal dec2 = {{7, 0, 0, 0}};
  s21_decimal expect = {{3297921316, 208949406, 1703746271, 0x1C0000}};
  s21_decimal result = {0};
  s21_div(dec1, dec2, &result);

  ck_assert(s21_equals(expect, result));
}
END_TEST

Suite *arithmetic_suite(void) {
  Suite *s1 = suite_create("Arithmetic");
  TCase *tc1_1 = tcase_create("addition");
  TCase *tc1_2 = tcase_create("subtraction");
  TCase *tc1_3 = tcase_create("multiply");
  TCase *tc1_4 = tcase_create("division");

  tcase_add_test(tc1_1, add_when_sign_equal_and_first_value_scale_bigger);
  tcase_add_test(tc1_1, add_when_sign_equal_and_first_value_scale_bigger);
  tcase_add_test(tc1_1, add_when_sign_equal_and_second_value_scale_bigger);
  tcase_add_test(tc1_1, add_when_sign_not_equal_first_value_bigger);
  tcase_add_test(tc1_1, add_when_sign_not_equal_second_value_bigger);
  suite_add_tcase(s1, tc1_1);

  tcase_add_test(tc1_2, sub_when_sign_equal_first_value_scale_bigger);
  tcase_add_test(tc1_2, sub_when_sign_equal_second_value_scale_bigger);
  tcase_add_test(tc1_2, sub_when_sign_equal_first_value_bigger);
  tcase_add_test(tc1_2, sub_when_sign_equal_second_value_bigger);
  tcase_add_test(tc1_2, sub_when_sign_dif);
  suite_add_tcase(s1, tc1_2);

  tcase_add_test(tc1_3, mul_one_equal_sign_equal_scale);
  tcase_add_test(tc1_3, mul_one_diff_sign_diff_scale);
  tcase_add_test(tc1_3, mul_big_num_equal_sign_diff_scale);
  suite_add_tcase(s1, tc1_3);

  tcase_add_test(tc1_4, div_one_equal_sign_equal_scale);
  tcase_add_test(tc1_4, div_one_diff_sign_diff_scale);
  tcase_add_test(tc1_4, div_one_equal_sign_second_num_bigger);
  tcase_add_test(tc1_4, div_34_8);
  tcase_add_test(tc1_4, div_22_7);
  suite_add_tcase(s1, tc1_4);

  return s1;
}