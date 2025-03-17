#ifndef S21_FILE_PROCESSING_H__
#define S21_FILE_PROCESSING_H__

#include <stdio.h>
#include <string.h>

#include "s21_back_defines.h"
#include "s21_back_objects.h"

int load_tetris_db(GameInfo_t *gameInfo);
int validate_data(GameInfo_t gameInfo);

void save_tetris_db(GameInfo_t gameInfo, int width, int height);
void save_matrix_to_file(FILE *file, int **matrix, int width, int height);

#endif  // S21_FILE_PROCESSING_H__