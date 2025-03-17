#include "s21_tetris_tests.h"

START_TEST(calculate_score_1) {
  int expected = 200;
  int score = 100;
  calculate_score(&score, 1);
  ck_assert_int_eq(expected, score);
}
END_TEST

START_TEST(calculate_score_2) {
  int score = 100;
  int expected = score + SCORE_FOR_FIRST_LINE * 3;
  calculate_score(&score, 2);
  ck_assert_int_eq(expected, score);

  int score1 = 100;
  int expected1 = score1 + SCORE_FOR_FIRST_LINE * 7;
  calculate_score(&score1, 3);
  ck_assert_int_eq(expected1, score1);

  int score2 = 100;
  int expected2 = score2 + SCORE_FOR_FIRST_LINE * 15;
  calculate_score(&score2, 4);
  ck_assert_int_eq(expected2, score2);
}
END_TEST

START_TEST(calculate_score_3) {
  int score = 0;
  int expected = 8000;
  calculate_score(&score, 5);
  ck_assert_int_eq(expected, score);

  int score1 = 0;
  int expected1 = 0;
  calculate_score(&score1, 0);
  ck_assert_int_eq(expected1, score1);
}
END_TEST

START_TEST(calculate_level_1) {
  int expected = MAX_LEVEL;
  int level = -2;
  int score = 9999999;
  calculate_level(&level, score);
  ck_assert_int_eq(expected, level);
}
END_TEST

Suite *game_stats_suite(void) {
  Suite *s1 = suite_create("Game statistics calculation");

  TCase *tc1_1 = tcase_create("calculate_score");
  tcase_add_test(tc1_1, calculate_score_1);
  tcase_add_test(tc1_1, calculate_score_2);
  tcase_add_test(tc1_1, calculate_score_3);

  TCase *tc1_2 = tcase_create("calculate_level");
  tcase_add_test(tc1_2, calculate_level_1);

  suite_add_tcase(s1, tc1_1);
  suite_add_tcase(s1, tc1_2);

  return s1;
}