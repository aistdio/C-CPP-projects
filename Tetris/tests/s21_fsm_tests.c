#include "s21_tetris_tests.h"

START_TEST(fsm_start_1) {
  GameInfo_t gameInfo = {0};
  int width = 10;
  int height = 20;
  init_backend(&gameInfo, width, height);

  int expected = 0;
  ck_assert_int_eq(gameInfo.pause, START_GAME_PAUSE);
  fsm_start();
  ck_assert_int_eq(gameInfo.pause, expected);

  gameInfo.pause = GAME_OVER_PAUSE;
  fsm_start();
  ck_assert_int_eq(gameInfo.pause, START_GAME_PAUSE);

  remove_backend();
}
END_TEST

START_TEST(fsm_spawn_figure_1) {
  GameInfo_t gameInfo = {0};
  int width = 10;
  int height = 20;
  init_backend(&gameInfo, width, height);

  Figure_t figure = getSetFigure(NULL, NO_ACTION);
  ck_assert_int_eq(figure.is_alive, 0);

  int expected = 1;
  fsm_spawn_figure();
  figure = getSetFigure(NULL, NO_ACTION);
  ck_assert_int_eq(figure.is_alive, expected);

  remove_backend();
}
END_TEST

START_TEST(fsm_falling_1) {
  GameInfo_t gameInfo = {0};
  int width = 10;
  int height = 20;
  init_backend(&gameInfo, width, height);

  Figures_t figures = getSetFigures(NULL);
  Figure_t figure = getSetFigure(NULL, NO_ACTION);
  spawn_figure(&gameInfo, &figures, &figure, 5, 5, 0);

  int collided = check_bottom_collision(gameInfo.field, &figures, &figure);
  ck_assert_int_eq(collided, 0);
  for (int i = 0; i < 100; i++) {
    fsm_falling();
  }
  figure = getSetFigure(NULL, NO_ACTION);
  int expected = 1;
  collided = check_bottom_collision(gameInfo.field, &figures, &figure);
  ck_assert_int_eq(collided, expected);

  remove_backend();
}
END_TEST

START_TEST(fsm_action_1) {
  GameInfo_t initial = {0};
  int width = 10;
  int height = 20;
  init_backend(&initial, width, height);
  GameInfo_t *gameInfo = getSetGameInfo(NULL);
  gameInfo->pause = 0;

  Figures_t figures = getSetFigures(NULL);
  Figure_t figure = getSetFigure(NULL, NO_ACTION);
  spawn_figure(gameInfo, &figures, &figure, 5, 5, 0);
  ck_assert_int_eq(gameInfo->field[5][6], 1);
  ck_assert_int_eq(gameInfo->field[6][18], 0);
  getSetFigure(&figure, NO_ACTION);

  fsm_action(State_Action_Left);
  fsm_action(State_Action_Right);
  fsm_action(State_Action_Rotate);
  fsm_action(State_Action_Down);

  ck_assert_int_eq(gameInfo->field[5][6], 0);
  ck_assert_int_eq(gameInfo->field[6][18], 1);

  remove_backend();
}
END_TEST

START_TEST(fsm_attaching_1) {
  GameInfo_t gameInfo = {0};
  int width = 10;
  int height = 20;
  init_backend(&gameInfo, width, height);

  int expected = 0;
  for (int i = 0; i < width; i++) {
    gameInfo.field[i][5] = 1;
  }

  fsm_attaching();

  for (int i = 0; i < width; i++) {
    ck_assert_int_eq(gameInfo.field[i][5], expected);
  }

  remove_backend();
}
END_TEST

START_TEST(fsm_gameover_1) {
  GameInfo_t gameInfo = {0};
  int width = 10;
  int height = 20;
  init_backend(&gameInfo, width, height);

  ck_assert_int_eq(gameInfo.pause, START_GAME_PAUSE);
  fsm_gameover();
  ck_assert_int_eq(gameInfo.pause, GAME_OVER_PAUSE);

  remove_backend();
}
END_TEST

START_TEST(fsm_pause_1) {
  GameInfo_t gameInfo = {0};
  int width = 10;
  int height = 20;
  init_backend(&gameInfo, width, height);

  gameInfo.pause = 0;
  fsm_pause();
  ck_assert_int_eq(gameInfo.pause, 1);
  fsm_pause();
  ck_assert_int_eq(gameInfo.pause, 0);

  remove_backend();
}
END_TEST

START_TEST(fsm_terminate_1) {
  GameInfo_t gameInfo = {0};
  int width = 10;
  int height = 20;

  init_backend(&gameInfo, width, height);
  ck_assert_ptr_nonnull(gameInfo.field);
  ck_assert_ptr_nonnull(gameInfo.next);
  ck_assert_int_eq(gameInfo.pause, START_GAME_PAUSE);

  fsm_terminate();
  ck_assert_ptr_null(gameInfo.field);
  ck_assert_ptr_null(gameInfo.next);
  ck_assert_int_eq(gameInfo.pause, EXIT_PAUSE);
}
END_TEST

START_TEST(fsm_state_1) {
  GameInfo_t gameInfo = {0};
  int width = 10;
  int height = 20;

  init_backend(&gameInfo, width, height);

  fsm_state(State_Start);
  fsm_state(State_Spawn);
  fsm_state(State_Falling);
  fsm_state(State_Action_Rotate);
  fsm_state(State_Action_Left);
  fsm_state(State_Action_Right);
  fsm_state(State_Action_Down);
  fsm_state(State_Attaching);
  fsm_state(State_Pause);
  fsm_state(State_Pause);
  fsm_state(State_GameOver);

  int passed = 0;
  for (int i = 0; i < width; i++) {
    for (int j = MATRIX_V_OFFSET; j < height + MATRIX_V_OFFSET; j++) {
      if (gameInfo.field[i][j] != 0) {
        passed = 1;
      }
    }
  }
  int expected = 1;
  ck_assert_int_eq(passed, expected);

  fsm_state(State_Terminate);
  ck_assert_ptr_null(gameInfo.field);
  ck_assert_ptr_null(gameInfo.next);
  ck_assert_int_eq(gameInfo.pause, EXIT_PAUSE);
}
END_TEST

Suite *fsm_suite(void) {
  Suite *s1 = suite_create("FSM");

  TCase *tc1_1 = tcase_create("fsm_start");
  tcase_add_test(tc1_1, fsm_start_1);

  TCase *tc1_2 = tcase_create("fsm_spawn_figure");
  tcase_add_test(tc1_2, fsm_spawn_figure_1);

  TCase *tc1_3 = tcase_create("fsm_falling");
  tcase_add_test(tc1_3, fsm_falling_1);

  TCase *tc1_4 = tcase_create("fsm_action");
  tcase_add_test(tc1_4, fsm_action_1);

  TCase *tc1_5 = tcase_create("fsm_attaching");
  tcase_add_test(tc1_5, fsm_attaching_1);

  TCase *tc1_6 = tcase_create("fsm_gameover");
  tcase_add_test(tc1_6, fsm_gameover_1);

  TCase *tc1_7 = tcase_create("fsm_pause");
  tcase_add_test(tc1_7, fsm_pause_1);

  TCase *tc1_8 = tcase_create("fsm_terminate");
  tcase_add_test(tc1_8, fsm_terminate_1);

  TCase *tc1_9 = tcase_create("fsm_state");
  tcase_add_test(tc1_9, fsm_state_1);

  suite_add_tcase(s1, tc1_1);
  suite_add_tcase(s1, tc1_2);
  suite_add_tcase(s1, tc1_3);
  suite_add_tcase(s1, tc1_4);
  suite_add_tcase(s1, tc1_5);
  suite_add_tcase(s1, tc1_6);
  suite_add_tcase(s1, tc1_7);
  suite_add_tcase(s1, tc1_8);
  suite_add_tcase(s1, tc1_9);

  return s1;
}