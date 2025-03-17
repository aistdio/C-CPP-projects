#ifndef S21_DRAWS_H__
#define S21_DRAWS_H__

#include <ncurses.h>

#include "s21_common.h"
#include "s21_front_defines.h"
#include "s21_front_objects.h"

void draw_overlay(int width, int height);
void draw_box(int width, int height, int startX, int startY);

void draw_field(GameInfo_t gameInfo, ScreenInfo_t screenInfo);
void draw_stats(GameInfo_t gameInfo, ScreenInfo_t screenInfo);
void draw_stats_overlay(GameInfo_t gameInfo, int startX, int startY,
                        int interval);
void draw_stats_data(GameInfo_t gameInfo, ScreenInfo_t screenInfo, int startX,
                     int startY, int interval);
void draw_matrix(int **matrix, int startX, int startY, int scaleX);

#endif  // S21_DRAWS_H__