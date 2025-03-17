/**
 * @file s21_fsm.c
 * @author aminaall (aminaall@student.21-school.ru)
 * @brief FSM states из диаграммы FSM*.pdf
 * @version 1.0
 * @date 2025-02-24
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "s21_fsm.h"

void fsm_state(GameState_t State) {
  switch (State) {
    case State_Start:
      fsm_start();
      break;

    case State_Spawn:
      fsm_spawn_figure();
      break;

    case State_Falling:
      fsm_falling();
      break;

    case State_Action_Rotate:
    case State_Action_Left:
    case State_Action_Right:
    case State_Action_Down:
      fsm_action(State);
      break;

    case State_Attaching:
      fsm_attaching();
      break;

    case State_GameOver:
      fsm_gameover();
      break;

    case State_Pause:
      fsm_pause();
      break;

    case State_Terminate:
      fsm_terminate();
      break;
  }
}

/**
 * @brief Паузы влияют не только на доступность действий пользователя с текущей
 * фигурой, но и на отображаемый тип фрейма в фронтенде (gameover frame/gameplay
 * fram/etc.)
 *
 */
void fsm_start() {
  GameInfo_t *gameInfo = getSetGameInfo(NULL);
  if (gameInfo->pause == START_GAME_PAUSE) {
    gameInfo->pause = 0;
  } else if (gameInfo->pause == GAME_OVER_PAUSE) {
    resetGameInfo(gameInfo);
    stopCurrentFigure();
    gameInfo->pause = START_GAME_PAUSE;
  }
}

/**
 * @brief Спавним фигуру и добавляем матрицу следующей в gameInfo.next.
 * Возможен переход в GameOver (этого нет в диаграмме FSM, поскольку это не
 * предусматривалось заданием и является необязательным дополнением к игре)
 *
 */
void fsm_spawn_figure() {
  GameInfo_t *gameInfo = getSetGameInfo(NULL);
  FieldSize_t fieldSize = getFieldSize(NULL, NULL);
  Figures_t figures = getSetFigures(NULL);
  Figure_t currentFigure = getSetFigure(NULL, NO_ACTION);
  int mid_with_offset =
      (fieldSize.width / 2) - (figures.max_figure_size / 2) + 1;

  static int type = -1;
  if (type == -1) type = get_random_from_zero(figures.types_total);

  spawn_figure(gameInfo, &figures, &currentFigure, mid_with_offset,
               SPAWN_FIGURE_Y, type);
  int attaching_on_spawn = move_down(gameInfo, &currentFigure);
  getSetFigure(&currentFigure, NO_ACTION);

  type = get_random_from_zero(figures.types_total);
  copy_cubic_matrix(gameInfo->next, figures.matrix[type],
                    figures.max_figure_size);
  multiply_matrix(gameInfo->next, figures.max_figure_size, type + 1);

  if (attaching_on_spawn) fsm_state(State_GameOver);
}

/**
 * @brief Падение, возможен переход в состояние Attaching
 *
 */
void fsm_falling() {
  GameInfo_t *gameInfo = getSetGameInfo(NULL);
  Figure_t currentFigure = getSetFigure(NULL, NO_ACTION);

  int attached = move_down(gameInfo, &currentFigure);
  if (attached) fsm_state(State_Attaching);

  getSetFigure(&currentFigure, NO_ACTION);
}

/**
 * @brief Обработка всех возможных действий пользователя с текущей живой
 * фигурой. Возможен переход в состояние Attaching
 *
 * @param Action действие пользователя
 */
void fsm_action(GameState_t Action) {
  GameInfo_t *gameInfo = getSetGameInfo(NULL);
  Figures_t figures = getSetFigures(NULL);
  Figure_t currentFigure = getSetFigure(NULL, NO_ACTION);

  if (currentFigure.is_alive && !gameInfo->pause) {
    if (Action == State_Action_Left) {
      move_left_side(gameInfo, &figures, &currentFigure);
    } else if (Action == State_Action_Right) {
      move_right_side(gameInfo, &figures, &currentFigure);
    } else if (Action == State_Action_Rotate) {
      rotate_figure(gameInfo, &figures, &currentFigure, COUNTER_CLOCKWISE);
    } else if (Action == State_Action_Down) {
      while (!move_down(gameInfo, &currentFigure));
      fsm_state(State_Attaching);
    }
  }

  getSetFigure(&currentFigure, NO_ACTION);
}

/**
 * @brief Обработка ситуации, когда текущая живая фигура коснулась с нижней
 * стороны другой поверхности (до перехода в это состояние параметр фигуры
 * is_alive уже стал false)
 *
 */
void fsm_attaching() {
  GameInfo_t *gameInfo = getSetGameInfo(NULL);

  int linesDeleted = deleteAttachedLines(gameInfo);
  if (linesDeleted) {
    calculate_score(&(gameInfo->score), linesDeleted);
    if (gameInfo->score > gameInfo->high_score) {
      gameInfo->high_score = gameInfo->score;
    }
    if (gameInfo->level < MAX_LEVEL) {
      calculate_level(&(gameInfo->level), gameInfo->score);
    }
  }
}

/**
 * @brief Этого состояния нет в диаграмме FSM, поскольку это не
 * предусматривалось заданием и является необязательным дополнением к игре.
 * Возможнен переход из gameover в start при нажатии на enter
 *
 */
void fsm_gameover() {
  GameInfo_t *gameInfo = getSetGameInfo(NULL);
  gameInfo->pause = GAME_OVER_PAUSE;
}

/**
 * @brief С состоянием пазуы можно взаимодействовать только в том случае, если
 * этот параметр уже не занят другим состонияем (к примеру, pause может быть
 * равен макросу GAME_OVER_PAUSE, означающий, что сейчас мы находимся в
 * состоянии окончания игры и пользователь взаимодействовать с паузой не может).
 * Макросы пауз находятся в common/s21_common_objects.h
 *
 */
void fsm_pause() {
  GameInfo_t *gameInfo = getSetGameInfo(NULL);
  if (gameInfo->pause == 0)
    gameInfo->pause = 1;
  else if (gameInfo->pause == 1)
    gameInfo->pause = 0;
}

/**
 * @brief Выход из игры
 *
 */
void fsm_terminate() {
  FieldSize_t fieldSize = getFieldSize(NULL, NULL);
  GameInfo_t *gameInfo = getSetGameInfo(NULL);
  save_tetris_db(*gameInfo, fieldSize.width, fieldSize.height);
  remove_backend();
  gameInfo->pause = EXIT_PAUSE;
}