/**
 * @file s21_actions.c
 * @author aminaall (aminaall@student.21-school.ru)
 * @brief Перемещения фигур currentFigure (Далее - Фигура), расположенных на
 * матрице gameInfo.field (Далее - Поле)
 *
 * В каждой из функций мы сверяем матрицу поля с матрицей currentFigure.matrix,
 * Поскольку стуктура Фигуры хранит свое местоположение через x и y, которые
 * означают x и y Поля, где находится Фигура, то мы сверяем, есть ли в матрице
 * Фигуры заполненный элемент (1) или нет. Если есть, то значит мы нашли
 * координату фигуры на поле и можем её переместить.
 *
 * В начале всех функций присутствует проверка на коллизию, возвращающая 1, если
 * произошла коллизия и 0, если коллизии не было и мы можем передвинуть Фигуру.
 *
 * @version 1.0
 * @date 2025-02-24
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "s21_actions.h"

int move_down(GameInfo_t *gameInfo, Figure_t *currentFigure) {
  Figures_t figures = getSetFigures(NULL);
  int collided =
      check_bottom_collision(gameInfo->field, &figures, currentFigure);
  if (!collided) {
    int startX = currentFigure->x;
    int startY = currentFigure->y;
    int **matrix = currentFigure->matrix;

    for (int y = figures.max_figure_size - 1; y >= 0; y--) {
      for (int x = 0; x <= figures.max_figure_size - 1; x++) {
        if (matrix[x][y] > 0) {
          gameInfo->field[startX + x][startY + y + MOVE_DOWN_SPEED] =
              gameInfo->field[startX + x][startY + y];
          gameInfo->field[startX + x][startY + y] = 0;
        }
      }
    }
    currentFigure->y += MOVE_DOWN_SPEED;
  } else {
    currentFigure->is_alive = 0;
  }

  return collided;
}

int move_left_side(GameInfo_t *gameInfo, Figures_t *figures,
                   Figure_t *currentFigure) {
  int collided = check_sides_collision(gameInfo->field, figures, currentFigure);
  if (!collided || collided == Right) {
    int startX = currentFigure->x;
    int startY = currentFigure->y;
    int **matrix = currentFigure->matrix;

    for (int x = 0; x <= figures->max_figure_size - 1; x++) {
      for (int y = 0; y <= figures->max_figure_size - 1; y++) {
        if (matrix[x][y] > 0) {
          gameInfo->field[startX + x - MOVE_SIDE_SPEED][startY + y] =
              gameInfo->field[startX + x][startY + y];
          gameInfo->field[startX + x][startY + y] = 0;
        }
      }
    }
    currentFigure->x -= MOVE_SIDE_SPEED;
  }
  return collided;
}

int move_right_side(GameInfo_t *gameInfo, Figures_t *figures,
                    Figure_t *currentFigure) {
  int collided = check_sides_collision(gameInfo->field, figures, currentFigure);
  if (!collided || collided == Left) {
    int startX = currentFigure->x;
    int startY = currentFigure->y;
    int **matrix = currentFigure->matrix;

    for (int x = figures->max_figure_size - 1; x >= 0; x--) {
      for (int y = figures->max_figure_size - 1; y >= 0; y--) {
        if (matrix[x][y] > 0) {
          gameInfo->field[startX + x + MOVE_SIDE_SPEED][startY + y] =
              gameInfo->field[startX + x][startY + y];
          gameInfo->field[startX + x][startY + y] = 0;
        }
      }
    }
    currentFigure->x += MOVE_SIDE_SPEED;
  }
  return collided;
}

int rotate_figure(GameInfo_t *gameInfo, Figures_t *figures,
                  Figure_t *currentFigure, int rotation_type) {
  int collided = check_rotation_collision(gameInfo->field, figures,
                                          currentFigure, rotation_type);
  if (!collided) {
    int type = currentFigure->type;
    int **matrix = currentFigure->matrix;
    int fieldX = currentFigure->x;
    int fieldY = currentFigure->y;

    subtract_matrix_from_field(gameInfo->field, matrix, fieldX, fieldY,
                               figures->max_figure_size);
    rotate_matrix(matrix, figures->type_sizes[type], figures->anchors_x[type],
                  figures->anchors_y[type], rotation_type);
    add_matrix_to_field(gameInfo->field, matrix, fieldX, fieldY,
                        figures->max_figure_size);

    currentFigure->rotation_type = rotation_type;
  }
  return collided;
}