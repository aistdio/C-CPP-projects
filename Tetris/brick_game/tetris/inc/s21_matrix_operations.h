#ifndef S21_MATRIX_OPERATIONS_H_
#define S21_MATRIX_OPERATIONS_H_

#include "s21_singletons.h"

void subtract_matrix_from_field(int **field, int **matrix, int startX,
                                int startY, int size);
void rotate_matrix(int **matrix, int size, int anchor_x, int anchor_y,
                   int rotation_type);
void rotate_complex_figure(int **matrix, int size, int anchor_x, int anchor_y);
void reverse_rows(int **dst, int **src, int size);
void transpose(int **dst, int **src, int size);
void add_matrix_to_field(int **field, int **matrix, int startX, int startY,
                         int size);
void shift_to_bottom(int **field, int topY, int bottomY, int width);
void swap_row_and_column(int **matrix, int size, int row, int column);
void multiply_matrix(int **matrix, int size, int number);
void nullify_matrix(int **matrix, int rows, int columns, int startX,
                    int startY);
void copy_cubic_matrix(int **dst, int **src, int size);

int check_bottom_collision(int **field, Figures_t *figures,
                           Figure_t *currentFigure);
int check_sides_collision(int **field, Figures_t *figures,
                          Figure_t *currentFigure);
int check_left_collision(int **field, Figures_t *figures,
                         Figure_t *currentFigure);
int check_right_collision(int **field, FieldSize_t *fieldSize,
                          Figures_t *figures, Figure_t *currentFigure);
int check_rotation_collision(int **field, Figures_t *figures,
                             Figure_t *currentFigure, int rotation_type);
void getMinMaxFilledXY(int **matrix, int matrix_size, int *minX, int *minY,
                       int *maxX, int *maxY);
int deleteAttachedLines(GameInfo_t *gameInfo);

#endif  // S21_MATRIX_OPERATIONS_H_