/**
 * @file s21_figures_default.c
 * @author aminaall (aminaall@student.21-school.ru)
 * @brief Загрузка матриц фигур из задания (pattern/ТИП матрицы) в массив матриц
 * Figures_t
 *
 * Figures_t figurse.matrix [ТИП][МАТРИЦА_X][МАТРИЦА_Y]
 *
 * @version 1.0
 * @date 2025-02-24
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "s21_figures_default.h"

void loadDefaultFigures(Figures_t *figures) {
  int size = figures->max_figure_size;
  if (size >= 4) {
    int **pattern;
    allocate_matrix(&pattern, size, size);
    for (int type = 0; type < DEFAULT_FIGURES; type++) {
      int *anchors = calloc(2, sizeof(int));
      if (anchors != NULL) {
        loadDefaultPattern(type, size, pattern, anchors);
        addFigure(figures, pattern, anchors);
        free(anchors);
      }
    }
    free_matrix(&pattern, size);
  }
}

void loadDefaultPattern(int type, int size, int **result, int *anchors) {
  int **pattern;
  allocate_matrix(&pattern, size, size);

  if (type == 0) {
    for (int i = 0; i < 4; i++) pattern[i][1] = 1;
    anchors[anchorX] = -1, anchors[anchorY] = -1;
  } else if (type == 1) {
    pattern[0][0] = 1;
    for (int i = 0; i < 3; i++) pattern[i][1] = 1;
  } else if (type == 2) {
    pattern[2][0] = 1;
    for (int i = 0; i < 3; i++) pattern[i][1] = 1;
  } else if (type == 3) {
    for (int i = 0; i < 2; i++)
      for (int j = 0; j < 2; j++) pattern[i][j] = 1;
    anchors[anchorX] = -1, anchors[anchorY] = -1;
  } else if (type == 4) {
    for (int i = 1; i < 3; i++) pattern[i][1] = 1;
    for (int i = 0; i < 2; i++) pattern[i][2] = 1;
    anchors[anchorX] = 1, anchors[anchorY] = 1;
  } else if (type == 5) {
    pattern[1][0] = 1;
    for (int i = 0; i < 3; i++) pattern[i][1] = 1;
  } else if (type == 6) {
    for (int i = 0; i < 2; i++) pattern[i][1] = 1;
    for (int i = 1; i < 3; i++) pattern[i][2] = 1;
    anchors[anchorX] = 1, anchors[anchorY] = 1;
  }

  copy_cubic_matrix(result, pattern, size);
  free_matrix(&pattern, size);
}

/**
 * @brief Добавляет матрицу фигуры в массив матриц фигур
 *
 * @param figures указатель на структуру, в массив матриц которой добавляется
 * матрица фигуры
 * @param figure матрица фигура
 * @param anchors опорные точки фигуры, нужные для корректного функционирования
 * поворота фигуры
 */
void addFigure(Figures_t *figures, int **figure, int *anchors) {
  if (figures != NULL && figure != NULL) {
    figures->types_total++;
    int *index = &(figures->types_total);
    int size = figures->max_figure_size;
    allocate_matrix(&(figures->matrix[*index]), size, size);
    copy_cubic_matrix(figures->matrix[*index], figure, size);

    figures->anchors_x[*index] = anchors[anchorX];
    figures->anchors_y[*index] = anchors[anchorY];

    int minX = 0, minY = 0, maxX = 0, maxY = 0;
    getMinMaxFilledXY(figure, size, &minX, &minY, &maxX, &maxY);
    figures->type_sizes[*index] = (maxX > maxY) ? maxX + 1 : maxY + 1;
  }
}