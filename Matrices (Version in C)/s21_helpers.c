#include "s21_matrix.h"

void s21_calculate_matrix_mult(const matrix_t *A, const matrix_t *B,
                               matrix_t *result) {
  for (int row1 = 0, row2 = 0; row1 < A->rows; row1++, row2++)
    for (int col1 = 0, col3 = 0; col1 < B->columns; col1++, col3++)
      for (int col2 = 0, row3 = 0; col2 < A->columns; col2++, row3++)
        result->matrix[row1][col1] +=
            A->matrix[row2][col2] * B->matrix[row3][col3];
}

int s21_matrix_size_eq(const matrix_t *A, const matrix_t *B) {
  return (A->columns == B->columns && A->rows == B->rows);
}

void s21_add_number(matrix_t *A, const double number) {
  for (int i = 0; i < A->rows; i++)
    for (int j = 0; j < A->columns; j++) A->matrix[i][j] += number;
}

int s21_is_valid_matrix(const matrix_t *A) {
  return (!(A == NULL || A->rows < 1 || A->columns < 1));
}

int s21_is_inf_or_nan(const matrix_t *A) {
  int return_code = 0;
  for (int i = 0; i < A->rows && !return_code; i++)
    for (int j = 0; j < A->columns && !return_code; j++)
      if (isinf(A->matrix[i][j]) || isnan(A->matrix[i][j])) return_code = 1;
  return return_code;
}