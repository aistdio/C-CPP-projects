/**
 * @file s21_common_objects.h
 * @author aminaall (aminaall@student.21-school.ru)
 * @brief Общие структуры бэкенда и фронтенда, которые были вынесены в отдельный
 * файл для избежания повторного объявления
 * @version 1.0
 * @date 2025-02-25
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef S21_COMMON_OBJECT_H__
#define S21_COMMON_OBJECT_H__

/**
 * @brief Данные игры, изменяемые в бэкенде и отрисовываемые на фронтенде
 *
 */
typedef struct {
  int **field;
  int **next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;

/**
 * @brief Действие пользователя
 *
 */
typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action
} UserAction_t;

/**
 * @brief Состояния паузы, хранящиеся в GameInfo_t.pause. Используются в
 * основном для отрисовки правильного кадра фронтендом и игнорирования
 * недоступных действий пользователя бэкендом (к примеру, пользователь при
 * нажатии на Pause сможет сменить состояние паузы с Paused на No_Pause и
 * наоборот, однако действие будет проигнорировано, если текущим состоянием
 * является START_GAME_PAUSE, GAME_OVER_PAUSE или EXIT_PAUSE, на которые
 * пользователь соответственно не может повлиять нажатием клавиши Pause)
 *
 */
typedef enum {
  NO_PAUSE = 0,
  PAUSED,
  START_GAME_PAUSE,
  GAME_OVER_PAUSE,
  EXIT_PAUSE,
} Pause_t;

#endif  // S21_COMMON_OBJECT_H__