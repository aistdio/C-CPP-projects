#include "s21_decimal_test.h"

START_TEST(first_value_greater_sign_equal_scale_equal) {
  s21_decimal dec1 = {{22, 0, 0, 0}};
  s21_decimal dec2 = {{7, 0, 0, 0}};
  int res = s21_is_greater(dec1, dec2);

  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(first_value_greater_diff_sign_diff_scale) {
  s21_decimal dec1 = {{22, 0, 0, 0x10000}};
  s21_decimal dec2 = {{7, 0, 0, (MINUS)}};
  int res = s21_is_greater(dec1, dec2);

  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(first_value_greater_diff_sign_equal_scale) {
  s21_decimal dec1 = {{22, 0, 0, 0}};
  s21_decimal dec2 = {{7, 0, 0, (MINUS)}};
  int res = s21_is_not_equal(dec1, dec2);

  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(equal_value) {
  s21_decimal dec1 = {{22, 0, 0, 0}};
  s21_decimal dec2 = {{22, 0, 0, 0}};
  int res = s21_is_not_equal(dec1, dec2);

  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(different_value) {
  s21_decimal dec1 = {{0, 2, 0, 0}};
  s21_decimal dec2 = {{22, 0, 0, 0}};
  int res = s21_is_not_equal(dec1, dec2);

  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(is_less_value_1_diff_scale) {
  s21_decimal dec1 = {{0, 0, 1, 0x230000}};
  s21_decimal dec2 = {{0, 1, 0, 0}};
  int res = s21_is_less_or_equal(dec1, dec2);

  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(is_less_or_equal_value_equal) {
  s21_decimal dec1 = {{100, 0, 0, 0x20000}};
  s21_decimal dec2 = {{1, 0, 0, 0}};
  int res = s21_is_less_or_equal(dec1, dec2);

  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(is_greater_or_equal_value_equal) {
  s21_decimal dec1 = {{100, 0, 0, 0x10000}};
  s21_decimal dec2 = {{1, 0, 0, 0}};
  int res = s21_is_greater_or_equal(dec1, dec2);

  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(is_greater_or_equal_value_1_bigger) {
  s21_decimal dec1 = {{10, 0, 0, (MINUS) + 0x10000}};
  s21_decimal dec2 = {{1, 0, 0, (MINUS)}};
  int res = s21_is_greater_or_equal(dec1, dec2);

  ck_assert_int_eq(res, 1);
}
END_TEST

Suite *comparsion_suite(void) {
  Suite *s2 = suite_create("Comparsion");
  TCase *tc2_1 = tcase_create("greater");

  tcase_add_test(tc2_1, first_value_greater_sign_equal_scale_equal);
  tcase_add_test(tc2_1, first_value_greater_diff_sign_diff_scale);
  tcase_add_test(tc2_1, first_value_greater_diff_sign_equal_scale);
  tcase_add_test(tc2_1, equal_value);
  tcase_add_test(tc2_1, different_value);
  tcase_add_test(tc2_1, is_less_value_1_diff_scale);
  tcase_add_test(tc2_1, is_less_or_equal_value_equal);
  tcase_add_test(tc2_1, is_greater_or_equal_value_equal);
  tcase_add_test(tc2_1, is_greater_or_equal_value_1_bigger);
  suite_add_tcase(s2, tc2_1);

  return s2;
}