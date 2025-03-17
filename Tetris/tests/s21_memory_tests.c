#include "s21_tetris_tests.h"

START_TEST(matrix_free_error_1) {
  int **matrix = NULL;
  free_matrix(&matrix, 0);
  ck_assert_ptr_null(matrix);
}
END_TEST

START_TEST(matrix_memory_error_1) {
  int error = allocate_matrix(NULL, 0, 0);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(matrix_memory_error_2) {
  int **matrix = NULL;
  int error = allocate_matrix(&matrix, 0, 0);
  ck_assert_int_eq(error, 1);
  ck_assert_ptr_null(matrix);
}
END_TEST

START_TEST(matrix_memory_1) {
  int **matrix = NULL;
  int width = 3;
  int height = 3;
  int error = allocate_matrix(&matrix, width, height);
  ck_assert_int_eq(error, 0);
  ck_assert_ptr_nonnull(matrix);
  free_matrix(&matrix, width);
}
END_TEST

START_TEST(matrix_free_1) {
  int **matrix = NULL;
  int width = 3;
  int height = 3;
  int error = allocate_matrix(&matrix, width, height);
  ck_assert_int_eq(error, 0);
  free_matrix(&matrix, width);
  ck_assert_ptr_null(matrix);
  error = allocate_matrix(&matrix, width, height);
  ck_assert_int_eq(error, 0);
  free(matrix[width - 1]);
  matrix[width - 1] = NULL;
  free_matrix(&matrix, width);
  ck_assert_ptr_null(matrix);
}
END_TEST

Suite *memory_suite(void) {
  Suite *s1 = suite_create("Memory");

  TCase *tc1_1 = tcase_create("free_matrix()");
  tcase_add_test(tc1_1, matrix_free_error_1);
  tcase_add_test(tc1_1, matrix_free_1);

  TCase *tc1_2 = tcase_create("allocate_matrix()");
  tcase_add_test(tc1_2, matrix_memory_error_1);
  tcase_add_test(tc1_2, matrix_memory_error_2);
  tcase_add_test(tc1_2, matrix_memory_1);

  suite_add_tcase(s1, tc1_1);
  suite_add_tcase(s1, tc1_2);

  return s1;
}