#include "s21_tetris_tests.h"

START_TEST(subtract_matrix_from_field_1) {
  int width = 4;
  int height = 4;
  int **matrix = NULL;
  int **matrix2 = NULL;
  int **matrix_expected = NULL;
  int memory_fail = allocate_matrix(&matrix_expected, width, height);
  ck_assert_int_eq(memory_fail, 0);
  memory_fail = allocate_matrix(&matrix, width, height);
  ck_assert_int_eq(memory_fail, 0);
  memory_fail = allocate_matrix(&matrix2, width, height);
  ck_assert_int_eq(memory_fail, 0);

  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      matrix_expected[i][j] = 0;
      matrix[i][j] = 1;
      matrix2[i][j] = 1;
    }
  }
  subtract_matrix_from_field(matrix, matrix2, 0, 0, width);

  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      ck_assert_int_eq(matrix[i][j], matrix_expected[i][j]);
    }
  }

  free_matrix(&matrix_expected, width);
  free_matrix(&matrix, width);
  free_matrix(&matrix2, width);
}
END_TEST

START_TEST(nullify_matrix_1) {
  int width = 4;
  int height = 4;
  int **matrix = NULL;
  int **matrix_expected = NULL;
  int memory_fail = allocate_matrix(&matrix_expected, width, height);
  ck_assert_int_eq(memory_fail, 0);
  memory_fail = allocate_matrix(&matrix, width, height);
  ck_assert_int_eq(memory_fail, 0);

  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      matrix_expected[i][j] = 0;
      matrix[i][j] = 5;
    }
  }
  nullify_matrix(matrix, width, height, 0, 0);

  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      ck_assert_int_eq(matrix[i][j], matrix_expected[i][j]);
    }
  }

  free_matrix(&matrix_expected, width);
  free_matrix(&matrix, width);
}
END_TEST

START_TEST(multiply_matrix_1) {
  int width = 4;
  int height = 4;
  int **matrix = NULL;
  int **matrix_expected = NULL;
  int memory_fail = allocate_matrix(&matrix_expected, width, height);
  ck_assert_int_eq(memory_fail, 0);
  memory_fail = allocate_matrix(&matrix, width, height);
  ck_assert_int_eq(memory_fail, 0);

  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      matrix_expected[i][j] = 6;
      matrix[i][j] = 3;
    }
  }
  multiply_matrix(matrix, width, 2);

  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      ck_assert_int_eq(matrix[i][j], matrix_expected[i][j]);
    }
  }

  free_matrix(&matrix_expected, width);
  free_matrix(&matrix, width);
}
END_TEST

START_TEST(swap_row_and_column_1) {
  int width = 2;
  int height = 2;
  int **matrix = NULL;
  int **matrix_expected = NULL;
  int memory_fail = allocate_matrix(&matrix_expected, width, height);
  ck_assert_int_eq(memory_fail, 0);
  memory_fail = allocate_matrix(&matrix, width, height);
  ck_assert_int_eq(memory_fail, 0);

  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      matrix_expected[i][j] = 6;
      matrix[i][j] = 6;
    }
  }
  matrix[1][0] = 3;
  matrix_expected[0][1] = 3;

  swap_row_and_column(matrix, width, 0, 0);

  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      ck_assert_int_eq(matrix[i][j], matrix_expected[i][j]);
    }
  }

  free_matrix(&matrix_expected, width);
  free_matrix(&matrix, width);
}
END_TEST

START_TEST(transpose_1) {
  int width = 2;
  int height = 2;
  int **matrix = NULL;
  int **matrix2 = NULL;
  int **matrix_expected = NULL;
  int memory_fail = allocate_matrix(&matrix_expected, width, height);
  ck_assert_int_eq(memory_fail, 0);
  memory_fail = allocate_matrix(&matrix, width, height);
  ck_assert_int_eq(memory_fail, 0);
  memory_fail = allocate_matrix(&matrix2, width, height);
  ck_assert_int_eq(memory_fail, 0);

  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      matrix_expected[i][j] = 1;
      matrix[i][j] = 1;
      matrix2[i][j] = 1;
    }
  }
  matrix2[0][1] = 3;
  matrix_expected[1][0] = 3;
  transpose(matrix, matrix2, width);

  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      ck_assert_int_eq(matrix[i][j], matrix_expected[i][j]);
    }
  }

  free_matrix(&matrix_expected, width);
  free_matrix(&matrix, width);
  free_matrix(&matrix2, width);
}
END_TEST

START_TEST(reverse_rows_1) {
  int width = 2;
  int height = 2;
  int **matrix = NULL;
  int **matrix2 = NULL;
  int **matrix_expected = NULL;
  int memory_fail = allocate_matrix(&matrix_expected, width, height);
  ck_assert_int_eq(memory_fail, 0);
  memory_fail = allocate_matrix(&matrix, width, height);
  ck_assert_int_eq(memory_fail, 0);
  memory_fail = allocate_matrix(&matrix2, width, height);
  ck_assert_int_eq(memory_fail, 0);

  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      matrix_expected[i][j] = 1;
      matrix[i][j] = 1;
      matrix2[i][j] = 1;
    }
  }
  matrix2[1][0] = 3;
  matrix_expected[1][1] = 3;
  reverse_rows(matrix, matrix2, width);

  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      ck_assert_int_eq(matrix[i][j], matrix_expected[i][j]);
    }
  }

  free_matrix(&matrix_expected, width);
  free_matrix(&matrix, width);
  free_matrix(&matrix2, width);
}
END_TEST

START_TEST(shift_to_bottom_1) {
  int width = 4;
  int height = 4;
  int **matrix = NULL;
  int **matrix_expected = NULL;
  int memory_fail = allocate_matrix(&matrix_expected, width, height);
  ck_assert_int_eq(memory_fail, 0);
  memory_fail = allocate_matrix(&matrix, width, height);
  ck_assert_int_eq(memory_fail, 0);

  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      matrix_expected[i][j] = 1;
      matrix[i][j] = 1;
    }
  }
  matrix[1][2] = 3;
  matrix_expected[1][3] = 3;
  shift_to_bottom(matrix, 1, 3, width);

  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      ck_assert_int_eq(matrix[i][j], matrix_expected[i][j]);
    }
  }

  free_matrix(&matrix_expected, width);
  free_matrix(&matrix, width);
}
END_TEST

START_TEST(add_matrix_to_field_1) {
  int width = 2;
  int height = 2;
  int **matrix = NULL;
  int **matrix2 = NULL;
  int **matrix_expected = NULL;
  int memory_fail = allocate_matrix(&matrix_expected, width, height);
  ck_assert_int_eq(memory_fail, 0);
  memory_fail = allocate_matrix(&matrix, width, height);
  ck_assert_int_eq(memory_fail, 0);
  memory_fail = allocate_matrix(&matrix2, width, height);
  ck_assert_int_eq(memory_fail, 0);

  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      matrix_expected[i][j] = 2;
      matrix[i][j] = 0;
      matrix2[i][j] = 2;
    }
  }
  add_matrix_to_field(matrix, matrix2, 0, 0, width);

  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      ck_assert_int_eq(matrix[i][j], matrix_expected[i][j]);
    }
  }

  free_matrix(&matrix_expected, width);
  free_matrix(&matrix, width);
  free_matrix(&matrix2, width);
}
END_TEST

START_TEST(rotate_complex_figure_1) {
  int width = 4;
  int height = 4;
  int **matrix = NULL;
  int **matrix_expected = NULL;
  int memory_fail = allocate_matrix(&matrix_expected, width, height);
  ck_assert_int_eq(memory_fail, 0);
  memory_fail = allocate_matrix(&matrix, width, height);
  ck_assert_int_eq(memory_fail, 0);

  matrix[0][1] = 3;
  matrix_expected[0][1] = 3;
  rotate_complex_figure(matrix, 2, 1, 1);

  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      ck_assert_int_eq(matrix[i][j], matrix_expected[i][j]);
    }
  }

  free_matrix(&matrix_expected, width);
  free_matrix(&matrix, width);
}
END_TEST

START_TEST(rotate_complex_figure_2) {
  int width = 4;
  int height = 4;
  int **matrix = NULL;
  int **matrix_expected = NULL;
  int memory_fail = allocate_matrix(&matrix_expected, width, height);
  ck_assert_int_eq(memory_fail, 0);
  memory_fail = allocate_matrix(&matrix, width, height);
  ck_assert_int_eq(memory_fail, 0);

  matrix[0][0] = 3;
  rotate_complex_figure(matrix, 2, 1, 1);
  matrix[2][2] = 4;
  rotate_complex_figure(matrix, 2, 1, 1);
  matrix[0][2] = 5;
  rotate_complex_figure(matrix, 2, 1, 1);
  matrix_expected[0][0] = 5;
  matrix_expected[1][1] = 4;
  matrix_expected[2][1] = 3;

  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      ck_assert_int_eq(matrix[i][j], matrix_expected[i][j]);
    }
  }

  free_matrix(&matrix_expected, width);
  free_matrix(&matrix, width);
}
END_TEST

START_TEST(rotate_matrix_1) {
  int width = 4;
  int height = 4;
  int **matrix = NULL;
  int **matrix_expected = NULL;
  int memory_fail = allocate_matrix(&matrix_expected, width, height);
  ck_assert_int_eq(memory_fail, 0);
  memory_fail = allocate_matrix(&matrix, width, height);
  ck_assert_int_eq(memory_fail, 0);

  matrix[1][1] = 3;
  matrix[2][2] = 2;
  matrix_expected[1][1] = 2;
  matrix_expected[2][1] = 3;
  rotate_matrix(matrix, 2, 0, 0, COUNTER_CLOCKWISE);
  rotate_matrix(matrix, 2, 0, 0, CLOCKWISE);
  rotate_matrix(matrix, 2, -1, -1, CLOCKWISE);
  rotate_matrix(matrix, 2, 1, 1, COUNTER_CLOCKWISE);

  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      ck_assert_int_eq(matrix[i][j], matrix_expected[i][j]);
    }
  }

  free_matrix(&matrix_expected, width);
  free_matrix(&matrix, width);
}
END_TEST

START_TEST(copy_cubic_matrix_1) {
  int width = 4;
  int height = width;
  int **matrix = NULL;
  int **matrix2 = NULL;
  int **matrix_expected = NULL;
  int memory_fail = allocate_matrix(&matrix_expected, width, height);
  ck_assert_int_eq(memory_fail, 0);
  memory_fail = allocate_matrix(&matrix, width, height);
  ck_assert_int_eq(memory_fail, 0);
  memory_fail = allocate_matrix(&matrix2, width, height);
  ck_assert_int_eq(memory_fail, 0);

  matrix2[1][1] = 3;
  matrix2[0][1] = 3;
  matrix2[2][2] = 4;
  matrix_expected[1][1] = 3;
  matrix_expected[0][1] = 3;
  matrix_expected[2][2] = 4;
  copy_cubic_matrix(matrix, matrix2, width);

  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      ck_assert_int_eq(matrix[i][j], matrix_expected[i][j]);
    }
  }

  free_matrix(&matrix_expected, width);
  free_matrix(&matrix, width);
  free_matrix(&matrix2, width);
}
END_TEST

Suite *matrix_operations_suite(void) {
  Suite *s1 = suite_create("Matrix operations");

  TCase *tc1_1 = tcase_create("subtract_matrix_from_field");
  tcase_add_test(tc1_1, subtract_matrix_from_field_1);

  TCase *tc1_2 = tcase_create("nullify_matrix");
  tcase_add_test(tc1_2, nullify_matrix_1);

  TCase *tc1_3 = tcase_create("multiply_matrix");
  tcase_add_test(tc1_3, multiply_matrix_1);

  TCase *tc1_4 = tcase_create("swap_row_and_column");
  tcase_add_test(tc1_4, swap_row_and_column_1);

  TCase *tc1_5 = tcase_create("transpose");
  tcase_add_test(tc1_5, transpose_1);

  TCase *tc1_6 = tcase_create("reverse_rows");
  tcase_add_test(tc1_6, reverse_rows_1);

  TCase *tc1_7 = tcase_create("shift_to_bottom");
  tcase_add_test(tc1_7, shift_to_bottom_1);

  TCase *tc1_8 = tcase_create("add_matrix_to_field");
  tcase_add_test(tc1_8, add_matrix_to_field_1);

  TCase *tc1_9 = tcase_create("rotate_complex_figure");
  tcase_add_test(tc1_9, rotate_complex_figure_1);
  tcase_add_test(tc1_9, rotate_complex_figure_2);

  TCase *tc1_10 = tcase_create("rotate_matrix");
  tcase_add_test(tc1_10, rotate_matrix_1);

  TCase *tc1_11 = tcase_create("rotate_matrix");
  tcase_add_test(tc1_11, copy_cubic_matrix_1);

  suite_add_tcase(s1, tc1_1);
  suite_add_tcase(s1, tc1_2);
  suite_add_tcase(s1, tc1_3);
  suite_add_tcase(s1, tc1_4);
  suite_add_tcase(s1, tc1_5);
  suite_add_tcase(s1, tc1_6);
  suite_add_tcase(s1, tc1_7);
  suite_add_tcase(s1, tc1_8);
  suite_add_tcase(s1, tc1_9);
  suite_add_tcase(s1, tc1_10);
  suite_add_tcase(s1, tc1_11);

  return s1;
}