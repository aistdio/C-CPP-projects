#include "s21_tetris_tests.h"

START_TEST(speed_time_passed_1) {
  int has_enough_time_passed = 0;
  int level = 3;
  int speed = 500;
  while (has_enough_time_passed != 1) {
    has_enough_time_passed = speed_time_passed(level, speed);
  }
  ck_assert_int_eq(has_enough_time_passed, 1);
}
END_TEST

START_TEST(get_random_from_zero_1) {
  int random = get_random_from_zero(5);
  int passed = 0;
  if (random >= 0 && random <= 6) {
    random = get_random_from_zero(5);
    if (random >= 0 && random <= 6) {
      passed = 1;
    }
  }
  ck_assert_int_eq(passed, 1);
}
END_TEST

Suite *time_management_suite(void) {
  Suite *s1 = suite_create("Time management");

  TCase *tc1_1 = tcase_create("speed_time_passed");
  tcase_add_test(tc1_1, speed_time_passed_1);

  TCase *tc1_2 = tcase_create("get_random_from_zero");
  tcase_add_test(tc1_2, get_random_from_zero_1);

  suite_add_tcase(s1, tc1_1);
  suite_add_tcase(s1, tc1_2);

  return s1;
}