/**
 * @file s21_file_processing.c
 * @author aminaall (aminaall@student.21-school.ru)
 * @brief Загрузка данных (Highscore) из DB_FILE. Выгрузка данных игры в DB_FILE
 * @version 1.0
 * @date 2025-02-24
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "s21_file_processing.h"

int load_tetris_db(GameInfo_t *gameInfo) {
  memset(gameInfo, 0, sizeof(*gameInfo));

  int db_fail = 0;
  FILE *file = fopen(DB_FILE, "r");

  if (file == NULL) {
    db_fail = 1;
  } else {
    char line_buffer[150];

    int line_index = 0;
    int values_start_line = 3;
    while (fgets(line_buffer, sizeof(line_buffer), file) != NULL) {
      line_index++;
      if (line_index == values_start_line) {
        sscanf(line_buffer, "Highscore: %d", &gameInfo->high_score);
      }
    }
    fclose(file);
  }

  if (!db_fail) {
    db_fail = validate_data(*gameInfo);
  }

  return db_fail;
}

int validate_data(GameInfo_t gameInfo) {
  int invalid_data = 0;
  if (gameInfo.high_score < 0) {
    invalid_data = 1;
  }

  return invalid_data;
}

void save_tetris_db(GameInfo_t gameInfo, int width, int height) {
  FILE *file = fopen(DB_FILE, "w");

  if (file != NULL) {
    fprintf(file, "Game by aistdio (aminaall)\n\n");
    fprintf(file, "Highscore: %d\n", gameInfo.high_score);
    fprintf(file, "Level: %d\n", gameInfo.level);
    fprintf(file, "Score: %d\n", gameInfo.score);
    fprintf(file, "Base Speed (in milliseconds): %d\n", gameInfo.speed);
    fprintf(file, "\nThanks for playing!\n");

    fprintf(file, "\nYour saved figures placement is:\n");
    save_matrix_to_file(file, gameInfo.field, width, height);

    fclose(file);
  }
}

void save_matrix_to_file(FILE *file, int **matrix, int width, int height) {
  for (int y = MATRIX_V_OFFSET; y < height + MATRIX_V_OFFSET; y++) {
    for (int x = MATRIX_H_OFFSET; x < width + MATRIX_H_OFFSET - 1; x++) {
      fprintf(file, "%d ", matrix[x][y]);
    }
    fprintf(file, "%d", matrix[width + MATRIX_H_OFFSET - 1][y]);
    fprintf(file, "\n");
  }
}