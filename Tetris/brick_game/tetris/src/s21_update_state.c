/**
 * @file s21_update_state.c
 * @author aminaall (aminaall@student.21-school.ru)
 * @brief Обновление и возвращение структуры GameInfo_t
 * @version 1.0
 * @date 2025-02-25
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "s21_update_state.h"

/**
 * @brief Обновление данных игры в зависимости от прошедшего времени
 *
 * @return GameInfo_t данные об игре для фронтенда
 */
GameInfo_t updateCurrentState() {
  GameInfo_t *gameInfo = getSetGameInfo(NULL);
  Figure_t currentFigure = getSetFigure(NULL, NO_ACTION);

  if (!gameInfo->pause && speed_time_passed(gameInfo->level, gameInfo->speed)) {
    if (currentFigure.is_alive) {
      fsm_state(State_Falling);
    } else {
      fsm_state(State_Spawn);
    }
  }

  return *gameInfo;
}