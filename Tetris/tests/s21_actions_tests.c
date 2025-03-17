#include "s21_tetris_tests.h"

START_TEST(move_down_1) {
  GameInfo_t gameInfo = {0};
  int width = 20;
  int memfail = allocate_matrix(&gameInfo.field, width, width);
  ck_assert_int_eq(memfail, 0);
  init_Figures(DEFAULT_FIGURE_SIZE);
  Figures_t figures = getSetFigures(NULL);
  Figure_t figure = getSetFigure(NULL, DEFAULT_FIGURE_SIZE);

  int expected = 1;
  spawn_figure(&gameInfo, &figures, &figure, 0, 0, 0);
  ck_assert_int_eq(gameInfo.field[0][1], expected);
  ck_assert_int_eq(gameInfo.field[0][2], 0);
  move_down(&gameInfo, &figure);
  ck_assert_int_eq(gameInfo.field[0][1], 0);
  ck_assert_int_eq(gameInfo.field[0][2], expected);

  remove_Figures(&figures);
  getSetFigure(NULL, REMOVE);
  free_matrix(&gameInfo.field, width);
}
END_TEST

START_TEST(move_left_side_1) {
  GameInfo_t gameInfo = {0};
  int width = 20;
  int memfail = allocate_matrix(&gameInfo.field, width, width);
  ck_assert_int_eq(memfail, 0);
  init_Figures(DEFAULT_FIGURE_SIZE);
  Figures_t figures = getSetFigures(NULL);
  Figure_t figure = getSetFigure(NULL, DEFAULT_FIGURE_SIZE);

  int expected = 1;
  spawn_figure(&gameInfo, &figures, &figure, 1, 0, 0);
  ck_assert_int_eq(gameInfo.field[0][1], 0);
  ck_assert_int_eq(gameInfo.field[1][1], expected);
  move_left_side(&gameInfo, &figures, &figure);
  ck_assert_int_eq(gameInfo.field[1][1], expected);
  ck_assert_int_eq(gameInfo.field[0][1], expected);

  remove_Figures(&figures);
  getSetFigure(NULL, REMOVE);
  free_matrix(&gameInfo.field, width);
}
END_TEST

START_TEST(move_right_side_1) {
  GameInfo_t gameInfo = {0};
  int width = 20;
  int memfail = allocate_matrix(&gameInfo.field, width, width);
  ck_assert_int_eq(memfail, 0);
  init_Figures(DEFAULT_FIGURE_SIZE);
  Figures_t figures = getSetFigures(NULL);
  Figure_t figure = getSetFigure(NULL, DEFAULT_FIGURE_SIZE);
  getFieldSize(&width, &width);

  spawn_figure(&gameInfo, &figures, &figure, 5, 5, 0);

  int expected = 1;
  ck_assert_int_eq(gameInfo.field[9][6], 0);
  move_right_side(&gameInfo, &figures, &figure);
  ck_assert_int_eq(gameInfo.field[9][6], expected);

  remove_Figures(&figures);
  getSetFigure(NULL, REMOVE);
  free_matrix(&gameInfo.field, width);
}
END_TEST

START_TEST(rotate_figure_1) {
  GameInfo_t gameInfo = {0};
  int width = 20;
  int memfail = allocate_matrix(&gameInfo.field, width, width);
  ck_assert_int_eq(memfail, 0);
  init_Figures(DEFAULT_FIGURE_SIZE);
  Figures_t figures = getSetFigures(NULL);
  Figure_t figure = getSetFigure(NULL, DEFAULT_FIGURE_SIZE);
  getFieldSize(&width, &width);

  spawn_figure(&gameInfo, &figures, &figure, 5, 5, 0);

  int expected = 1;
  ck_assert_int_eq(gameInfo.field[6][5], 0);
  rotate_figure(&gameInfo, &figures, &figure, COUNTER_CLOCKWISE);
  ck_assert_int_eq(gameInfo.field[6][5], expected);

  remove_Figures(&figures);
  getSetFigure(NULL, REMOVE);
  free_matrix(&gameInfo.field, width);
}
END_TEST

Suite *actions_suite(void) {
  Suite *s1 = suite_create("Actions");

  TCase *tc1_1 = tcase_create("move_down");
  tcase_add_test(tc1_1, move_down_1);

  TCase *tc1_2 = tcase_create("move_left_side");
  tcase_add_test(tc1_2, move_left_side_1);

  TCase *tc1_3 = tcase_create("move_right_side");
  tcase_add_test(tc1_3, move_right_side_1);

  TCase *tc1_4 = tcase_create("rotate_figure");
  tcase_add_test(tc1_4, rotate_figure_1);

  suite_add_tcase(s1, tc1_1);
  suite_add_tcase(s1, tc1_2);
  suite_add_tcase(s1, tc1_3);
  suite_add_tcase(s1, tc1_4);

  return s1;
}
