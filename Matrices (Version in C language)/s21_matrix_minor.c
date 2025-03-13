#include "s21_matrix.h"

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int return_code = OK;
  if ((s21_is_valid_matrix(A) && result != NULL) && A->rows == A->columns &&
      !s21_is_inf_or_nan(A)) {
    s21_create_matrix(A->rows, A->columns, result);
    if (A->rows == 1) {
      result->matrix[0][0] = 1.0;
    } else {
      s21_minor_calculation(A, result);
    }
  } else if (!s21_is_valid_matrix(A) || result == NULL)
    return_code = MATRIX_INCORRECT;
  else
    return_code = CALCULATION_INCORRECT;
  return return_code;
}

void s21_minor_calculation(matrix_t *A, matrix_t *result) {
  matrix_t subA;
  s21_create_matrix(A->rows - 1, A->columns - 1, &subA);
  for (int mrow = 0; mrow < A->rows; mrow++) {
    for (int mcol = 0; mcol < A->columns; mcol++) {
      s21_get_minor_subm(A, &subA, mrow, mcol);
      s21_determinant(&subA, &(result->matrix[mrow][mcol]));
      if ((mrow + mcol) % 2 != 0) result->matrix[mrow][mcol] *= -1;
    }
  }
  s21_remove_matrix(&subA);
}

void s21_get_minor_subm(matrix_t *A, matrix_t *subA, int mrow, int mcol) {
  int rowXOR = 0, colXOR = 0;
  for (int row = 0; row < A->rows - 1; row++) {
    for (int col = 0; col < A->columns - 1; col++) {
      if (row == mrow) rowXOR = 1;
      if (col == mcol) colXOR = 1;
      subA->matrix[row][col] = A->matrix[row + rowXOR][col + colXOR];
    }
    colXOR = 0;
  }
}