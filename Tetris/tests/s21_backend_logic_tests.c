#include "s21_tetris_tests.h"

START_TEST(singleton_GameInfo_1) {
  GameInfo_t gameInfo;
  gameInfo.high_score = 100;
  int expected = 100;

  getSetGameInfo(&gameInfo);
  GameInfo_t *result = getSetGameInfo(NULL);

  ck_assert_int_eq(result->high_score, expected);
}
END_TEST

START_TEST(singleton_FieldSize_1) {
  int width = 10;
  int height = width;
  int expected = 10;

  getFieldSize(&width, &height);

  FieldSize_t result = getFieldSize(NULL, NULL);

  ck_assert_int_eq(result.width, expected);
  ck_assert_int_eq(result.height, expected);
}
END_TEST

START_TEST(init_GameInfo_1) {
  GameInfo_t gameInfo;
  int width = 10;
  int height = 20;
  int max_figure_size = 4;
  int speed = 500;
  init_GameInfo(&gameInfo, width, height, max_figure_size, speed);
  ck_assert_ptr_nonnull(gameInfo.field);
  ck_assert_ptr_nonnull(gameInfo.next);
  ck_assert_int_eq(gameInfo.speed, speed);
  free_matrix(&gameInfo.field, width);
  free_matrix(&gameInfo.next, max_figure_size);
  ck_assert_ptr_null(gameInfo.field);
  ck_assert_ptr_null(gameInfo.next);
}
END_TEST

START_TEST(init_backend_1) {
  GameInfo_t gameInfo;
  int width = 10;
  int height = 20;

  init_backend(&gameInfo, width, height);
  ck_assert_int_eq(gameInfo.speed, DEFAULT_USPEED);
  ck_assert_ptr_nonnull(gameInfo.field);
  ck_assert_ptr_nonnull(gameInfo.next);
  Figures_t figures = getSetFigures(NULL);
  ck_assert_int_eq(figures.types_total, DEFAULT_FIGURES - 1);
  ck_assert_ptr_nonnull(figures.matrix);
  ck_assert_ptr_nonnull(figures.anchors_x);
  ck_assert_ptr_nonnull(figures.anchors_y);
  ck_assert_ptr_nonnull(figures.type_sizes);
  Figure_t figure = getSetFigure(NULL, NO_ACTION);
  ck_assert_ptr_nonnull(figure.matrix);

  free_matrix(&gameInfo.field, width);
  free_matrix(&gameInfo.next, DEFAULT_FIGURE_SIZE);
  remove_Figures(&figures);
  getSetFigure(NULL, REMOVE);
}
END_TEST

START_TEST(resetGameInfo_1) {
  GameInfo_t gameInfo;
  int width = 10;
  int height = 20;

  init_backend(&gameInfo, width, height);

  int expected = 0;
  gameInfo.field[5][5] = 1;
  resetGameInfo(&gameInfo);
  ck_assert_int_eq(gameInfo.field[5][5], expected);

  free_matrix(&gameInfo.field, width);
  free_matrix(&gameInfo.next, DEFAULT_FIGURE_SIZE);
  Figures_t figures = getSetFigures(NULL);
  remove_Figures(&figures);
  getSetFigure(NULL, REMOVE);
}
END_TEST

START_TEST(remove_GameInfo_1) {
  GameInfo_t gameInfo;
  int width = 10;
  int height = 20;

  init_GameInfo(&gameInfo, width, height, DEFAULT_FIGURE_SIZE, DEFAULT_USPEED);
  ck_assert_ptr_nonnull(gameInfo.field);
  ck_assert_ptr_nonnull(gameInfo.next);
  remove_GameInfo(width, DEFAULT_FIGURE_SIZE);
  ck_assert_ptr_null(gameInfo.field);
  ck_assert_ptr_null(gameInfo.next);

  free_matrix(&gameInfo.field, width);
  free_matrix(&gameInfo.next, DEFAULT_FIGURE_SIZE);
}
END_TEST

START_TEST(remove_backend_1) {
  GameInfo_t gameInfo;
  int width = 10;
  int height = 20;

  init_backend(&gameInfo, width, height);
  GameInfo_t *result = getSetGameInfo(&gameInfo);
  remove_backend();
  ck_assert_ptr_null(result->field);
  ck_assert_ptr_null(result->next);
}
END_TEST

START_TEST(updateCurrentState_1) {
  GameInfo_t gameInfo;
  int width = 10;
  int height = 20;

  init_backend(&gameInfo, width, height);
  gameInfo.pause = 0;

  Figures_t figures = getSetFigures(NULL);
  Figure_t figure = getSetFigure(NULL, NO_ACTION);
  spawn_figure(&gameInfo, &figures, &figure, 5, 5, 0);
  getSetFigure(&figure, NO_ACTION);

  ck_assert_int_eq(gameInfo.field[5][6], 1);
  ck_assert_int_eq(gameInfo.field[5][7], 0);
  while (gameInfo.field[5][7] != 1) {
    updateCurrentState();
  }
  ck_assert_int_eq(gameInfo.field[5][6], 0);
  ck_assert_int_eq(gameInfo.field[5][7], 1);

  stopCurrentFigure();
  Figure_t figure_res = getSetFigure(NULL, NO_ACTION);
  int expected = 1;

  while (figure_res.is_alive != expected) {
    updateCurrentState();
    figure_res = getSetFigure(NULL, NO_ACTION);
  }
  ck_assert_int_eq(figure.is_alive, expected);

  remove_backend();
}
END_TEST

Suite *backend_logic_suite(void) {
  Suite *s1 = suite_create("Backend logic");

  TCase *tc1_1 = tcase_create("singleton_GameInfo");
  tcase_add_test(tc1_1, singleton_GameInfo_1);

  TCase *tc1_2 = tcase_create("singleton_FieldSize");
  tcase_add_test(tc1_2, singleton_FieldSize_1);

  TCase *tc1_3 = tcase_create("Initialization of GameInfo_t");
  tcase_add_test(tc1_3, init_GameInfo_1);

  TCase *tc1_4 = tcase_create("Initialization of backend");
  tcase_add_test(tc1_4, init_backend_1);

  TCase *tc1_5 = tcase_create("resetGameInfo");
  tcase_add_test(tc1_5, resetGameInfo_1);

  TCase *tc1_6 = tcase_create("remove_GameInfo");
  tcase_add_test(tc1_6, remove_GameInfo_1);

  TCase *tc1_7 = tcase_create("remove_backend");
  tcase_add_test(tc1_7, remove_backend_1);

  TCase *tc1_8 = tcase_create("updateCurrentState");
  tcase_add_test(tc1_8, updateCurrentState_1);

  suite_add_tcase(s1, tc1_1);
  suite_add_tcase(s1, tc1_2);
  suite_add_tcase(s1, tc1_3);
  suite_add_tcase(s1, tc1_4);
  suite_add_tcase(s1, tc1_5);
  suite_add_tcase(s1, tc1_6);
  suite_add_tcase(s1, tc1_7);
  suite_add_tcase(s1, tc1_8);

  return s1;
}