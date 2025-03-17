/**
 * @file s21_frontend.c
 * @author aminaall (aminaall@student.21-school.ru)
 * @brief Основные функции фронтенда
 * @version 1.0
 * @date 2025-02-25
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "s21_frontend.h"

void init_frontend(ScreenInfo_t *screenInfo, int width, int height,
                   int width_scale, int height_scale) {
  screenInfo->width = width;
  screenInfo->height = height;
  screenInfo->width_scale = width_scale;
  screenInfo->height_scale = height_scale;
  screenInfo->scaled_width = width * width_scale;
  screenInfo->scaled_height = height * height_scale;
  setup_main_window();
  setup_color();
}

void setup_main_window() {
  initscr();
  noecho();
  keypad(stdscr, TRUE);
  curs_set(0);
  timeout(INPUT_CD);
  setup_color();
}

void setup_color() {
  if (has_colors() && can_change_color()) {
    start_color();
    short COLOR_PEACH = 21;
    short COLOR_KIND_OF_GREEN = 22;
    short COLOR_KIND_OF_PURPLE = 23;
    short COLOR_WHITE_PURPLE = 24;
    short COLOR_KIND_OF_BLUE = 25;
    init_color(COLOR_PEACH, 1000, 500, 500);
    init_color(COLOR_KIND_OF_GREEN, 700, 1000, 500);
    init_color(COLOR_KIND_OF_PURPLE, 500, 500, 1000);
    init_color(COLOR_WHITE_PURPLE, 850, 850, 1000);
    init_color(COLOR_KIND_OF_BLUE, 450, 950, 1000);

    init_pair(1, COLOR_BLACK, COLOR_MAGENTA);
    init_pair(2, COLOR_BLACK, COLOR_KIND_OF_GREEN);
    init_pair(3, COLOR_BLACK, COLOR_CYAN);
    init_pair(4, COLOR_BLACK, COLOR_YELLOW);
    init_pair(5, COLOR_BLACK, COLOR_PEACH);
    init_pair(6, COLOR_BLACK, COLOR_GREEN);
    init_pair(7, COLOR_BLACK, COLOR_RED);
    init_pair(8, COLOR_BLACK, COLOR_WHITE);
    init_pair(9, COLOR_BLACK, COLOR_KIND_OF_BLUE);
    init_pair(STATS_FINAL_COLOR_INDEX, COLOR_WHITE_PURPLE, COLOR_BLACK);
    init_pair(BACKGROUND_COLOR_INDEX, COLOR_KIND_OF_PURPLE, COLOR_BLACK);
  }
}

/**
 * @brief Основная функция фронтенда, которая отрисовывает кадр в зависимости от
 * состояния игры
 *
 * Поскольку это первая вызываемая контроллером функция фронтенда, эта функция
 * вызывает иницилизацию стуктуры фронтенда
 *
 * @param gameInfo
 */
void draw_frame(GameInfo_t gameInfo) {
  static ScreenInfo_t screenInfo = {0};
  static int first_time = 1;
  if (first_time) {
    init_frontend(&screenInfo, WIDTH, HEIGHT, WIDTH_SCALE, HEIGHT_SCALE);
    first_time = 0;
  }

  static int previous_frame = START_GAME_PAUSE;
  int current_frame = gameInfo.pause;

  if (current_frame != previous_frame) {
    clear();
    previous_frame = current_frame;
  }

  if (current_frame == START_GAME_PAUSE) {
    game_start_frame(gameInfo);
    refresh();
  }

  else if (current_frame == NO_PAUSE) {
    gameplay_frame(gameInfo, screenInfo);
    refresh();
  }

  else if (current_frame == PAUSED) {
    game_pause_frame();
  }

  else if (current_frame == GAME_OVER_PAUSE) {
    game_over_frame(gameInfo);
    refresh();
  }

  else if (current_frame == EXIT_PAUSE) {
    game_exit_frame();
    refresh();
    exit_frontend();
  }
}

void exit_frontend() {
  napms(EXIT_SLEEP_TIME);
  attrset(A_NORMAL);
  clear();
  endwin();
}