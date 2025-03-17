#include "s21_tetris_tests.h"

START_TEST(validate_data_1_error) {
  GameInfo_t gameInfo = {0};
  gameInfo.high_score = -100;
  int data_fail = validate_data(gameInfo);
  ck_assert_int_eq(data_fail, 1);
}
END_TEST

START_TEST(validate_data_1) {
  GameInfo_t gameInfo = {0};
  gameInfo.high_score = 100;
  int data_fail = validate_data(gameInfo);
  ck_assert_int_eq(data_fail, 0);
}
END_TEST

START_TEST(save_and_load_tetris_db_1) {
  GameInfo_t gameInfo = {0};
  int expected = 500;
  gameInfo.high_score = expected;
  gameInfo.score = 20;
  gameInfo.level = MAX_LEVEL;
  gameInfo.speed = 500;
  int width = 10;
  int height = 20;
  int figure_size = 4;
  int memory_fail_1 =
      allocate_matrix(&gameInfo.field, width, height + MATRIX_V_OFFSET);
  int memory_fail_2 = allocate_matrix(&gameInfo.next, figure_size, figure_size);
  ck_assert_int_eq(memory_fail_1, 0);
  ck_assert_int_eq(memory_fail_2, 0);

  save_tetris_db(gameInfo, width, height);

  free_matrix(&gameInfo.field, width);
  free_matrix(&gameInfo.next, figure_size);

  gameInfo.high_score = 0;

  int db_fail = load_tetris_db(&gameInfo);
  ck_assert_int_eq(db_fail, 0);

  ck_assert_int_eq(gameInfo.high_score, expected);
}
END_TEST

Suite *file_processing_suite(void) {
  Suite *s1 = suite_create("File processing");

  TCase *tc1_1 = tcase_create("validate_data");
  tcase_add_test(tc1_1, validate_data_1_error);
  tcase_add_test(tc1_1, validate_data_1);

  TCase *tc1_2 = tcase_create("save_tetris_db and load_tetris_db");
  tcase_add_test(tc1_2, save_and_load_tetris_db_1);

  suite_add_tcase(s1, tc1_1);
  suite_add_tcase(s1, tc1_2);

  return s1;
}