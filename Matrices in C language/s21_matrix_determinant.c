#include "s21_matrix.h"

int s21_determinant(matrix_t *A, double *result) {
  int return_code = OK;
  if ((s21_is_valid_matrix(A) && result != NULL) && A->rows == A->columns &&
      !s21_is_inf_or_nan(A)) {
    if (A->rows == 1) {
      *result = A->matrix[0][0];
    } else if (A->rows == 2) {
      *result = s21_determinant_calculation_2x2(A->matrix);
    } else {
      matrix_t tmp;
      s21_create_matrix(A->rows, A->columns, &tmp);
      for (int i = 0; i < A->rows; i++)
        for (int j = 0; j < A->columns; j++) tmp.matrix[i][j] = A->matrix[i][j];
      *result = s21_get_upper_row_determinant(&tmp, A->rows);
      s21_remove_matrix(&tmp);
    }
  } else if (!s21_is_valid_matrix(A))
    return_code = MATRIX_INCORRECT;
  else
    return_code = CALCULATION_INCORRECT;
  return return_code;
}

double s21_get_upper_row_determinant(matrix_t *A, int size) {
  double result = 0.0;
  if (size > 2) {
    double upper_determinant[size];
    matrix_t subA;
    s21_create_matrix(size - 1, size - 1, &subA);
    for (int col = 0; col < size; col++) {
      s21_get_minor_subm(A, &subA, 0, col);
      upper_determinant[col] = s21_get_upper_row_determinant(&subA, size - 1);
    }
    s21_remove_matrix(&subA);
    for (int i = 0; i < size; i++) {
      if (i % 2) A->matrix[0][i] *= -1.0;
      result += A->matrix[0][i] * upper_determinant[i];
    }
  } else {
    result = s21_determinant_calculation_2x2(A->matrix);
  }
  return result;
}

double s21_determinant_calculation_2x2(double **M) {
  double result = (M[0][0] * M[1][1]) - (M[0][1] * M[1][0]);
  return result;
}