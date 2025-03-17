#ifndef S21_FIGURES_DEFAULT_H_
#define S21_FIGURES_DEFAULT_H_

#include "s21_matrix_operations.h"

void loadDefaultFigures(Figures_t *figures);
void loadDefaultPattern(int type, int size, int **result, int *anchors);
void addFigure(Figures_t *figures, int **figure, int *anchors);

#endif  // S21_FIGURES_DEFAULT_H_