#ifndef S21_FSM_H__
#define S21_FSM_H__

#include "s21_actions.h"
#include "s21_backend.h"
#include "s21_time_management.h"

void fsm_state(GameState_t State);
void fsm_start();
void fsm_spawn_figure();
void fsm_falling();
void fsm_action(GameState_t Action);
void fsm_attaching();
void fsm_gameover();
void fsm_pause();
void fsm_terminate();

#endif  // S21_FSM_H__