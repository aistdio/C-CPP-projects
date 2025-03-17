#ifndef S21_BACK_DEFINES_H_
#define S21_BACK_DEFINES_H_

#include "s21_common_defines.h"

#define DB_FILE "tetris_save_data.txt"

#define DEFAULT_USPEED 500

#define SPAWN_FIGURE_Y 0
#define MOVE_SIDE_SPEED 1
#define MOVE_DOWN_SPEED 1

#define SCORE_FOR_FIRST_LINE 100
#define SCORE_MULTIPLIER 2

#define SCORE_TO_LEVEL_UP 600

#define MAX_FIGURES 20
#define DEFAULT_FIGURES 7

#define USECOND_TO_SECOND 1000

#ifndef __NCURSES_H
#define bool char
#define true 1
#define false 0
#endif

#ifndef NULL
#define NULL ((void *)0)
#endif

#define NANO_TO_SECONDS 1000000000LL

#endif  // S21_BACK_DEFINES_H_