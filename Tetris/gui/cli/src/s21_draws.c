/**
 * @file s21_draws.c
 * @author aminaall (aminaall@student.21-school.ru)
 * @brief Основные функции, необходимые отрисовки кадров
 * @version 1.0
 * @date 2025-02-25
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "s21_draws.h"

void draw_overlay(int width, int height) {
  attron(COLOR_PAIR(BACKGROUND_COLOR_INDEX));
  draw_box(width, height, 0, 0);
  draw_box(width / 2, height, width + OVERLAY_OFFSET, 0);
  attroff(COLOR_PAIR(BACKGROUND_COLOR_INDEX));
}

void draw_box(int width, int height, int startX, int startY) {
  mvhline(0 + startY, 1 + startX, ACS_HLINE, width);
  mvvline(1 + startY, 0 + startX, ACS_VLINE, height);
  mvvline(1 + startY, width + 1 + startX, ACS_VLINE, height);
  mvhline(height + 1 + startY, 1 + startX, ACS_HLINE, width);

  mvaddch(0 + startY, 0 + startX, ACS_ULCORNER);
  mvaddch(0 + startY, width + 1 + startX, ACS_URCORNER);
  mvaddch(height + 1 + startY, 0 + startX, ACS_LLCORNER);
  mvaddch(height + 1 + startY, width + 1 + startX, ACS_LRCORNER);
}

void draw_field(GameInfo_t gameInfo, ScreenInfo_t screenInfo) {
  for (int i = 0; i < screenInfo.scaled_width; i += screenInfo.width_scale) {
    for (int wscale = 0; wscale < screenInfo.width_scale; wscale++) {
      for (int j = 0; j < screenInfo.scaled_height; j++) {
        int *value =
            &(gameInfo.field[i / screenInfo.width_scale][j + MATRIX_V_OFFSET]);
        if (*value <= 0) {
          attron(COLOR_PAIR(BACKGROUND_COLOR_INDEX));
          mvaddch(1 + j, 1 + i + wscale, MATRIX_EMPTY);
          attroff(COLOR_PAIR(BACKGROUND_COLOR_INDEX));
        } else {
          attron(COLOR_PAIR(*value));
          mvaddch(1 + j, 1 + i + wscale, MATRIX_CHAR);
          attroff(COLOR_PAIR(*value));
        }
      }
    }
  }
}

void draw_stats(GameInfo_t gameInfo, ScreenInfo_t screenInfo) {
  int startX = screenInfo.scaled_width + OVERLAY_OFFSET + 1;
  int startY = 1;
  int interval = 3;
  draw_stats_overlay(gameInfo, startX, startY, interval);
  draw_stats_data(gameInfo, screenInfo, startX, startY + 1, interval);
}

void draw_stats_overlay(GameInfo_t gameInfo, int startX, int startY,
                        int interval) {
  attron(COLOR_PAIR(gameInfo.level) | A_REVERSE);
  mvprintw(startY, startX, "HIGHSCORE");
  mvprintw(startY + interval, startX, "SCORE");
  mvprintw(startY + interval * 2, startX, "LEVEL");
  mvprintw(startY + interval * 3, startX + 2, "NEXT");
  attroff(COLOR_PAIR(gameInfo.level) | A_REVERSE);
}

void draw_stats_data(GameInfo_t gameInfo, ScreenInfo_t screenInfo, int startX,
                     int startY, int interval) {
  attron(COLOR_PAIR(gameInfo.level) | A_REVERSE);
  mvprintw(startY, startX, "%d", gameInfo.high_score);
  mvprintw(startY + interval, startX, "%d", gameInfo.score);
  mvprintw(startY + interval * 2, startX, "%d", gameInfo.level);
  attroff(COLOR_PAIR(gameInfo.level) | A_REVERSE);
  if (!gameInfo.pause) {
    draw_matrix(gameInfo.next, startX, 1 + startY + interval * 3,
                screenInfo.width_scale);
  }
}

void draw_matrix(int **matrix, int startX, int startY, int scaleX) {
  for (int x = 0; x < DEFAULT_FIGURE_SIZE * scaleX; x += scaleX) {
    for (int x_scale = 0; x_scale < scaleX; x_scale++) {
      for (int y = 0; y < DEFAULT_FIGURE_SIZE; y++) {
        if (matrix[x / scaleX][y] <= 0) {
          attron(COLOR_PAIR(BACKGROUND_COLOR_INDEX));
          mvaddch(startY + y, startX + x + x_scale, MATRIX_EMPTY);
          attroff(COLOR_PAIR(BACKGROUND_COLOR_INDEX));
        } else {
          attron(COLOR_PAIR(matrix[x / scaleX][y]));
          mvaddch(startY + y, startX + x + x_scale, MATRIX_CHAR);
          attroff(COLOR_PAIR(matrix[x / scaleX][y]));
        }
      }
    }
  }
}