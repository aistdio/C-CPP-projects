#include "s21_matrix.h"

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int return_code = OK;
  if ((s21_is_valid_matrix(A) && result != NULL) && A->rows == A->columns &&
      !s21_is_inf_or_nan(A)) {
    double determinant;
    s21_determinant(A, &determinant);
    if (determinant != 0.0)
      s21_inverse_matrix_calculation(A, result, determinant);
    else
      return_code = CALCULATION_INCORRECT;
  } else if (!s21_is_valid_matrix(A) || result == NULL)
    return_code = MATRIX_INCORRECT;
  else
    return_code = CALCULATION_INCORRECT;
  return return_code;
}

void s21_inverse_matrix_calculation(matrix_t *A, matrix_t *result,
                                    double determinant) {
  matrix_t A_minor;
  s21_calc_complements(A, &A_minor);
  matrix_t A_minor_transposed;
  s21_transpose(&A_minor, &A_minor_transposed);
  s21_remove_matrix(&A_minor);
  s21_mult_number(&A_minor_transposed, 1.0 / determinant, result);
  s21_remove_matrix(&A_minor_transposed);
}