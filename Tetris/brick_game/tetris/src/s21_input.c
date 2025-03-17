/**
 * @file s21_input.c
 * @author aminaall (aminaall@student.21-school.ru)
 * @brief userInput принимает обработанное фронтом действие (action)
 * пользователя и вызывает соответствующий fsm_state
 *
 * Однако в начале, поскольку выступает в качестве первой функции, вызываемой
 * контроллером, данная функция вызывает функцию-иницилизатор бэкенда (которая
 * возвращает memory_fail == 1 в случае, если один из вызываемых calloc не смог
 * выделить память)
 *
 * @version 1.0
 * @date 2025-02-24
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "s21_input.h"

void userInput(UserAction_t action, bool hold __attribute__((unused))) {
  static GameInfo_t initial_gameInfo = {0};
  static int first_time = 1;
  if (first_time) {
    first_time = 0;
    int memory_fail = init_backend(&initial_gameInfo, WIDTH, HEIGHT);
    if (memory_fail) {
      action = Terminate;
    }
  }

  switch (action) {
    case Up:
      break;

    case Left:
      fsm_state(State_Action_Left);
      break;

    case Right:
      fsm_state(State_Action_Right);
      break;

    case Down:
      fsm_state(State_Action_Down);
      break;

    case Action:
      fsm_state(State_Action_Rotate);
      break;

    case Pause:
      fsm_state(State_Pause);
      break;

    case Start:
      fsm_state(State_Start);
      break;

    case Terminate:
      fsm_state(State_Terminate);
      break;
  }
}