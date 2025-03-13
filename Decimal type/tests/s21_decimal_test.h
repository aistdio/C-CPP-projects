#include <check.h>

#include "../s21_decimal.h"

int s21_equals(s21_decimal a, s21_decimal b);

Suite *arithmetic_suite(void);
Suite *comparsion_suite(void);
Suite *conversion_suite(void);
Suite *round_suite(void);