#include "s21_matrix.h"

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int result = SUCCESS;
  if (s21_is_valid_matrix(A) && s21_is_valid_matrix(B) &&
      s21_matrix_size_eq(A, B)) {
    for (int i = 0; i < A->rows && result; i++)
      for (int j = 0; j < A->columns && result; j++)
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) >= 1e-7) result = FAILURE;
  } else
    result = FAILURE;
  return result;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int return_code = OK;
  if ((s21_is_valid_matrix(A) && s21_is_valid_matrix(B) && result != NULL) &&
      s21_matrix_size_eq(A, B) &&
      (!s21_is_inf_or_nan(A) && !s21_is_inf_or_nan(B))) {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++)
      for (int j = 0; j < A->columns; j++)
        result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
    if (s21_is_inf_or_nan(result)) return_code = CALCULATION_INCORRECT;
  } else if (!s21_is_valid_matrix(A) || !s21_is_valid_matrix(B) ||
             result == NULL)
    return_code = MATRIX_INCORRECT;
  else
    return_code = CALCULATION_INCORRECT;
  return return_code;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int return_code = OK;
  if ((s21_is_valid_matrix(A) && s21_is_valid_matrix(B) && result != NULL) &&
      s21_matrix_size_eq(A, B) &&
      (!s21_is_inf_or_nan(A) && !s21_is_inf_or_nan(B))) {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++)
      for (int j = 0; j < A->columns; j++)
        result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
    if (s21_is_inf_or_nan(result)) return_code = CALCULATION_INCORRECT;
  } else if (!s21_is_valid_matrix(A) || !s21_is_valid_matrix(B) ||
             result == NULL)
    return_code = MATRIX_INCORRECT;
  else
    return_code = CALCULATION_INCORRECT;
  return return_code;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int return_code = OK;
  if (s21_is_valid_matrix(A) && result != NULL && !s21_is_inf_or_nan(A) &&
      isnan(number) == 0 && isinf(number) == 0) {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++)
      for (int j = 0; j < A->columns; j++)
        result->matrix[i][j] = A->matrix[i][j] * number;
    if (s21_is_inf_or_nan(result)) return_code = CALCULATION_INCORRECT;
  } else if (!s21_is_valid_matrix(A) || result == NULL)
    return_code = MATRIX_INCORRECT;
  else
    return_code = CALCULATION_INCORRECT;
  return return_code;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int return_code = OK;
  if (s21_is_valid_matrix(A) && s21_is_valid_matrix(B) && result != NULL &&
      (!s21_is_inf_or_nan(A) && !s21_is_inf_or_nan(B)) &&
      A->columns == B->rows) {
    s21_create_matrix(A->rows, B->columns, result);
    s21_calculate_matrix_mult(A, B, result);
  } else if (!s21_is_valid_matrix(A) || !s21_is_valid_matrix(B) ||
             result == NULL)
    return_code = MATRIX_INCORRECT;
  else
    return_code = CALCULATION_INCORRECT;
  return return_code;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int return_code = OK;
  if (s21_is_valid_matrix(A) && result != NULL) {
    s21_create_matrix(A->columns, A->rows, result);
    for (int i = 0; i < A->columns; i++)
      for (int j = 0; j < A->rows; j++) result->matrix[i][j] = A->matrix[j][i];
  } else
    return_code = MATRIX_INCORRECT;
  return return_code;
}