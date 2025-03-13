#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int return_code = OK;
  if (result != NULL && rows > 0 && columns > 0) {
    result->rows = rows;
    result->columns = columns;
    result->matrix = (double **)calloc(rows, sizeof(double *));
    for (int i = 0; i < rows; i++)
      result->matrix[i] = (double *)calloc(columns, sizeof(double));
  } else
    return_code = MATRIX_INCORRECT;
  return return_code;
}

void s21_remove_matrix(matrix_t *A) {
  if (s21_is_valid_matrix(A) && A->matrix != NULL) {
    for (int i = 0; i < A->rows; i++)
      if (A->matrix[i] != NULL) free(A->matrix[i]);
    free(A->matrix);
    A->matrix = NULL;
    A->rows = 0, A->columns = 0;
  }
}