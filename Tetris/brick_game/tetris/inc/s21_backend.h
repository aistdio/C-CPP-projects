#ifndef S21_BACKEND_H_
#define S21_BACKEND_H_

#include "s21_figures.h"
#include "s21_file_processing.h"
#include "s21_input.h"
#include "s21_update_state.h"

int init_backend(GameInfo_t *gameInfo, int width, int height);
int init_GameInfo(GameInfo_t *gameInfo, int width, int height,
                  int max_figure_size, int speed);
void resetGameInfo(GameInfo_t *gameInfo);

void calculate_score(int *result, int lines);
void calculate_level(int *level, int score);

void remove_backend();
void remove_GameInfo(int width, int max_figure_size);

#endif  // S21_BACKEND_H_