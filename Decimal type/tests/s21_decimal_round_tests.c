#include "s21_decimal_test.h"

START_TEST(s21_round_1) {
  s21_decimal dec1 = {{124999, 0, 0, 0}};
  s21_decimal expect = {{124999, 0, 0, 0}};
  s21_decimal result = {{0}};
  s21_round(dec1, &result);

  ck_assert(s21_equals(expect, result));
}
END_TEST

START_TEST(s21_round_2) {
  s21_decimal dec1 = {{124999, 0, 0, 196608}};
  s21_decimal expect = {{125, 0, 0, 0}};
  s21_decimal result = {{0}};
  s21_round(dec1, &result);

  ck_assert(s21_equals(expect, result));
}
END_TEST

START_TEST(s21_round_3) {
  s21_decimal dec1 = {{125001, 0, 0, 196608}};
  s21_decimal expect = {{125, 0, 0, 0}};
  s21_decimal result = {{0}};
  s21_round(dec1, &result);

  ck_assert(s21_equals(expect, result));
}
END_TEST

START_TEST(s21_round_4) {
  s21_decimal dec1 = {{123, 5, 0, 262144}};
  s21_decimal expect = {{2147484, 0, 0, 0}};
  s21_decimal result = {{0}};
  s21_round(dec1, &result);

  ck_assert(s21_equals(expect, result));
}
END_TEST

START_TEST(s21_round_5) {
  s21_decimal dec1 = {{123, 5, 0, 2147483648}};
  s21_decimal expect = {{123, 5, 0, 2147483648}};
  s21_decimal result = {{0}};
  s21_round(dec1, &result);

  ck_assert(s21_equals(expect, result));
}
END_TEST

START_TEST(s21_round_6) {
  s21_decimal dec1 = {{123, 5, 0, 2147745792}};
  s21_decimal expect = {{2147484, 0, 0, 2147483648}};
  s21_decimal result = {{0}};
  s21_round(dec1, &result);

  ck_assert(s21_equals(expect, result));
}
END_TEST

Suite *round_suite(void) {
  Suite *s1 = suite_create("Round");
  TCase *tc1_1 = tcase_create("round");

  tcase_add_test(tc1_1, s21_round_1);
  tcase_add_test(tc1_1, s21_round_2);
  tcase_add_test(tc1_1, s21_round_3);
  tcase_add_test(tc1_1, s21_round_4);
  tcase_add_test(tc1_1, s21_round_5);
  tcase_add_test(tc1_1, s21_round_6);
  suite_add_tcase(s1, tc1_1);

  return s1;
}
