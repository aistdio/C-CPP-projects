#include "s21_tetris_tests.h"

START_TEST(addFigure_1) {
  Figures_t figures = {0};
  figures.types_total = -1;
  figures.max_figure_size = DEFAULT_FIGURE_SIZE;
  figures.matrix = calloc(1, sizeof(int **));
  ck_assert_ptr_nonnull(figures.matrix);
  figures.type_sizes = calloc(1, sizeof(int));
  ck_assert_ptr_nonnull(figures.type_sizes);
  int **figure;
  int width = 4;
  int height = width;
  int memory_fail = allocate_matrix(&figure, width, height);
  ck_assert_int_eq(memory_fail, 0);
  int **matrix_expected;
  memory_fail = allocate_matrix(&matrix_expected, width, height);
  ck_assert_int_eq(memory_fail, 0);
  int *anchors = calloc(2, sizeof(int));
  ck_assert_ptr_nonnull(anchors);
  figures.anchors_x = calloc(1, sizeof(int));
  ck_assert_ptr_nonnull(figures.anchors_x);
  figures.anchors_y = calloc(1, sizeof(int));
  ck_assert_ptr_nonnull(figures.anchors_y);

  anchors[anchorX] = 1;
  anchors[anchorY] = 2;
  for (int i = 0, counter = 1; i < width; i++, counter++) {
    for (int j = 0; j < height; j++) {
      figure[i][j] = counter;
      matrix_expected[i][j] = figure[i][j];
    }
  }

  addFigure(&figures, figure, anchors);

  ck_assert_int_eq(figures.anchors_x[0], 1);
  ck_assert_int_eq(figures.anchors_y[0], 2);
  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      ck_assert_int_eq(figures.matrix[0][i][j], matrix_expected[i][j]);
    }
  }

  free_matrix(&figure, width);
  free_matrix(&matrix_expected, width);
  free_matrix(&figures.matrix[0], width);
  free(figures.type_sizes);
  free(figures.matrix);
  free(anchors);
  free(figures.anchors_x);
  free(figures.anchors_y);
}
END_TEST

START_TEST(loadDefaultPattern_1) {
  int **figure;
  int width = DEFAULT_FIGURE_SIZE;
  int height = width;
  int memory_fail = allocate_matrix(&figure, width, height);
  ck_assert_int_eq(memory_fail, 0);
  int *anchors = calloc(2, sizeof(int));
  ck_assert_ptr_nonnull(anchors);

  loadDefaultPattern(0, width, figure, anchors);
  ck_assert_int_eq(anchors[0], -1);
  ck_assert_int_eq(anchors[1], -1);
  ck_assert_int_eq(figure[0][1], 1);
  ck_assert_int_eq(figure[3][1], 1);
  ck_assert_int_eq(figure[3][3], 0);
  loadDefaultPattern(1, width, figure, anchors);
  ck_assert_int_eq(figure[0][1], 1);
  ck_assert_int_eq(figure[2][1], 1);
  ck_assert_int_eq(figure[3][3], 0);
  loadDefaultPattern(2, width, figure, anchors);
  ck_assert_int_eq(figure[0][1], 1);
  ck_assert_int_eq(figure[2][1], 1);
  ck_assert_int_eq(figure[3][3], 0);
  loadDefaultPattern(3, width, figure, anchors);
  ck_assert_int_eq(figure[0][1], 1);
  ck_assert_int_eq(figure[1][1], 1);
  ck_assert_int_eq(figure[3][3], 0);
  loadDefaultPattern(4, width, figure, anchors);
  ck_assert_int_eq(figure[0][2], 1);
  ck_assert_int_eq(figure[1][2], 1);
  ck_assert_int_eq(figure[3][3], 0);
  loadDefaultPattern(5, width, figure, anchors);
  ck_assert_int_eq(figure[0][1], 1);
  ck_assert_int_eq(figure[2][1], 1);
  ck_assert_int_eq(figure[3][3], 0);
  loadDefaultPattern(6, width, figure, anchors);
  ck_assert_int_eq(anchors[0], 1);
  ck_assert_int_eq(anchors[1], 1);
  ck_assert_int_eq(figure[1][2], 1);
  ck_assert_int_eq(figure[2][2], 1);
  ck_assert_int_eq(figure[3][3], 0);

  free_matrix(&figure, width);
  free(anchors);
}
END_TEST

START_TEST(loadDefaultFigures_1) {
  Figures_t figures = {0};
  figures.types_total = -1;
  figures.max_figure_size = DEFAULT_FIGURE_SIZE;
  figures.matrix = calloc(DEFAULT_FIGURES, sizeof(int **));
  ck_assert_ptr_nonnull(figures.matrix);
  figures.type_sizes = calloc(DEFAULT_FIGURES, sizeof(int));
  ck_assert_ptr_nonnull(figures.type_sizes);
  int size = figures.max_figure_size;
  int **matrix_expected;
  int memory_fail = allocate_matrix(&matrix_expected, size, size);
  ck_assert_int_eq(memory_fail, 0);
  int **matrix_expected6;
  memory_fail = allocate_matrix(&matrix_expected6, size, size);
  ck_assert_int_eq(memory_fail, 0);
  figures.anchors_x = calloc(DEFAULT_FIGURES, sizeof(int));
  ck_assert_ptr_nonnull(figures.anchors_x);
  figures.anchors_y = calloc(DEFAULT_FIGURES, sizeof(int));
  ck_assert_ptr_nonnull(figures.anchors_y);

  for (int i = 0; i < size; i++) matrix_expected[i][1] = 1;

  for (int i = 0; i < 2; i++) matrix_expected6[i][1] = 1;
  for (int i = 1; i < 3; i++) matrix_expected6[i][2] = 1;

  loadDefaultFigures(&figures);

  ck_assert_int_eq(figures.type_sizes[0], 4);
  ck_assert_int_eq(figures.type_sizes[6], 3);
  ck_assert_int_eq(figures.anchors_x[0], -1);
  ck_assert_int_eq(figures.anchors_y[0], -1);
  ck_assert_int_eq(figures.anchors_x[6], 1);
  ck_assert_int_eq(figures.anchors_y[6], 1);
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      ck_assert_int_eq(figures.matrix[0][i][j], matrix_expected[i][j]);
      ck_assert_int_eq(figures.matrix[6][i][j], matrix_expected6[i][j]);
    }
  }

  free_matrix(&matrix_expected, size);
  free_matrix(&matrix_expected6, size);
  for (int i = 0; i < DEFAULT_FIGURES; i++) {
    free_matrix(&figures.matrix[i], size);
  }
  free(figures.matrix);
  free(figures.type_sizes);
  free(figures.anchors_x);
  free(figures.anchors_y);
}
END_TEST

START_TEST(figures_singleton_1) {
  Figures_t figures = {0};
  figures.types_total = 7;
  int expected = 7;

  getSetFigures(&figures);

  Figures_t singleton = getSetFigures(NULL);
  ck_assert_int_eq(singleton.types_total, expected);
}
END_TEST

START_TEST(figure_singleton_1) {
  Figure_t memory_check = getSetFigure(NULL, 7);
  ck_assert_ptr_nonnull(memory_check.matrix[6]);

  Figure_t memory_check2 = getSetFigure(NULL, REMOVE);
  ck_assert_ptr_null(memory_check2.matrix);
}
END_TEST

START_TEST(init_Figures_1) {
  int max_figure_size = DEFAULT_FIGURE_SIZE;
  init_Figures(max_figure_size);
  Figures_t result = getSetFigures(NULL);
  ck_assert_ptr_nonnull(result.anchors_x);
  ck_assert_ptr_nonnull(result.anchors_y);
  ck_assert_ptr_nonnull(result.matrix);
  ck_assert_ptr_nonnull(result.type_sizes);
  free(result.anchors_x);
  free(result.anchors_y);
  free(result.type_sizes);
  for (int i = 0; i < DEFAULT_FIGURES; i++) {
    free_matrix(&result.matrix[i], max_figure_size);
  }
  free(result.matrix);
}
END_TEST

START_TEST(remove_Figures_1) {
  int max_figure_size = DEFAULT_FIGURE_SIZE;
  init_Figures(max_figure_size);
  Figures_t result = getSetFigures(NULL);
  remove_Figures(&result);
  ck_assert_ptr_null(result.anchors_x);
  ck_assert_ptr_null(result.anchors_y);
  ck_assert_ptr_null(result.matrix);
  ck_assert_ptr_null(result.type_sizes);
}
END_TEST

START_TEST(spawn_figure_1) {
  int **expected;
  int width = 4;
  int memory_fail = allocate_matrix(&expected, width, width);
  ck_assert_int_eq(memory_fail, 0);
  GameInfo_t gameInfo = {0};
  memory_fail = allocate_matrix(&gameInfo.field, width, width);
  ck_assert_int_eq(memory_fail, 0);

  init_Figures(DEFAULT_FIGURE_SIZE);
  Figures_t figures = getSetFigures(NULL);
  getSetFigure(NULL, DEFAULT_FIGURE_SIZE);
  Figure_t figure = getSetFigure(NULL, NO_ACTION);

  for (int i = 0; i < width; i++) expected[i][1] = 1;

  spawn_figure(&gameInfo, &figures, &figure, 0, 0, 0);

  for (int i = 0; i < width; i++) {
    for (int j = 0; j < width; j++) {
      ck_assert_int_eq(gameInfo.field[i][j], expected[i][j]);
    }
  }

  remove_Figures(&figures);
  getSetFigure(NULL, REMOVE);
  free_matrix(&expected, width);
  free_matrix(&gameInfo.field, width);
}
END_TEST

START_TEST(stopCurrentFigure_1) {
  Figure_t figure = {0};
  figure.is_alive = 1;
  int expected = 0;
  getSetFigure(&figure, NO_ACTION);

  stopCurrentFigure();

  figure = getSetFigure(NULL, NO_ACTION);
  ck_assert_int_eq(figure.is_alive, expected);
}
END_TEST

Suite *figures_suite(void) {
  Suite *s1 = suite_create("Figures");

  TCase *tc1_1 = tcase_create("addFigure_1");
  tcase_add_test(tc1_1, addFigure_1);

  TCase *tc1_2 = tcase_create("loadDefaultPattern");
  tcase_add_test(tc1_2, loadDefaultPattern_1);

  TCase *tc1_3 = tcase_create("loadDefaultFigures");
  tcase_add_test(tc1_3, loadDefaultFigures_1);

  TCase *tc1_4 = tcase_create("figures_singleton");
  tcase_add_test(tc1_4, figures_singleton_1);

  TCase *tc1_5 = tcase_create("figure_singleton");
  tcase_add_test(tc1_5, figure_singleton_1);

  TCase *tc1_6 = tcase_create("init_Figures");
  tcase_add_test(tc1_6, init_Figures_1);

  TCase *tc1_7 = tcase_create("remove_Figures");
  tcase_add_test(tc1_7, remove_Figures_1);

  TCase *tc1_8 = tcase_create("spawn_figure");
  tcase_add_test(tc1_8, spawn_figure_1);

  TCase *tc1_9 = tcase_create("stopCurrentFigure");
  tcase_add_test(tc1_9, stopCurrentFigure_1);

  suite_add_tcase(s1, tc1_1);
  suite_add_tcase(s1, tc1_2);
  suite_add_tcase(s1, tc1_3);
  suite_add_tcase(s1, tc1_4);
  suite_add_tcase(s1, tc1_5);
  suite_add_tcase(s1, tc1_6);
  suite_add_tcase(s1, tc1_7);
  suite_add_tcase(s1, tc1_8);
  suite_add_tcase(s1, tc1_9);

  return s1;
}
