/**
 * @file s21_backend.c
 * @author aminaall (aminaall@student.21-school.ru)
 * @brief Иницилизация, очищение всех основных структур бэкенда. Обновление
 * текущего статуса игры (UpdateCurrentState).
 * @version 1.0
 * @date 2025-02-24
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "s21_backend.h"

/**
 * @brief Иницилизация всех основных структур
 *
 * @param gameInfo указатель на структуру
 * @param width ширина игрового поля
 * @param height высота игрового поля
 * @return int ошибка выделения памяти
 */
int init_backend(GameInfo_t *gameInfo, int width, int height) {
  int memory_fail = init_GameInfo(gameInfo, width, height, DEFAULT_FIGURE_SIZE,
                                  DEFAULT_USPEED);
  if (!memory_fail) {
    memory_fail = init_Figures(DEFAULT_FIGURE_SIZE);
  }
  if (!memory_fail) {
    Figure_t memory_check = getSetFigure(NULL, DEFAULT_FIGURE_SIZE);
    memory_fail = (memory_check.type == -1) ? true : false;
  }
  if (!memory_fail) {
    getFieldSize(&width, &height);
  }
  return memory_fail;
}

/**
 * @brief Выделение памяти и первичная настройка gameInfo
 *
 * @param gameInfo указатель на структуру
 * @param width ширина игрового поля
 * @param height высота игрового поля
 * @param max_figure_size максимальный размер фигурки
 * @param speed базовая скорость игры
 * @return int ошибка выделения памяти
 */
int init_GameInfo(GameInfo_t *gameInfo, int width, int height,
                  int max_figure_size, int speed) {
  int db_fail = load_tetris_db(gameInfo);
  if (db_fail) {
    gameInfo->high_score = 0;
  }
  gameInfo->score = 0;
  gameInfo->level = START_LEVEL;
  gameInfo->speed = speed;
  gameInfo->pause = START_GAME_PAUSE;

  height += MATRIX_V_OFFSET * 2;

  int error = allocate_matrix(&(gameInfo->field), width, height);
  if (!error) {
    error =
        allocate_matrix(&(gameInfo->next), max_figure_size, max_figure_size);
  }
  if (!error) {
    for (int i = 0; i < MATRIX_V_OFFSET; i++) {
      for (int j = 0; j < width; j++) {
        gameInfo->field[j][height - i - 1] = 1;
      }
    }
    getSetGameInfo(gameInfo);
  }

  return error;
}

/**
 * @brief Возврат данных структуры gameInfo к начальному состоянию (после
 * иницилизации)
 *
 * @param gameInfo
 */
void resetGameInfo(GameInfo_t *gameInfo) {
  FieldSize_t fieldSize = getFieldSize(NULL, NULL);
  Figures_t figures = getSetFigures(NULL);

  nullify_matrix(gameInfo->field, fieldSize.width, fieldSize.height,
                 MATRIX_H_OFFSET, MATRIX_V_OFFSET);
  nullify_matrix(gameInfo->next, figures.max_figure_size,
                 figures.max_figure_size, 0, 0);
  gameInfo->level = START_LEVEL;
  gameInfo->score = 0;
}

/**
 * @brief Очистка всех основных структур бэкенда, иницилизированных после
 * init_backend()
 *
 */
void remove_backend() {
  FieldSize_t fieldSize = getFieldSize(NULL, NULL);
  Figures_t figures = getSetFigures(NULL);

  remove_GameInfo(fieldSize.width, figures.max_figure_size);

  remove_Figures(&figures);

  getSetFigure(NULL, REMOVE);
}

/**
 * @brief Очистка памяти стуктуры gameInfo
 *
 * @param width ширина поля
 * @param max_figure_size максимальный размер фигурки
 */
void remove_GameInfo(int width, int max_figure_size) {
  GameInfo_t *gameInfo = getSetGameInfo(NULL);
  free_matrix(&gameInfo->field, width);
  free_matrix(&gameInfo->next, max_figure_size);
}