/**
 * @file s21_process_input.c
 * @author aminaall (aminaall@student.21-school.ru)
 * @brief Обработка данных фронтендом, полученных из контроллера. Используется
 * для дальнейшей передачи в бэкенд через контроллер
 * @version 1.0
 * @date 2025-02-25
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "s21_process_input.h"

UserAction_t process_input(int input_key) {
  UserAction_t result = Up;
  switch (tolower(input_key)) {
    case KEY_LEFT:
      result = Left;
      break;

    case KEY_RIGHT:
      result = Right;
      break;

    case KEY_DOWN:
      result = Down;
      break;

    case 'z':
      result = Action;
      break;

    case 'p':
      result = Pause;
      break;

    case '\n':
    case ' ':
      result = Start;
      break;

    case 'q':
      result = Terminate;
      break;

    default:
      break;
  }
  return result;
}