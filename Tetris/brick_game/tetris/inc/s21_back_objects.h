/**
 * @file s21_back_objects.h
 * @author aminaall
 * @brief Необходимые структуры для работы бэкенда
 * @version 1.0
 * @date 2025-02-24
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef S21_BACK_OBJECTS_H_
#define S21_BACK_OBJECTS_H_

#include "s21_common_objects.h"

/**
 * @brief Состояния игры
 *
 */
typedef enum {
  State_Start = Start,
  State_Spawn = 10,
  State_Falling = 11,
  State_Action_Rotate = Action,
  State_Action_Left = Left,
  State_Action_Right = Right,
  State_Action_Down = Down,
  State_Attaching = 12,
  State_GameOver = 13,
  State_Pause = Pause,
  State_Terminate = Terminate,
} GameState_t;

/**
 * @brief Структура всех фигур игры
 *
 * @param matrix [ ТИП фигуры (из задания) ][ X ][ Y ]
 * @param max_figure_size - максимальный размер квадратных матриц matrix
 * @param types_total - сколько всего ТИПов фигур
 * @param type_sizes [ ТИП ] - размер типа фигуры
 * @param anchors_x [ ТИП ] - опорная точка по X для поворота фигуры
 * определенного ТИПа
 * @param anchors_y [ ТИП ] - опорная точка по Y для поворота фигуры
 * определенного ТИПа
 *
 */
typedef struct {
  int ***matrix;
  int max_figure_size;
  int types_total;
  int *type_sizes;
  int *anchors_x;
  int *anchors_y;
} Figures_t;

/**
 * @brief Структура текущей живой (последней живой, если живой нету) фигуры
 *
 * @param matrix [ X ][ Y ] матрица текущей фигуры
 * @param x - X
 * @param y - Y
 * @param type ТИП текущей матрицы
 * @param rotation_type тип применяемой ротации - по часовой или против часовой
 * стрелки (в текущей вариации игры оставлен только вариант против часовой
 * стрелки)
 * @param is_alive жива ли фигура и может ли она перемещаться. Не жива, если
 * происходит коллизия с нижней стороны.
 * (Под живой понимается та фигура, которая ещё может падать)
 *
 */
typedef struct {
  int **matrix;
  int x;
  int y;
  int type;
  int rotation_type;
  int is_alive;
} Figure_t;

/**
 * @brief Специальные значения для синглтона Figure_t
 *
 */
typedef enum { NO_ACTION = 0, REMOVE = -1 } FigureAction_t;

/**
 * @brief Определение стороны поворота фигур
 *
 */
typedef enum { CLOCKWISE = 1, COUNTER_CLOCKWISE } Rotation_t;

/**
 * @brief Опорные точки по X и Y, нужные для поворота фигур
 *
 */
typedef enum { anchorX, anchorY } Anchors_t;

/**
 * @brief Заданный размер поля gameInfo.field контроллером
 *
 */
typedef struct {
  int width;
  int height;
} FieldSize_t;

#endif  // S21_BACK_OBJECTS_H_