#ifndef S21_FRAMES_H__
#define S21_FRAMES_H__

#include "s21_draws.h"

void game_start_frame(GameInfo_t gameInfo);
void gameplay_frame(GameInfo_t gameInfo, ScreenInfo_t screenInfo);
void game_pause_frame();
void game_over_frame(GameInfo_t gameInfo);
void game_exit_frame();
void draw_menu(int startX, int startY, char *items[], int startItem, int size,
               int attribute);

#endif  // S21_FRAMES_H__