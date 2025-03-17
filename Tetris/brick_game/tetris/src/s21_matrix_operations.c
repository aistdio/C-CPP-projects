/**
 * @file s21_matrix_operations.c
 * @author aminaall (aminaall@student.21-school.ru)
 * @brief Основные операции с матрицами
 * @version 1.0
 * @date 2025-02-24
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "s21_matrix_operations.h"

void subtract_matrix_from_field(int **field, int **matrix, int startX,
                                int startY, int size) {
  for (int y = 0; y < size; y++) {
    for (int x = 0; x < size; x++) {
      if (matrix[x][y]) {
        field[startX + x][startY + y] = 0;
      }
    }
  }
}

void rotate_matrix(int **matrix, int size, int anchor_x, int anchor_y,
                   int rotation_type) {
  if (anchor_x == 0 || anchor_y == 0) {
    int **matrix_copy;
    int memory_fail = allocate_matrix(&matrix_copy, size, size);
    if (!memory_fail) {
      if (rotation_type == COUNTER_CLOCKWISE) {
        transpose(matrix_copy, matrix, size);
        reverse_rows(matrix, matrix_copy, size);
      } else {
        reverse_rows(matrix_copy, matrix, size);
        transpose(matrix, matrix_copy, size);
      }
      free_matrix(&matrix_copy, size);
    }
  } else if (anchor_x < 0 || anchor_y < 0) {
    swap_row_and_column(matrix, size, anchor_x * -1, anchor_y * -1);
  } else {
    rotate_complex_figure(matrix, size, anchor_x, anchor_y);
  }
}

void rotate_complex_figure(int **matrix, int size, int anchor_x, int anchor_y) {
  if (matrix[0][anchor_y + 1]) {
    swap_row_and_column(matrix, size, anchor_x - 1, anchor_y + 1);
    swap_row_and_column(matrix, size, anchor_x + 1, anchor_y + 1);
  } else if (matrix[anchor_x - 1][anchor_y - 1]) {
    swap_row_and_column(matrix, size, anchor_x + 1, anchor_y - 1);
    matrix[anchor_x + 1][anchor_y] = matrix[anchor_x - 1][anchor_y];
    matrix[anchor_x - 1][anchor_y] = 0;
    matrix[anchor_x - 1][anchor_y + 1] = matrix[anchor_x + 1][anchor_y + 1];
    matrix[anchor_x + 1][anchor_y + 1] = 0;
  }

  else if (matrix[anchor_x + 1][anchor_y + 1]) {
    swap_row_and_column(matrix, size, anchor_x + 1, anchor_y);
    matrix[anchor_x][anchor_y] = matrix[anchor_x + 1][anchor_y + 1];
    matrix[anchor_x + 1][anchor_y + 1] = 0;
  } else if (matrix[anchor_x + 1][anchor_y - 1]) {
    swap_row_and_column(matrix, size, anchor_x + 1, anchor_y);
  }
}

void add_matrix_to_field(int **field, int **matrix, int startX, int startY,
                         int size) {
  for (int y = 0; y < size; y++) {
    for (int x = 0; x < size; x++) {
      if (matrix[x][y]) {
        field[startX + x][startY + y] = matrix[x][y];
      }
    }
  }
}

void shift_to_bottom(int **field, int topY, int bottomY, int width) {
  for (int y = bottomY; y > topY; y--) {
    for (int x = MATRIX_H_OFFSET; x < width; x++) {
      field[x][y] = field[x][y - 1];
    }
  }
}

void reverse_rows(int **dst, int **src, int size) {
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      dst[i][j] = src[i][size - 1 - j];
    }
  }
}

void transpose(int **dst, int **src, int size) {
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      dst[i][j] = src[j][i];
    }
  }
}

void swap_row_and_column(int **matrix, int size, int row, int column) {
  for (int i = 0; i < size; i++) {
    int tmp = matrix[i][column];
    matrix[i][column] = matrix[row][i];
    matrix[row][i] = tmp;
  }
}

void multiply_matrix(int **matrix, int size, int number) {
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      matrix[i][j] *= number;
    }
  }
}

void nullify_matrix(int **matrix, int rows, int columns, int startX,
                    int startY) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      matrix[startX + i][startY + j] = 0;
    }
  }
}

void copy_cubic_matrix(int **dst, int **src, int size) {
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      dst[i][j] = src[i][j];
    }
  }
}

int check_bottom_collision(int **field, Figures_t *figures,
                           Figure_t *currentFigure) {
  int **matrix = currentFigure->matrix;
  int startX = currentFigure->x;
  int startY = currentFigure->y + MOVE_DOWN_SPEED;

  int collided = 0;
  for (int y = figures->max_figure_size - 1; y >= 0; y--)
    for (int x = 0; x <= figures->max_figure_size - 1 && !collided; x++) {
      if (matrix[x][y] > 0 && field[startX + x][startY + y] > 0) {
        if (y == figures->max_figure_size - 1) {
          collided = 1;
        } else if (!matrix[x][y + MOVE_DOWN_SPEED]) {
          collided = 1;
        }
      }
    }

  return collided;
}

int check_sides_collision(int **field, Figures_t *figures,
                          Figure_t *currentFigure) {
  FieldSize_t fieldSize = getFieldSize(NULL, NULL);

  int collided_on_left = check_left_collision(field, figures, currentFigure);
  int collided_on_right =
      check_right_collision(field, &fieldSize, figures, currentFigure);

  return collided_on_left + collided_on_right;
}

int check_left_collision(int **field, Figures_t *figures,
                         Figure_t *currentFigure) {
  int collided_on_left = 0;
  int **matrix = currentFigure->matrix;

  int startLeftX = currentFigure->x - MOVE_SIDE_SPEED;
  int startY = currentFigure->y;

  for (int y = 0; y <= figures->max_figure_size - 1; y++) {
    for (int x = 0; x <= figures->max_figure_size - 1 && !collided_on_left;
         x++) {
      if (startLeftX + x < 0 && matrix[x][y]) {
        collided_on_left = Left;
      } else if (matrix[x][y] > 0 && field[startLeftX + x][startY + y] > 0) {
        if (x == 0) {
          collided_on_left = Left;
        } else if (!matrix[x - MOVE_SIDE_SPEED][y]) {
          collided_on_left = Left;
        }
      }
    }
  }

  return collided_on_left;
}

int check_right_collision(int **field, FieldSize_t *fieldSize,
                          Figures_t *figures, Figure_t *currentFigure) {
  int collided_on_right = 0;
  int **matrix = currentFigure->matrix;

  int startRightX = currentFigure->x + MOVE_SIDE_SPEED;
  int startY = currentFigure->y;

  for (int y = 0; y <= figures->max_figure_size - 1; y++) {
    for (int x = figures->max_figure_size - 1; x >= 0 && !collided_on_right;
         x--) {
      if (startRightX + x > fieldSize->width - 1 && matrix[x][y] > 0) {
        collided_on_right = Right;
      } else if (matrix[x][y] > 0 && field[startRightX + x][startY + y] > 0) {
        if (x == figures->max_figure_size - 1) {
          collided_on_right = Right;
        } else if (!matrix[x + MOVE_SIDE_SPEED][y]) {
          collided_on_right = Right;
        }
      }
    }
  }

  return collided_on_right;
}

int check_rotation_collision(int **field, Figures_t *figures,
                             Figure_t *currentFigure, int rotation_type) {
  FieldSize_t fieldSize = getFieldSize(NULL, NULL);
  int collided = 0;

  int type = currentFigure->type;
  int size = figures->max_figure_size;
  int **rotated_matrix;
  allocate_matrix(&rotated_matrix, size, size);
  copy_cubic_matrix(rotated_matrix, currentFigure->matrix, size);
  rotate_matrix(rotated_matrix, figures->type_sizes[type],
                figures->anchors_x[type], figures->anchors_y[type],
                rotation_type);

  int minX = 0, minY = 0, maxX = 0, maxY = 0;
  getMinMaxFilledXY(rotated_matrix, size, &minX, &minY, &maxX, &maxY);

  int fieldX = currentFigure->x;
  int fieldY = currentFigure->y;

  if (fieldX + maxX >= fieldSize.width - MATRIX_H_OFFSET ||
      fieldX + minX < MATRIX_H_OFFSET) {
    collided = 1;
  } else if (fieldY + maxY >= fieldSize.height - MATRIX_V_OFFSET ||
             fieldY + minY < MATRIX_V_OFFSET) {
    collided = 1;
  }

  for (int y = 0; y < size; y++) {
    for (int x = 0; x < size && !collided; x++) {
      if (rotated_matrix[x][y] > 0 && !currentFigure->matrix[x][y]) {
        if (field[fieldX + x][fieldY + y] > 0) {
          collided = 1;
        }
      }
    }
  }
  free_matrix(&rotated_matrix, size);

  return collided;
}

void getMinMaxFilledXY(int **matrix, int matrix_size, int *minX, int *minY,
                       int *maxX, int *maxY) {
  for (int y = 0; y <= matrix_size - 1; y++) {
    for (int x = 0; x <= matrix_size - 1; x++) {
      if (matrix[x][y] > 0) {
        *minX = (x < *minX) ? x : *minX;
        *minY = (y < *minY) ? y : *minY;
        *maxX = (x > *maxX) ? x : *maxX;
        *maxY = (y > *maxY) ? y : *maxY;
      }
    }
  }
}

/**
 * @brief Находит заполненные линии в матрице поля игры, обнуляет их и сдвигает
 * элементы матрицы выше удаленной линии вниз
 *
 * @param gameInfo указатель на основную структуру игры
 * @return int сколько заполенных линий было удалено
 */
int deleteAttachedLines(GameInfo_t *gameInfo) {
  FieldSize_t fieldSize = getFieldSize(NULL, NULL);
  int linesDeleted = 0;
  bool lineDeleted = false;

  do {
    lineDeleted = false;
    for (int y = MATRIX_V_OFFSET; y < fieldSize.height + MATRIX_V_OFFSET; y++) {
      int line_is_full = 1;
      for (int x = 0; x < fieldSize.width; x++) {
        if (gameInfo->field[x][y] == 0) {
          line_is_full = 0;
        }
      }
      if (line_is_full) {
        for (int x = 0; x < fieldSize.width; x++) {
          gameInfo->field[x][y] = 0;
        }
        shift_to_bottom(gameInfo->field, MATRIX_V_OFFSET, y, fieldSize.width);
        lineDeleted = true;
        linesDeleted++;
      }
    }
  } while (lineDeleted);

  return linesDeleted;
}