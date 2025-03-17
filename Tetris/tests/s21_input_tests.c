#include "s21_tetris_tests.h"

START_TEST(userInput_1) {
  userInput(Start, false);
  userInput(Pause, false);
  userInput(Pause, false);
  userInput(Action, false);
  userInput(Up, false);
  userInput(Left, false);
  userInput(Right, false);
  userInput(Down, false);

  GameInfo_t *gameInfo = getSetGameInfo(NULL);
  ck_assert_ptr_nonnull(gameInfo);
  ck_assert_ptr_nonnull(gameInfo->field);
  ck_assert_ptr_nonnull(gameInfo->next);

  int expected = 1;
  int passed = 0;
  while (!passed) {
    updateCurrentState();
    for (int y = MATRIX_V_OFFSET; y < HEIGHT + MATRIX_V_OFFSET; y++) {
      for (int x = MATRIX_H_OFFSET; x < WIDTH + MATRIX_H_OFFSET; x++) {
        if (gameInfo->field[x][y] != 0) passed = 1;
      }
    }
  }
  ck_assert_int_eq(passed, expected);

  userInput(Terminate, false);
  ck_assert_ptr_null(gameInfo->field);
  ck_assert_ptr_null(gameInfo->next);
}
END_TEST

Suite *user_input_suite(void) {
  Suite *s1 = suite_create("User input");

  TCase *tc1_1 = tcase_create("userInput");
  tcase_add_test(tc1_1, userInput_1);

  suite_add_tcase(s1, tc1_1);

  return s1;
}