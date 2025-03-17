/**
 * @file s21_figures.c
 * @author aminaall (aminaall@student.21-school.ru)
 * @brief Основные функции для работы со структурами Figures_t и Figure_t
 *
 * @version 1.0
 * @date 2025-02-24
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "s21_figures.h"

/**
 * @brief Выделение памяти и загрузка ТИПов/pattern'ов фигур из задания в массив
 * матриц Figures_t
 *
 * @param max_figure_size максимальный размер матрицы
 * @return int ошибка выделения памяти
 */
int init_Figures(int max_figure_size) {
  int error = 0;

  Figures_t figures = {0};
  figures.type_sizes = calloc(MAX_FIGURES, sizeof(int));
  figures.anchors_x = calloc(MAX_FIGURES, sizeof(int));
  figures.anchors_y = calloc(MAX_FIGURES, sizeof(int));

  figures.matrix = calloc(MAX_FIGURES, sizeof(int **));
  figures.max_figure_size = max_figure_size;
  figures.types_total = -1;
  if (figures.matrix != NULL) {
    loadDefaultFigures(&figures);
    getSetFigures(&figures);
  } else {
    error = 1;
  }

  return error;
}

/**
 * @brief Очистка структуры Figures_t
 *
 */
void remove_Figures(Figures_t *figures) {
  if (figures != NULL && figures->matrix != NULL) {
    if (figures->type_sizes != NULL) {
      free(figures->type_sizes);
      figures->type_sizes = NULL;
    }
    if (figures->anchors_x != NULL) {
      free(figures->anchors_x);
      figures->anchors_x = NULL;
    }
    if (figures->anchors_y != NULL) {
      free(figures->anchors_y);
      figures->anchors_y = NULL;
    }
    for (int i = 0; i <= figures->types_total; i++) {
      free_matrix(&(figures->matrix[i]), figures->max_figure_size);
    }
    free(figures->matrix);
    figures->matrix = NULL;
    figures->max_figure_size = 0;
    figures->types_total = 0;
  }
}

/**
 * @brief Спавн фигуры
 *
 * Функция обновляет данные текущей фигуры Figure_t figure.
 * Копируется матрица из массива матриц Figures_t figures в матрицы Figure_t
 * figure (текущая уже живая фигура) и gameInfo.field (игровое поле)
 *
 * @param gameInfo для заполнения игрового поля
 * @param figures отсюда берется тип матрицы (это и есть массив указателей на
 * матрицы)
 * @param figure фигура, которой может управлять игрок
 * @param startX начальное положение X
 * @param startY начальное положение Y
 * @param type ТИП матрицы (из задания)
 */
void spawn_figure(GameInfo_t *gameInfo, Figures_t *figures, Figure_t *figure,
                  int startX, int startY, int type) {
  figure->is_alive = 1;
  figure->type = type;
  figure->rotation_type = COUNTER_CLOCKWISE;
  figure->x = startX;
  figure->y = startY;

  int *size = &(figures->max_figure_size);
  for (int i = 0; i < *size; i++) {
    for (int j = 0; j < *size; j++) {
      if (figures->matrix[type][i][j] > 0) {
        figure->matrix[i][j] = type + 1;
        gameInfo->field[i + startX][j + startY] = type + 1;
      } else {
        figure->matrix[i][j] = 0;
      }
    }
  }
}

/**
 * @brief Остановка текущей фигуры
 *
 */
void stopCurrentFigure() {
  Figure_t figure = getSetFigure(NULL, NO_ACTION);
  figure.is_alive = 0;
  getSetFigure(&figure, NO_ACTION);
}