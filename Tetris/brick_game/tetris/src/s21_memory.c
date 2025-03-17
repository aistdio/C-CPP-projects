/**
 * @file s21_memory.c
 * @author aminaall (aminaall@student.21-school.ru)
 * @brief Выделение и очистки памяти матрицам, с проверками
 * @version 1.0
 * @date 2025-02-24
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "s21_memory.h"

int allocate_matrix(int ***matrix, int width, int height) {
  int error = 0;
  if (matrix == NULL || width < 1 || height < 1) {
    error = 1;
  } else {
    *matrix = calloc(width, sizeof(int *));
  }
  if (!error && *matrix != NULL) {
    (*matrix)[0] = calloc(height, sizeof(int));
    for (int i = 1; !error && i < width; i++) {
      if ((*matrix)[i - 1] == NULL)
        error = 1;
      else
        (*matrix)[i] = calloc(height, sizeof(int));
    }
  }
  return error;
}

void free_matrix(int ***matrix, int width) {
  if (matrix != NULL && *matrix != NULL && width > 0) {
    for (int i = 0, error = 0; !error && i < width; i++) {
      if ((*matrix)[i] != NULL)
        free((*matrix)[i]);
      else
        error = 1;
    }
    free(*matrix);
    *matrix = NULL;
  }
}