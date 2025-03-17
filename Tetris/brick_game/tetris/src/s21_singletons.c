/**
 * @file s21_singletons.c
 * @author aminaall (aminaall@student.21-school.ru)
 * @brief Все синглтоны бэкенда
 * @version 1.0
 * @date 2025-02-25
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "s21_singletons.h"

/**
 * @brief Синглтон структуры gameInfo для получения данных этой структуры
 * другими функциями
 *
 */
GameInfo_t *getSetGameInfo(GameInfo_t *gameInfo) {
  static GameInfo_t *result = NULL;
  if (gameInfo != NULL) {
    result = gameInfo;
  }
  return result;
}

/**
 * @brief Синглтон структуры fieldSize для получения данных этой структуры
 * другими функциями
 *
 */
FieldSize_t getFieldSize(int *width, int *height) {
  static FieldSize_t fieldSize = {0};
  if (width != NULL && height != NULL) {
    fieldSize.width = *width;
    fieldSize.height = *height;
  }
  return fieldSize;
}

/**
 * @brief Синглтон Figures_t, необходимый для получения данных текущей структуры
 * Фигур другими функциями
 *
 */
Figures_t getSetFigures(Figures_t *figures) {
  static Figures_t result = {0};
  if (figures != NULL) {
    result = *figures;
  }
  return result;
}

/**
 * @brief Синглтон Figure_t, выделящий своей матрице память при setting > 0.
 * Очищает память при setting == -1
 *
 *
 */
Figure_t getSetFigure(Figure_t *figure, int setting) {
  static Figure_t result = {0};
  static int size = 0;

  if (figure != NULL) {
    result = *figure;
  } else if (setting > NO_ACTION) {
    size = setting;
    int memory_fail = allocate_matrix(&result.matrix, size, size);
    if (memory_fail) {
      result.type = -1;
    }
  } else if (setting == REMOVE) {
    free_matrix(&result.matrix, size);
  }

  return result;
}