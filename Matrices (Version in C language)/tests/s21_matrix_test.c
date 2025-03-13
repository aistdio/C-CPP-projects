#include "./../s21_matrix.h"

#include <check.h>

START_TEST(s21_matrix_create_correct) {
  matrix_t a;
  int arows = 3;
  int acolumns = 4;

  int result = s21_create_matrix(arows, acolumns, &a);
  int expected = 0;

  double avalue = 0.123456799;
  for (int i = 0; i < arows; i++)
    for (int j = 0; j < acolumns; j++) a.matrix[i][j] = avalue;

  s21_remove_matrix(&a);

  ck_assert_int_eq(result, expected);
}
END_TEST

START_TEST(s21_matrix_create_incorrect_rows) {
  matrix_t a;
  int arows = 0;
  int acolumns = 4;

  int result = s21_create_matrix(arows, acolumns, &a);
  int expected = 1;

  ck_assert_int_eq(result, expected);
}
END_TEST

START_TEST(s21_matrix_create_incorrect_columns) {
  matrix_t a;
  int arows = 3;
  int acolumns = 0;

  int result = s21_create_matrix(arows, acolumns, &a);
  int expected = 1;

  ck_assert_int_eq(result, expected);
}
END_TEST

START_TEST(s21_matrix_remove) {
  matrix_t a;
  int arows = 3;
  int acolumns = 2;

  int result = s21_create_matrix(arows, acolumns, &a);
  int expected = 0;

  s21_remove_matrix(&a);
  ck_assert_int_eq(result, expected);
}
END_TEST

START_TEST(s21_matrix_eq_correct_in_precision) {
  matrix_t a;
  int arows = 3;
  int acolumns = 3;

  matrix_t b;
  int brows = 3;
  int bcolumns = 3;

  s21_create_matrix(arows, acolumns, &a);
  s21_create_matrix(brows, bcolumns, &b);

  double avalue = 0.123456700;
  double bvalue = 0.123456710;
  for (int i = 0; i < arows; i++)
    for (int j = 0; j < acolumns; j++)
      a.matrix[i][j] = avalue, b.matrix[i][j] = bvalue;

  int result = s21_eq_matrix(&a, &b);
  int expected = 1;

  s21_remove_matrix(&a);
  s21_remove_matrix(&b);

  ck_assert_int_eq(result, expected);
}
END_TEST

START_TEST(s21_matrix_eq_incorrect_in_precision) {
  matrix_t a;
  int arows = 3;
  int acolumns = 3;

  matrix_t b;
  int brows = 3;
  int bcolumns = 3;

  s21_create_matrix(arows, acolumns, &a);
  s21_create_matrix(brows, bcolumns, &b);

  double avalue = 0.123456000;
  double bvalue = 0.123456100;
  for (int i = 0; i < arows; i++)
    for (int j = 0; j < acolumns; j++)
      a.matrix[i][j] = avalue, b.matrix[i][j] = bvalue;

  int result = s21_eq_matrix(&a, &b);
  int expected = 0;

  s21_remove_matrix(&a);
  s21_remove_matrix(&b);

  ck_assert_int_eq(result, expected);
}
END_TEST

START_TEST(s21_matrix_eq_incorrect_in_rows) {
  matrix_t a;
  int arows = 3;
  int acolumns = 3;

  matrix_t b;
  int brows = 4;
  int bcolumns = 3;

  s21_create_matrix(arows, acolumns, &a);
  s21_create_matrix(brows, bcolumns, &b);

  double avalue = 0.123456789;
  double bvalue = 0.123456789;
  for (int i = 0; i < arows; i++)
    for (int j = 0; j < acolumns; j++)
      a.matrix[i][j] = avalue, b.matrix[i][j] = bvalue;

  int result = s21_eq_matrix(&a, &b);
  int expected = 0;

  s21_remove_matrix(&a);
  s21_remove_matrix(&b);

  ck_assert_int_eq(result, expected);
}
END_TEST

START_TEST(s21_matrix_eq_incorrect_in_columns) {
  matrix_t a;
  int arows = 3;
  int acolumns = 3;

  matrix_t b;
  int brows = 3;
  int bcolumns = 2;

  s21_create_matrix(arows, acolumns, &a);
  s21_create_matrix(brows, bcolumns, &b);

  int result = s21_eq_matrix(&a, &b);
  int expected = 0;

  s21_remove_matrix(&a);
  s21_remove_matrix(&b);

  ck_assert_int_eq(result, expected);
}
END_TEST

START_TEST(s21_matrix_sum_incorrect_nullptr) {
  ck_assert_int_eq(s21_sum_matrix(NULL, NULL, NULL), 1);
}
END_TEST

START_TEST(s21_matrix_sum_incorrect_result_matrix_size) {
  matrix_t a;
  int arows = 2;
  int acolumns = 2;

  matrix_t b;
  int brows = 1;
  int bcolumns = 1;

  s21_create_matrix(arows, acolumns, &a);
  s21_create_matrix(brows, bcolumns, &b);

  matrix_t c;

  int result = s21_sum_matrix(&a, &b, &c);
  int expected = 2;

  s21_remove_matrix(&a);
  s21_remove_matrix(&b);

  ck_assert_int_eq(result, expected);
}
END_TEST

START_TEST(s21_matrix_sum_incorrect_matrix_size) {
  matrix_t a;
  int arows = 3;
  int acolumns = 3;

  matrix_t b;
  int brows = 4;
  int bcolumns = 2;

  s21_create_matrix(arows, acolumns, &a);
  s21_create_matrix(brows, bcolumns, &b);

  matrix_t c;

  int result = s21_sum_matrix(&a, &b, &c);
  int expected = 2;

  s21_remove_matrix(&a);
  s21_remove_matrix(&b);

  ck_assert_int_eq(result, expected);
}
END_TEST

START_TEST(s21_matrix_sum_correct_equals) {
  matrix_t a;
  int arows = 4;
  int acolumns = 4;
  matrix_t b;
  int brows = 4;
  int bcolumns = 4;
  matrix_t c;
  matrix_t expected;
  int erows = 4;
  int ecolumns = 4;

  s21_create_matrix(arows, acolumns, &a);
  s21_create_matrix(brows, bcolumns, &b);
  s21_create_matrix(erows, ecolumns, &expected);

  s21_add_number(&a, 1.0);
  s21_add_number(&b, 3.0);

  ck_assert_int_eq(s21_sum_matrix(&a, &b, &c), 0);

  s21_add_number(&expected, 4.0);

  ck_assert_int_eq(s21_eq_matrix(&c, &expected), 1);

  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&c);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(s21_matrix_sum_correct_not_equals) {
  matrix_t a;
  int arows = 4;
  int acolumns = 4;
  matrix_t b;
  int brows = 4;
  int bcolumns = 4;
  matrix_t c;
  matrix_t expected;
  int erows = 4;
  int ecolumns = 4;

  s21_create_matrix(arows, acolumns, &a);
  s21_create_matrix(brows, bcolumns, &b);
  s21_create_matrix(erows, ecolumns, &expected);

  s21_add_number(&a, 1.0);
  s21_add_number(&b, 3.0);

  ck_assert_int_eq(s21_sum_matrix(&a, &b, &c), 0);

  s21_add_number(&expected, 5.0);

  ck_assert_int_eq(s21_eq_matrix(&c, &expected), 0);

  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&c);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(s21_matrix_sub_incorrect_nullptr) {
  ck_assert_int_eq(s21_sub_matrix(NULL, NULL, NULL), 1);
}
END_TEST

START_TEST(s21_matrix_sub_incorrect_result_matrix_size) {
  matrix_t a;
  int arows = 3;
  int acolumns = 3;

  matrix_t b;
  int brows = 1;
  int bcolumns = 1;

  s21_create_matrix(arows, acolumns, &a);
  s21_create_matrix(brows, bcolumns, &b);

  matrix_t c;

  int result = s21_sub_matrix(&a, &b, &c);
  int expected = 2;

  s21_remove_matrix(&a);
  s21_remove_matrix(&b);

  ck_assert_int_eq(result, expected);
}
END_TEST

START_TEST(s21_matrix_sub_incorrect_matrix_size) {
  matrix_t a;
  int arows = 3;
  int acolumns = 3;

  matrix_t b;
  int brows = 4;
  int bcolumns = 2;

  s21_create_matrix(arows, acolumns, &a);
  s21_create_matrix(brows, bcolumns, &b);

  matrix_t c;

  int result = s21_sum_matrix(&a, &b, &c);
  int expected = 2;

  s21_remove_matrix(&a);
  s21_remove_matrix(&b);

  ck_assert_int_eq(result, expected);
}
END_TEST

START_TEST(s21_matrix_sub_correct_equals) {
  matrix_t a;
  int arows = 4;
  int acolumns = 4;
  matrix_t b;
  int brows = 4;
  int bcolumns = 4;
  matrix_t c;
  matrix_t expected;
  int erows = 4;
  int ecolumns = 4;

  s21_create_matrix(arows, acolumns, &a);
  s21_create_matrix(brows, bcolumns, &b);
  s21_create_matrix(erows, ecolumns, &expected);

  s21_add_number(&a, 1.0);
  s21_add_number(&b, 3.0);

  ck_assert_int_eq(s21_sub_matrix(&a, &b, &c), 0);

  s21_add_number(&expected, -2.0);

  ck_assert_int_eq(s21_eq_matrix(&c, &expected), 1);

  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&c);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(s21_matrix_sub_correct_not_equals) {
  matrix_t a;
  int arows = 4;
  int acolumns = 4;
  matrix_t b;
  int brows = 4;
  int bcolumns = 4;
  matrix_t c;
  matrix_t expected;
  int erows = 4;
  int ecolumns = 4;

  s21_create_matrix(arows, acolumns, &a);
  s21_create_matrix(brows, bcolumns, &b);
  s21_create_matrix(erows, ecolumns, &expected);

  s21_add_number(&a, 1.0);
  s21_add_number(&b, 3.0);

  ck_assert_int_eq(s21_sub_matrix(&a, &b, &c), 0);

  s21_add_number(&expected, 5.0);

  ck_assert_int_eq(s21_eq_matrix(&c, &expected), 0);

  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&c);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(s21_matrix_mult_number_incorrect_nullptr) {
  ck_assert_int_eq(s21_mult_number(NULL, 0.0, NULL), 1);
}
END_TEST

START_TEST(s21_matrix_mult_number_incorrect_matrix_size) {
  matrix_t a;
  int arows = 3;
  int acolumns = 3;

  matrix_t b;

  s21_create_matrix(arows, acolumns, &a);

  int result = s21_mult_number(&a, INFINITY, &b);
  int expected = 2;

  s21_remove_matrix(&a);

  ck_assert_int_eq(result, expected);
}
END_TEST

START_TEST(s21_matrix_mult_number_correct) {
  matrix_t a;
  matrix_t b;
  int arows = 4;
  int acolumns = 4;

  s21_create_matrix(arows, acolumns, &a);

  s21_add_number(&a, 3.0);

  ck_assert_int_eq(s21_mult_number(&a, 2.0, &b), 0);

  matrix_t expected;
  s21_create_matrix(arows, acolumns, &expected);
  s21_add_number(&expected, 6.0);

  ck_assert_int_eq(s21_eq_matrix(&b, &expected), 1);

  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(s21_matrix_mult_nullptr) {
  ck_assert_int_eq(s21_mult_matrix(NULL, NULL, NULL), 1);
}
END_TEST

START_TEST(s21_matrix_mult_incorrect_size) {
  matrix_t a;
  int arows = 2;
  int acolumns = 2;

  matrix_t b;
  int brows = 4;
  int bcolumns = 4;

  s21_create_matrix(arows, acolumns, &a);
  s21_create_matrix(brows, bcolumns, &b);

  matrix_t c;

  int result = s21_mult_matrix(&a, &b, &c);
  int expected = 2;

  s21_remove_matrix(&a);
  s21_remove_matrix(&b);

  ck_assert_int_eq(result, expected);
}
END_TEST

START_TEST(s21_matrix_mult_correct) {
  matrix_t a;
  int arows = 2;
  int acolumns = 4;

  matrix_t b;
  int brows = 4;
  int bcolumns = 2;

  s21_create_matrix(arows, acolumns, &a);
  s21_create_matrix(brows, bcolumns, &b);

  s21_add_number(&a, 20.0);
  s21_add_number(&b, 4.0);

  matrix_t c;
  ck_assert_int_eq(s21_mult_matrix(&a, &b, &c), 0);

  matrix_t expect;
  s21_create_matrix(arows, bcolumns, &expect);
  s21_add_number(&expect, 320.0);

  ck_assert_int_eq(s21_eq_matrix(&c, &expect), 1);

  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&c);
  s21_remove_matrix(&expect);
}
END_TEST

START_TEST(s21_matrix_transpose_nullptr) {
  ck_assert_int_eq(s21_transpose(NULL, NULL), 1);
}
END_TEST

START_TEST(s21_matrix_transpose_incorrect_size) {
  matrix_t a;
  a.rows = 2;
  a.columns = 0;

  matrix_t c;

  ck_assert_int_eq(s21_transpose(&a, &c), 1);
}
END_TEST

START_TEST(s21_matrix_transpose_correct) {
  matrix_t a;
  int arows = 4;
  int acolumns = 2;

  s21_create_matrix(arows, acolumns, &a);

  for (int i = 0, counter = 1; i < arows; i++)
    for (int j = 0; j < acolumns; j++, counter++) a.matrix[i][j] = counter;

  matrix_t c;
  ck_assert_int_eq(s21_transpose(&a, &c), 0);

  matrix_t expect;
  s21_create_matrix(acolumns, arows, &expect);
  for (int i = 0; i < acolumns; i++)
    for (int j = 0, counter = i + 1; j < arows; j++, counter += 2)
      expect.matrix[i][j] = counter;

  ck_assert_int_eq(s21_eq_matrix(&c, &expect), 1);

  s21_remove_matrix(&a);
  s21_remove_matrix(&c);
  s21_remove_matrix(&expect);
}
END_TEST

START_TEST(s21_matrix_transpose_correct_square) {
  matrix_t a;
  int arows = 5;
  int acolumns = 5;

  s21_create_matrix(arows, acolumns, &a);

  for (int i = 0, counter = 1; i < arows; i++)
    for (int j = 0; j < acolumns; j++, counter++) a.matrix[i][j] = counter;

  matrix_t c;
  ck_assert_int_eq(s21_transpose(&a, &c), 0);

  matrix_t expect;
  s21_create_matrix(acolumns, arows, &expect);
  for (int i = 0; i < arows; i++)
    for (int j = 0, counter = i + 1; j < acolumns; j++, counter += 5)
      expect.matrix[i][j] = counter;

  ck_assert_int_eq(s21_eq_matrix(&c, &expect), 1);

  s21_remove_matrix(&a);
  s21_remove_matrix(&c);
  s21_remove_matrix(&expect);
}
END_TEST

START_TEST(s21_matrix_determinant_incorrent_null) {
  matrix_t A;
  A.rows = 1;
  A.columns = 1;
  ck_assert_int_eq(s21_determinant(&A, NULL), 2);
}
END_TEST

START_TEST(s21_matrix_determinant_incorrent_size) {
  matrix_t a;
  a.rows = 0;
  a.columns = 1;

  double res;
  ck_assert_int_eq(s21_determinant(&a, &res), 1);
}
END_TEST

START_TEST(s21_matrix_determinant_correct_1x1) {
  matrix_t a;
  int arows = 1;
  int acolumns = 1;

  s21_create_matrix(arows, acolumns, &a);

  s21_add_number(&a, 2.0);
  for (int i = 0; i < arows; i++) a.matrix[i][i] = -5.0;

  double result = -1.0;
  ck_assert_int_eq(s21_determinant(&a, &result), 0);

  double expected = -5.0;
  ck_assert_double_eq_tol(result, expected, 1e-6);

  s21_remove_matrix(&a);
}
END_TEST

START_TEST(s21_matrix_determinant_correct_2x2) {
  matrix_t a;
  int arows = 2;
  int acolumns = 2;

  s21_create_matrix(arows, acolumns, &a);

  a.matrix[0][0] = 0.;
  a.matrix[0][1] = 2.;
  a.matrix[1][0] = 5.;
  a.matrix[1][1] = 1.;

  double result = -1.0;
  ck_assert_int_eq(s21_determinant(&a, &result), 0);

  double expected = -10.0;
  ck_assert_double_eq_tol(result, expected, 1e-6);

  s21_remove_matrix(&a);
}
END_TEST

START_TEST(s21_matrix_determinant_correct_3x3) {
  matrix_t a;
  int arows = 3;
  int acolumns = 3;

  s21_create_matrix(arows, acolumns, &a);

  s21_add_number(&a, 2.0);
  for (int i = 0; i < arows; i++) a.matrix[i][i] = 5.0;

  double result = 0.0;
  ck_assert_int_eq(s21_determinant(&a, &result), 0);

  double expected = 81.0;
  ck_assert_double_eq_tol(result, expected, 1e-6);

  s21_remove_matrix(&a);
}
END_TEST

START_TEST(s21_matrix_determinant_correct_4x4) {
  matrix_t a;
  int arows = 4;
  int acolumns = 4;

  s21_create_matrix(arows, acolumns, &a);

  s21_add_number(&a, 2.0);
  for (int i = 0; i < arows; i++) a.matrix[i][i] = 0.0;

  double result = -1.0;
  ck_assert_int_eq(s21_determinant(&a, &result), 0);

  double expected = -48.0;
  ck_assert_double_eq_tol(result, expected, 1e-6);

  s21_remove_matrix(&a);
}
END_TEST

START_TEST(s21_matrix_determinant_correct_5x5) {
  matrix_t a;
  int arows = 5;
  int acolumns = 5;

  s21_create_matrix(arows, acolumns, &a);

  s21_add_number(&a, 0.0);
  for (int i = 0; i < arows; i++) a.matrix[i][i] = 0.0;
  a.matrix[4][4] = 0.0;

  double result = -1.0;
  ck_assert_int_eq(s21_determinant(&a, &result), 0);

  double expected = 0.0;
  ck_assert_double_eq_tol(result, expected, 1e-6);

  s21_remove_matrix(&a);
}
END_TEST

START_TEST(s21_matrix_determinant_correct_6x6) {
  matrix_t a;
  int arows = 6;
  int acolumns = 6;

  s21_create_matrix(arows, acolumns, &a);

  s21_add_number(&a, 2.0);
  for (int i = 0; i < arows; i++) a.matrix[i][i] = -5.0;
  a.matrix[4][4] = -23.0;
  a.matrix[0][0] = 17.0;

  double result = -1.0;
  ck_assert_int_eq(s21_determinant(&a, &result), 0);

  double expected = 80605.0;
  ck_assert_double_eq_tol(result, expected, 1e-6);

  s21_remove_matrix(&a);
}
END_TEST

START_TEST(s21_matrix_minor_incorrent_null) {
  matrix_t result;
  ck_assert_int_eq(s21_calc_complements(NULL, &result), 1);
}
END_TEST

START_TEST(s21_matrix_minor_incorrent_size) {
  matrix_t a;
  int arows = 5;
  int acolumns = 4;
  matrix_t result;

  s21_create_matrix(arows, acolumns, &a);

  ck_assert_int_eq(s21_calc_complements(&a, &result), 2);

  s21_remove_matrix(&a);
}
END_TEST

START_TEST(s21_matrix_minor_corrent_3x3) {
  matrix_t a;
  matrix_t result;
  int arows = 3;
  int acolumns = 3;

  s21_create_matrix(arows, acolumns, &a);
  a.matrix[0][0] = 1.;
  a.matrix[0][1] = 2.;
  a.matrix[0][2] = 3.;
  a.matrix[1][0] = 0.;
  a.matrix[1][1] = 4.;
  a.matrix[1][2] = 2.;
  a.matrix[2][0] = 5.;
  a.matrix[2][1] = 2.;
  a.matrix[2][2] = 1.;

  ck_assert_int_eq(s21_calc_complements(&a, &result), 0);

  matrix_t expceted;
  s21_create_matrix(arows, acolumns, &expceted);
  expceted.matrix[0][0] = 0.;
  expceted.matrix[0][1] = 10.;
  expceted.matrix[0][2] = -20.;
  expceted.matrix[1][0] = 4.;
  expceted.matrix[1][1] = -14.;
  expceted.matrix[1][2] = 8.;
  expceted.matrix[2][0] = -8.;
  expceted.matrix[2][1] = -2.;
  expceted.matrix[2][2] = 4.;

  ck_assert_int_eq(s21_eq_matrix(&result, &expceted), 1);

  s21_remove_matrix(&a);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expceted);
}
END_TEST

START_TEST(s21_matrix_inverse_incorrent_null) {
  matrix_t result;
  ck_assert_int_eq(s21_inverse_matrix(NULL, &result), 1);
}
END_TEST

START_TEST(s21_matrix_inverse_incorrent_size) {
  matrix_t a;
  int arows = 5;
  int acolumns = 4;
  matrix_t result;

  s21_create_matrix(arows, acolumns, &a);

  ck_assert_int_eq(s21_inverse_matrix(&a, &result), 2);

  s21_remove_matrix(&a);
}
END_TEST

START_TEST(s21_matrix_inverse_corrent_1x1) {
  matrix_t a;
  matrix_t result;
  int arows = 1;
  int acolumns = 1;

  s21_create_matrix(arows, acolumns, &a);
  a.matrix[0][0] = -62.;

  ck_assert_int_eq(s21_inverse_matrix(&a, &result), 0);

  matrix_t expceted;
  s21_create_matrix(arows, acolumns, &expceted);
  expceted.matrix[0][0] = -1. / 62.;

  ck_assert_int_eq(s21_eq_matrix(&result, &expceted), 1);

  s21_remove_matrix(&a);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expceted);
}
END_TEST

START_TEST(s21_matrix_inverse_corrent_2x2) {
  matrix_t a;
  matrix_t result;
  int arows = 2;
  int acolumns = 2;

  s21_create_matrix(arows, acolumns, &a);
  a.matrix[0][0] = 2.;
  a.matrix[0][1] = 5.;
  a.matrix[1][0] = 7.;
  a.matrix[1][1] = 3.;

  ck_assert_int_eq(s21_inverse_matrix(&a, &result), 0);

  matrix_t expceted;
  s21_create_matrix(arows, acolumns, &expceted);
  expceted.matrix[0][0] = -3. / 29.;
  expceted.matrix[0][1] = 5. / 29.;
  expceted.matrix[1][0] = 7. / 29.;
  expceted.matrix[1][1] = -2. / 29.;

  ck_assert_int_eq(s21_eq_matrix(&result, &expceted), 1);

  s21_remove_matrix(&a);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expceted);
}
END_TEST

START_TEST(s21_matrix_inverse_corrent_3x3) {
  matrix_t a;
  matrix_t result;
  int arows = 3;
  int acolumns = 3;

  s21_create_matrix(arows, acolumns, &a);
  a.matrix[0][0] = 2.;
  a.matrix[0][1] = 5.;
  a.matrix[0][2] = 7.;
  a.matrix[1][0] = 6.;
  a.matrix[1][1] = 3.;
  a.matrix[1][2] = 4.;
  a.matrix[2][0] = 5.;
  a.matrix[2][1] = -2.;
  a.matrix[2][2] = -3.;

  ck_assert_int_eq(s21_inverse_matrix(&a, &result), 0);

  matrix_t expceted;
  s21_create_matrix(arows, acolumns, &expceted);
  expceted.matrix[0][0] = 1.;
  expceted.matrix[0][1] = -1.;
  expceted.matrix[0][2] = 1.;
  expceted.matrix[1][0] = -38.;
  expceted.matrix[1][1] = 41.;
  expceted.matrix[1][2] = -34.;
  expceted.matrix[2][0] = 27.;
  expceted.matrix[2][1] = -29.;
  expceted.matrix[2][2] = 24.;

  ck_assert_int_eq(s21_eq_matrix(&result, &expceted), 1);

  s21_remove_matrix(&a);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expceted);
}
END_TEST

START_TEST(s21_matrix_inverse_corrent_4x4_det_0) {
  matrix_t a;
  matrix_t result;
  int arows = 4;
  int acolumns = 4;

  s21_create_matrix(arows, acolumns, &a);
  a.matrix[0][0] = 2.;
  a.matrix[0][1] = 5.;
  a.matrix[0][2] = 7.;
  a.matrix[0][3] = 7.;
  a.matrix[1][0] = 6.;
  a.matrix[1][1] = 3.;
  a.matrix[1][2] = 4.;
  a.matrix[1][3] = 4.;
  a.matrix[2][0] = 5.;
  a.matrix[2][1] = -2.;
  a.matrix[2][2] = -3.;
  a.matrix[2][3] = -3.;
  a.matrix[3][0] = 5.;
  a.matrix[3][1] = -2.;
  a.matrix[3][2] = -3.;
  a.matrix[3][3] = -3.;

  ck_assert_int_eq(s21_inverse_matrix(&a, &result), 2);

  s21_remove_matrix(&a);
}
END_TEST

START_TEST(s21_matrix_inverse_corrent_4x4) {
  matrix_t a;
  matrix_t result;
  int arows = 4;
  int acolumns = 4;

  s21_create_matrix(arows, acolumns, &a);
  a.matrix[0][0] = 2.;
  a.matrix[0][1] = 5.;
  a.matrix[0][2] = 7.;
  a.matrix[0][3] = 7.;
  a.matrix[1][0] = 6.;
  a.matrix[1][1] = 5.;
  a.matrix[1][2] = 4.;
  a.matrix[1][3] = 4.;
  a.matrix[2][0] = 5.;
  a.matrix[2][1] = -2.;
  a.matrix[2][2] = 5.;
  a.matrix[2][3] = -3.;
  a.matrix[3][0] = 5.;
  a.matrix[3][1] = -2.;
  a.matrix[3][2] = -3.;
  a.matrix[3][3] = 5.;

  ck_assert_int_eq(s21_inverse_matrix(&a, &result), 0);

  matrix_t expceted;
  s21_create_matrix(arows, acolumns, &expceted);
  expceted.matrix[0][0] = -13. / 163.;
  expceted.matrix[0][1] = 19. / 163.;
  expceted.matrix[0][2] = 15. / 326.;
  expceted.matrix[0][3] = 15. / 326.;
  expceted.matrix[1][0] = -14. / 163.;
  expceted.matrix[1][1] = 33. / 163.;
  expceted.matrix[1][2] = -17. / 163.;
  expceted.matrix[1][3] = -17. / 163.;
  expceted.matrix[2][0] = 37. / 326.;
  expceted.matrix[2][1] = -29. / 326.;
  expceted.matrix[2][2] = 243. / 2608.;
  expceted.matrix[2][3] = -83. / 2608.;
  expceted.matrix[3][0] = 37. / 326.;
  expceted.matrix[3][1] = -29. / 326.;
  expceted.matrix[3][2] = -83. / 2608.;
  expceted.matrix[3][3] = 243. / 2608.;

  ck_assert_int_eq(s21_eq_matrix(&result, &expceted), 1);

  s21_remove_matrix(&a);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expceted);
}
END_TEST

Suite *matrix_memory_suite(void) {
  Suite *s1 = suite_create("Matrix Memory");

  TCase *tc1_1 = tcase_create("Create");
  tcase_add_test(tc1_1, s21_matrix_create_correct);
  tcase_add_test(tc1_1, s21_matrix_create_incorrect_rows);
  tcase_add_test(tc1_1, s21_matrix_create_incorrect_columns);

  TCase *tc1_2 = tcase_create("Remove");
  tcase_add_test(tc1_2, s21_matrix_remove);

  suite_add_tcase(s1, tc1_1);
  suite_add_tcase(s1, tc1_2);

  return s1;
}

Suite *matrix_operations_suite(void) {
  Suite *s1 = suite_create("Matrix Operations");

  TCase *tc1_1 = tcase_create("Equals");
  tcase_add_test(tc1_1, s21_matrix_eq_correct_in_precision);
  tcase_add_test(tc1_1, s21_matrix_eq_incorrect_in_precision);
  tcase_add_test(tc1_1, s21_matrix_eq_incorrect_in_rows);
  tcase_add_test(tc1_1, s21_matrix_eq_incorrect_in_columns);

  TCase *tc1_2 = tcase_create("Sum");
  tcase_add_test(tc1_2, s21_matrix_sum_incorrect_nullptr);
  tcase_add_test(tc1_2, s21_matrix_sum_incorrect_result_matrix_size);
  tcase_add_test(tc1_2, s21_matrix_sum_incorrect_matrix_size);
  tcase_add_test(tc1_2, s21_matrix_sum_correct_equals);
  tcase_add_test(tc1_2, s21_matrix_sum_correct_not_equals);

  TCase *tc1_3 = tcase_create("Sub");
  tcase_add_test(tc1_3, s21_matrix_sub_incorrect_nullptr);
  tcase_add_test(tc1_3, s21_matrix_sub_incorrect_result_matrix_size);
  tcase_add_test(tc1_3, s21_matrix_sub_incorrect_matrix_size);
  tcase_add_test(tc1_3, s21_matrix_sub_correct_equals);
  tcase_add_test(tc1_3, s21_matrix_sub_correct_not_equals);

  TCase *tc1_4 = tcase_create("Mult Number");
  tcase_add_test(tc1_4, s21_matrix_mult_number_incorrect_nullptr);
  tcase_add_test(tc1_4, s21_matrix_mult_number_incorrect_matrix_size);
  tcase_add_test(tc1_4, s21_matrix_mult_number_correct);

  TCase *tc1_5 = tcase_create("Mult Matrix");
  tcase_add_test(tc1_5, s21_matrix_mult_nullptr);
  tcase_add_test(tc1_5, s21_matrix_mult_incorrect_size);
  tcase_add_test(tc1_5, s21_matrix_mult_correct);

  TCase *tc1_6 = tcase_create("Transpose");
  tcase_add_test(tc1_6, s21_matrix_transpose_nullptr);
  tcase_add_test(tc1_6, s21_matrix_transpose_incorrect_size);
  tcase_add_test(tc1_6, s21_matrix_transpose_correct);
  tcase_add_test(tc1_6, s21_matrix_transpose_correct_square);

  TCase *tc1_7 = tcase_create("Determinant");
  tcase_add_test(tc1_7, s21_matrix_determinant_incorrent_null);
  tcase_add_test(tc1_7, s21_matrix_determinant_incorrent_size);
  tcase_add_test(tc1_7, s21_matrix_determinant_correct_1x1);
  tcase_add_test(tc1_7, s21_matrix_determinant_correct_2x2);
  tcase_add_test(tc1_7, s21_matrix_determinant_correct_3x3);
  tcase_add_test(tc1_7, s21_matrix_determinant_correct_4x4);
  tcase_add_test(tc1_7, s21_matrix_determinant_correct_5x5);
  tcase_add_test(tc1_7, s21_matrix_determinant_correct_6x6);

  TCase *tc1_8 = tcase_create("Minor + Algebraic addition");
  tcase_add_test(tc1_8, s21_matrix_minor_incorrent_null);
  tcase_add_test(tc1_8, s21_matrix_minor_incorrent_size);
  tcase_add_test(tc1_8, s21_matrix_minor_corrent_3x3);

  TCase *tc1_9 = tcase_create("Inverse Matrix");
  tcase_add_test(tc1_9, s21_matrix_inverse_incorrent_null);
  tcase_add_test(tc1_9, s21_matrix_inverse_incorrent_size);
  tcase_add_test(tc1_9, s21_matrix_inverse_corrent_1x1);
  tcase_add_test(tc1_9, s21_matrix_inverse_corrent_2x2);
  tcase_add_test(tc1_9, s21_matrix_inverse_corrent_3x3);
  tcase_add_test(tc1_9, s21_matrix_inverse_corrent_4x4_det_0);
  tcase_add_test(tc1_9, s21_matrix_inverse_corrent_4x4);

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

int main(void) {
  int failed = 0;
  SRunner *sr;
  sr = srunner_create(NULL);

  srunner_set_fork_status(sr, CK_NOFORK);  // Valgrind

  srunner_add_suite(sr, matrix_memory_suite());
  srunner_add_suite(sr, matrix_operations_suite());
  failed = srunner_ntests_failed(sr);

  srunner_run_all(sr, CK_NORMAL);
  srunner_free(sr);
  return (failed == 0) ? 0 : 1;
}