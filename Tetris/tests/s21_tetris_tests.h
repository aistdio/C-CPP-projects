#ifndef S21_TETRIS_TESTS_H_
#define S21_TETRIS_TESTS_H_

#include <check.h>

#include "s21_backend.h"

Suite *memory_suite(void);
Suite *time_management_suite(void);
Suite *game_stats_suite(void);
Suite *matrix_operations_suite(void);
Suite *file_processing_suite(void);
Suite *figures_suite(void);
Suite *actions_suite(void);
Suite *backend_logic_suite(void);
Suite *fsm_suite(void);
Suite *matrix_checks_suite(void);
Suite *user_input_suite(void);

#endif  // S21_TETRIS_TESTS_H_