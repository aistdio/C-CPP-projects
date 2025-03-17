/**
 * @file s21_front_objects.h
 * @author aminaall (aminaall@student.21-school.ru)
 * @brief Необходимые структуры для работы фронтенда
 * @version 1.0
 * @date 2025-02-25
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef S21_FRONT_OBJECTS_H__
#define S21_FRONT_OBJECTS_H__

/**
 * @brief Параметры экрана и масштабирования кадра игры
 *
 */
typedef struct {
  int width;
  int width_scale;
  int height;
  int height_scale;
  int scaled_width;
  int scaled_height;
} ScreenInfo_t;

#endif  // S21_FRONT_OBJECTS_H__