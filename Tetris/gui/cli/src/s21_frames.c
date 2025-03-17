/**
 * @file s21_frames.c
 * @author aminaall (aminaall@student.21-school.ru)
 * @brief Отрисовка кадров, которые выбирает draw_frame из s21_frontend.c в
 * зависимости от состояния игры GameInfo_t
 * @version 1.0
 * @date 2025-02-25
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "s21_frames.h"

void game_start_frame(GameInfo_t gameInfo) {
  draw_box(DEFAULT_MENU_WIDTH * 1.3, DEFAULT_MENU_HEIGHT * 2.3,
           OVERLAY_OFFSET * 3 + 1, OVERLAY_OFFSET);

  attron(COLOR_PAIR(BACKGROUND_COLOR_INDEX));
  int size = 9;
  char *items[] = {"\tPress 'Enter' to start the game!\t",
                   "",
                   "'Enter' when game over to restart",
                   "'P' to pause",
                   "'Left arrow' to move left",
                   "'Right arrow' to move right",
                   "'Down arrow' to ground piece",
                   "'Z' to rotate piece counter-clockwise",
                   "'Q' to close the game"};

  mvprintw(OVERLAY_OFFSET + UP_PADDING, OVERLAY_OFFSET + LEFT_PADDING,
           "Your highscore is ");
  attron(A_BLINK);
  printw("%d", gameInfo.high_score);
  attroff(A_BLINK);

  draw_menu(OVERLAY_OFFSET, OVERLAY_OFFSET + 3, items, 0, size, true);

  attroff(COLOR_PAIR(BACKGROUND_COLOR_INDEX));
}

void gameplay_frame(GameInfo_t gameInfo, ScreenInfo_t screenInfo) {
  draw_overlay(screenInfo.scaled_width, screenInfo.scaled_height);
  if (gameInfo.level == MAX_LEVEL)
    attron(A_STANDOUT);
  else if (gameInfo.level == MAX_LEVEL - 1)
    attron(A_BLINK);
  else if (gameInfo.level == START_LEVEL)
    attron(A_DIM);

  draw_stats(gameInfo, screenInfo);
  draw_field(gameInfo, screenInfo);

  if (gameInfo.level == MAX_LEVEL)
    attroff(A_STANDOUT);
  else if (gameInfo.level == MAX_LEVEL - 1)
    attroff(A_BLINK);
  else if (gameInfo.level == START_LEVEL)
    attroff(A_DIM);
}

void game_pause_frame() {
  draw_box(DEFAULT_MENU_WIDTH * 1.3, DEFAULT_MENU_HEIGHT * 2.3,
           OVERLAY_OFFSET * 3 + 1, OVERLAY_OFFSET);

  attron(COLOR_PAIR(BACKGROUND_COLOR_INDEX));

  attron(A_BLINK);
  mvprintw(DEFAULT_MENU_HEIGHT * 1.3, DEFAULT_MENU_WIDTH * 1.2 / 2,
           "Press 'P' to unpause!");
  attroff(A_BLINK);

  attroff(COLOR_PAIR(BACKGROUND_COLOR_INDEX));
}

void game_over_frame(GameInfo_t gameInfo) {
  draw_box(DEFAULT_MENU_WIDTH * 1.3, DEFAULT_MENU_HEIGHT * 2.3,
           OVERLAY_OFFSET * 3 + 1, OVERLAY_OFFSET);

  attron(COLOR_PAIR(BACKGROUND_COLOR_INDEX));
  int size = 3;
  char *items[] = {"\tPress 'Enter' to reset the game!\t", "",
                   "Press 'Q' to close the game"};

  mvprintw(OVERLAY_OFFSET + UP_PADDING, OVERLAY_OFFSET + LEFT_PADDING,
           "Your highscore is ");
  attron(A_BLINK);
  printw("%d", gameInfo.high_score);
  attroff(A_BLINK);

  draw_menu(OVERLAY_OFFSET, OVERLAY_OFFSET + 4, items, 0, size, true);

  attroff(COLOR_PAIR(BACKGROUND_COLOR_INDEX));
}

void game_exit_frame() {
  draw_box(DEFAULT_MENU_WIDTH * 1.3, DEFAULT_MENU_HEIGHT * 2.3,
           OVERLAY_OFFSET * 3 + 1, OVERLAY_OFFSET);

  attron(COLOR_PAIR(BACKGROUND_COLOR_INDEX));
  int size = 2;
  char *items[] = {"\tThanks for playing!\t", "\tGoodbye!\t"};

  draw_menu(OVERLAY_OFFSET, OVERLAY_OFFSET + 3, items, 0, size, true);

  attroff(COLOR_PAIR(BACKGROUND_COLOR_INDEX));
}

void draw_menu(int startX, int startY, char *items[], int startItem, int size,
               int attribute) {
  for (int y = startItem; y < size * 2; y += 2) {
    if (y == startItem && attribute) attron(A_BLINK | A_REVERSE);
    mvprintw(startY + y + UP_PADDING, startX + LEFT_PADDING, "%s",
             items[y / 2]);
    if (y == startItem && attribute) attroff(A_BLINK | A_REVERSE);
  }
}