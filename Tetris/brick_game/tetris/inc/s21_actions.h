#ifndef S21_ACTIONS_H_
#define S21_ACTIONS_H_

#include "s21_matrix_operations.h"

int move_down(GameInfo_t *gameInfo, Figure_t *currentFigure);
int move_left_side(GameInfo_t *gameInfo, Figures_t *figures,
                   Figure_t *currentFigure);
int move_right_side(GameInfo_t *gameInfo, Figures_t *figures,
                    Figure_t *currentFigure);
int rotate_figure(GameInfo_t *gameInfo, Figures_t *figures,
                  Figure_t *currentFigure, int rotation_type);
void add_matrix_to_field(int **field, int **matrix, int startX, int startY,
                         int size);

#endif  // S21_ACTIONS_H_