/**
 * @file s21_back_stats.c
 * @author aminaall (aminaall@student.21-school.ru)
 * @brief Вычисление текущих gameInfo.score и gameInfo.level
 *
 * @version 1.0
 * @date 2025-02-24
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "s21_back_stats.h"

void calculate_score(int *result, int lines) {
  int unusual_score = 0;
  switch (lines) {
    case 1:
      *result += SCORE_FOR_FIRST_LINE;
      break;

    case 2:
      *result += SCORE_FOR_FIRST_LINE * 3;
      break;

    case 3:
      *result += SCORE_FOR_FIRST_LINE * 7;
      break;

    case 4:
      *result += SCORE_FOR_FIRST_LINE * 15;
      break;

    case 0:
      break;

    default:
      for (int i = 0; i < lines; i++) {
        unusual_score +=
            SCORE_FOR_FIRST_LINE * powf(SCORE_MULTIPLIER, lines - 1);
      }
      *result += unusual_score;
      break;
  }
}

void calculate_level(int *level, int score) {
  *level = START_LEVEL + score / SCORE_TO_LEVEL_UP;
  *level = (*level > MAX_LEVEL) ? MAX_LEVEL : *level;
}