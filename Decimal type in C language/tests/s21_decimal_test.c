#include "s21_decimal_test.h"

int s21_equals(s21_decimal a, s21_decimal b) {
  return (a.bits[0] == b.bits[0]) && (a.bits[1] == b.bits[1]) &&
         (a.bits[2] == b.bits[2]) && ((a.bits[3] == b.bits[3]));
}

int main(void) {
  int failed = 0;
  SRunner *sr;
  sr = srunner_create(NULL);
  srunner_add_suite(sr, arithmetic_suite());
  srunner_add_suite(sr, comparsion_suite());
  srunner_add_suite(sr, conversion_suite());
  srunner_add_suite(sr, round_suite());
  failed = srunner_ntests_failed(sr);

  srunner_run_all(sr, CK_NORMAL);
  srunner_free(sr);
  return (failed == 0) ? 0 : 1;
}