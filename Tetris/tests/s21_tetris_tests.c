#include "s21_tetris_tests.h"

int main() {
  int failed = 0;
  SRunner *sr;
  sr = srunner_create(NULL);

  srunner_set_fork_status(sr, CK_NOFORK);  // Valgrind

  srunner_add_suite(sr, memory_suite());
  srunner_add_suite(sr, time_management_suite());
  srunner_add_suite(sr, game_stats_suite());
  srunner_add_suite(sr, matrix_operations_suite());
  srunner_add_suite(sr, file_processing_suite());
  srunner_add_suite(sr, figures_suite());
  srunner_add_suite(sr, actions_suite());
  srunner_add_suite(sr, backend_logic_suite());
  srunner_add_suite(sr, fsm_suite());
  srunner_add_suite(sr, matrix_checks_suite());
  srunner_add_suite(sr, user_input_suite());
  failed = srunner_ntests_failed(sr);

  srunner_run_all(sr, CK_NORMAL);
  srunner_free(sr);
  return (failed == 0) ? 0 : 1;
}