#include "s21_tetris_tests.h"

START_TEST(check_bottom_collision_1) {
  int startx = 5;
  int starty = 5;
  int width = 10;
  int height = 20;

  GameInfo_t gameInfoCheck = {0};
  init_backend(&gameInfoCheck, width, height);
  Figures_t figures = getSetFigures(NULL);
  Figure_t figure = getSetFigure(NULL, 0);
  spawn_figure(&gameInfoCheck, &figures, &figure, startx, starty, 0);

  int collided = check_bottom_collision(gameInfoCheck.field, &figures, &figure);
  int expected = 0;
  ck_assert_int_eq(collided, expected);

  figure.is_alive = 0;
  spawn_figure(&gameInfoCheck, &figures, &figure, startx, starty - 1, 0);
  collided = check_bottom_collision(gameInfoCheck.field, &figures, &figure);
  expected = 1;

  remove_backend();
  ck_assert_int_eq(collided, expected);
}
END_TEST

START_TEST(check_left_collision_1) {
  int startx = 5;
  int starty = 5;
  int width = 10;
  int height = 20;

  GameInfo_t gameInfoCheck = {0};
  init_backend(&gameInfoCheck, width, height);
  Figures_t figures = getSetFigures(NULL);
  Figure_t figure = getSetFigure(NULL, 0);
  spawn_figure(&gameInfoCheck, &figures, &figure, startx - 4, starty, 0);

  int collided = check_left_collision(gameInfoCheck.field, &figures, &figure);
  int expected = 0;
  ck_assert_int_eq(collided, expected);

  figure.is_alive = 0;
  spawn_figure(&gameInfoCheck, &figures, &figure, startx, starty, 0);
  collided = check_left_collision(gameInfoCheck.field, &figures, &figure);
  expected = Left;

  remove_backend();
  ck_assert_int_eq(collided, expected);
}
END_TEST

START_TEST(check_right_collision_1) {
  int startx = 5;
  int starty = 5;
  int width = 10;
  int height = 20;

  GameInfo_t gameInfoCheck = {0};
  init_backend(&gameInfoCheck, width, height);
  FieldSize_t fieldSize = getFieldSize(NULL, NULL);
  Figures_t figures = getSetFigures(NULL);
  Figure_t figure = getSetFigure(NULL, 0);
  spawn_figure(&gameInfoCheck, &figures, &figure, startx, starty, 0);

  int collided =
      check_right_collision(gameInfoCheck.field, &fieldSize, &figures, &figure);
  int expected = 0;
  ck_assert_int_eq(collided, expected);

  figure.is_alive = 0;
  spawn_figure(&gameInfoCheck, &figures, &figure, startx - 4, starty, 0);
  collided =
      check_right_collision(gameInfoCheck.field, &fieldSize, &figures, &figure);
  expected = Right;

  remove_backend();
  ck_assert_int_eq(collided, expected);
}
END_TEST

START_TEST(check_sides_collision_1) {
  int startx = 5;
  int starty = 5;
  int width = 10;
  int height = 20;

  GameInfo_t gameInfoCheck = {0};
  init_backend(&gameInfoCheck, width, height);
  Figures_t figures = getSetFigures(NULL);
  Figure_t figure = getSetFigure(NULL, 0);
  spawn_figure(&gameInfoCheck, &figures, &figure, startx, starty, 0);

  int collided = check_sides_collision(gameInfoCheck.field, &figures, &figure);
  int expected = 0;
  ck_assert_int_eq(collided, expected);

  figure.is_alive = 0;
  spawn_figure(&gameInfoCheck, &figures, &figure, startx - 4, starty, 0);
  collided = check_sides_collision(gameInfoCheck.field, &figures, &figure);
  expected = Right;

  remove_backend();
  ck_assert_int_eq(collided, expected);
}
END_TEST

START_TEST(check_rotation_collision_1) {
  int startx = 5;
  int starty = 5;
  int width = 10;
  int height = 20;

  GameInfo_t gameInfoCheck = {0};
  init_backend(&gameInfoCheck, width, height);
  Figures_t figures = getSetFigures(NULL);
  Figure_t figure = getSetFigure(NULL, 0);
  spawn_figure(&gameInfoCheck, &figures, &figure, startx, starty, 0);

  int collided = check_rotation_collision(gameInfoCheck.field, &figures,
                                          &figure, COUNTER_CLOCKWISE);
  int expected = 0;
  ck_assert_int_eq(collided, expected);

  figure.is_alive = 0;
  spawn_figure(&gameInfoCheck, &figures, &figure, startx, starty + 1, 0);
  collided = check_rotation_collision(gameInfoCheck.field, &figures, &figure,
                                      COUNTER_CLOCKWISE);
  expected = 1;

  remove_backend();
  ck_assert_int_eq(collided, expected);
}
END_TEST

START_TEST(deleteAttachedLines_1) {
  int startx = 0;
  int starty = 5;
  int width = 10;
  int height = 20;

  GameInfo_t gameInfoCheck = {0};
  init_backend(&gameInfoCheck, width, height);
  Figures_t figures = getSetFigures(NULL);
  Figure_t figure = getSetFigure(NULL, 0);
  spawn_figure(&gameInfoCheck, &figures, &figure, startx, starty, 0);

  int lines = deleteAttachedLines(&gameInfoCheck);
  int expected = 0;
  ck_assert_int_eq(lines, expected);

  spawn_figure(&gameInfoCheck, &figures, &figure, startx + 4, starty, 0);
  spawn_figure(&gameInfoCheck, &figures, &figure, startx + 6, starty, 0);

  lines = deleteAttachedLines(&gameInfoCheck);
  expected = 1;

  remove_backend();
  ck_assert_int_eq(lines, expected);
}
END_TEST

START_TEST(getMinMaxFilledXY_1) {
  int width = 10;
  int **matrix;
  int memory_fail = allocate_matrix(&matrix, width, width);
  ck_assert_int_eq(memory_fail, 0);

  matrix[0][0] = 1;
  matrix[2][2] = 1;

  int minX = 0, minY = 0, maxX = 0, maxY = 0;
  int expectedMinX = 0;
  int expectedMinY = 0;
  int expectedMaxX = 2;
  int expectedMaxY = 2;

  getMinMaxFilledXY(matrix, width, &minX, &minY, &maxX, &maxY);

  free_matrix(&matrix, width);

  ck_assert_int_eq(expectedMaxX, maxX);
  ck_assert_int_eq(expectedMaxY, maxY);
  ck_assert_int_eq(expectedMinX, minX);
  ck_assert_int_eq(expectedMinY, minY);
}
END_TEST

Suite *matrix_checks_suite(void) {
  Suite *s1 = suite_create("Matrix checks");

  TCase *tc1_1 = tcase_create("check_bottom_collision");
  tcase_add_test(tc1_1, check_bottom_collision_1);

  TCase *tc1_2 = tcase_create("check_left_collision");
  tcase_add_test(tc1_2, check_left_collision_1);

  TCase *tc1_3 = tcase_create("check_right_collision");
  tcase_add_test(tc1_3, check_right_collision_1);

  TCase *tc1_4 = tcase_create("check_sides_collision");
  tcase_add_test(tc1_4, check_sides_collision_1);

  TCase *tc1_5 = tcase_create("check_rotation_collision");
  tcase_add_test(tc1_5, check_rotation_collision_1);

  TCase *tc1_6 = tcase_create("deleteAttachedLines");
  tcase_add_test(tc1_6, deleteAttachedLines_1);

  TCase *tc1_7 = tcase_create("getMinMaxFilledXY");
  tcase_add_test(tc1_7, getMinMaxFilledXY_1);

  suite_add_tcase(s1, tc1_1);
  suite_add_tcase(s1, tc1_2);
  suite_add_tcase(s1, tc1_3);
  suite_add_tcase(s1, tc1_4);
  suite_add_tcase(s1, tc1_5);
  suite_add_tcase(s1, tc1_6);
  suite_add_tcase(s1, tc1_7);

  return s1;
}
