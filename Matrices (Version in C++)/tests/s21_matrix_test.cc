#include <gtest/gtest.h>

#include <iostream>

#include "../s21_matrix_oop.h"

using namespace s21;

TEST(s21_matrix_suite, s21_matrix_create_correct) {
  S21Matrix a(3, 4);
  ASSERT_TRUE(a.IsValid());
  ASSERT_EQ(a.GetCols(), 4);
  ASSERT_TRUE(a.GetMatrix());

  S21Matrix b;
  ASSERT_TRUE(b.IsValid());
  ASSERT_TRUE(b.GetMatrix());

  S21Matrix c(a);
  ASSERT_TRUE(c.IsValid());
  ASSERT_EQ(c.GetCols(), 4);
  ASSERT_TRUE(c.GetMatrix());

  S21Matrix d = std::move(a);
  ASSERT_TRUE(d.IsValid());
  ASSERT_EQ(d.GetCols(), 4);
  ASSERT_TRUE(d.GetMatrix());
  ASSERT_EQ(a.GetCols(), 0);
}

TEST(s21_matrix_suite, s21_matrix_create_incorrect_rows_cols) {
  S21Matrix a(0, 0);
  ASSERT_EQ(a.GetRows(), 0);
  ASSERT_EQ(a.GetCols(), 0);
}

TEST(s21_matrix_suite, s21_matrix_eq_correct_in_precision) {
  int rows = 3;
  int cols = 3;

  S21Matrix a(rows, cols);

  S21Matrix b(rows, cols);

  double** amtx = a.GetMatrix();
  double** bmtx = b.GetMatrix();

  double avalue = 0.123456700;
  double bvalue = 0.123456710;
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++) amtx[i][j] = avalue, bmtx[i][j] = bvalue;

  ASSERT_TRUE(a.EqMatrix(b));
}

TEST(s21_matrix_suite, s21_matrix_eq_incorrect_in_precision) {
  int rows = 3;
  int cols = 3;

  S21Matrix a(rows, cols);

  S21Matrix b(rows, cols);

  double** amtx = a.GetMatrix();
  double** bmtx = b.GetMatrix();

  double avalue = 0.123456000;
  double bvalue = 0.123456100;
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++) amtx[i][j] = avalue, bmtx[i][j] = bvalue;

  ASSERT_FALSE(a.EqMatrix(b));
}

TEST(s21_matrix_suite, s21_matrix_eq_incorrect_in_rows) {
  int rows = 3;
  int cols = 3;

  S21Matrix a(rows, cols);

  S21Matrix b(rows, cols + 1);

  double** amtx = a.GetMatrix();
  double** bmtx = b.GetMatrix();

  double avalue = 0.123456000;
  double bvalue = 0.123456100;
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++) amtx[i][j] = avalue, bmtx[i][j] = bvalue;

  ASSERT_FALSE(a.EqMatrix(b));
}

TEST(s21_matrix_suite, s21_matrix_eq_incorrect_in_columns) {
  int rows = 3;
  int cols = 3;

  S21Matrix a(rows, cols);

  S21Matrix b(rows + 1, cols);

  double** amtx = a.GetMatrix();
  double** bmtx = b.GetMatrix();

  double avalue = 0.123456000;
  double bvalue = 0.123456100;
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++) amtx[i][j] = avalue, bmtx[i][j] = bvalue;

  ASSERT_FALSE(a.EqMatrix(b));
}

TEST(s21_matrix_suite, s21_matrix_sum_number_incorrect_matrix_size) {
  S21Matrix a(0, 0);
  ASSERT_NO_THROW(a.SumNumber(5.));
}

TEST(s21_matrix_suite, s21_matrix_sum_number_correct) {
  int rows = 4;
  int cols = 4;

  S21Matrix a(rows, cols);

  ASSERT_NO_THROW(a.SumNumber(3.));

  S21Matrix expected(rows, cols);
  double** matrix = expected.GetMatrix();

  for (int j = 0; j < cols; j++)
    for (int i = 0; i < rows; i++) matrix[i][j] = 3.;

  ASSERT_TRUE(a.EqMatrix(expected));
}

TEST(s21_matrix_suite, s21_matrix_sum_incorrect_null_size) {
  S21Matrix a(4, 4);
  S21Matrix b(0, 0);
  ASSERT_ANY_THROW(a.MulMatrix(b));
}

TEST(s21_matrix_suite, s21_matrix_sum_incorrect_matrix) {
  S21Matrix a(0, 0);
  S21Matrix b(0, 0);
  ASSERT_ANY_THROW(a.SumMatrix(b));
}

TEST(s21_matrix_suite, s21_matrix_sum_incorrect_matrix_size) {
  S21Matrix a(2, 2);
  S21Matrix b(1, 1);
  ASSERT_ANY_THROW(a.SumMatrix(b));
}

TEST(s21_matrix_suite, s21_matrix_sum_correct_equals) {
  S21Matrix a(4, 4);
  S21Matrix b(4, 4);
  S21Matrix expected(4, 4);

  a.SumNumber(1.);
  b.SumNumber(3.);

  ASSERT_NO_THROW(a.SumMatrix(b));

  expected.SumNumber(4.);

  ASSERT_TRUE(a.EqMatrix(expected));
}

TEST(s21_matrix_suite, s21_matrix_sum_correct_not_equals) {
  S21Matrix a(4, 4);
  S21Matrix b(4, 4);
  S21Matrix expected(4, 4);

  a.SumNumber(1.);
  b.SumNumber(3.);

  ASSERT_NO_THROW(a.SumMatrix(b));

  expected.SumNumber(5.);

  ASSERT_FALSE(a.EqMatrix(expected));
}

TEST(s21_matrix_suite, s21_matrix_sub_incorrect_matrix) {
  S21Matrix a(0, 0);
  S21Matrix b(0, 0);
  ASSERT_ANY_THROW(a.SubMatrix(b));
}

TEST(s21_matrix_suite, s21_matrix_sub_incorrect_matrix_size) {
  S21Matrix a(2, 2);
  S21Matrix b(1, 1);
  ASSERT_ANY_THROW(a.SubMatrix(b));
}

TEST(s21_matrix_suite, s21_matrix_sub_correct_equals) {
  S21Matrix a(4, 4);
  S21Matrix b(4, 4);
  S21Matrix expected(4, 4);

  a.SumNumber(1.);
  b.SumNumber(3.);

  ASSERT_NO_THROW(a.SubMatrix(b));

  expected.SumNumber(-2.);

  ASSERT_TRUE(a.EqMatrix(expected));
}

TEST(s21_matrix_suite, s21_matrix_sub_correct_not_equals) {
  S21Matrix a(4, 4);
  S21Matrix b(4, 4);
  S21Matrix expected(4, 4);

  a.SumNumber(1.);
  b.SumNumber(3.);

  ASSERT_NO_THROW(a.SubMatrix(b));

  expected.SumNumber(5.);

  ASSERT_FALSE(a.EqMatrix(expected));
}

TEST(s21_matrix_suite, s21_matrix_mult_number_incorrect_matrix_size) {
  S21Matrix a(0, 0);
  ASSERT_NO_THROW(a.MulNumber(5.));
}

TEST(s21_matrix_suite, s21_matrix_mult_number_correct) {
  S21Matrix a(4, 4);

  a.SumNumber(3.);

  ASSERT_NO_THROW(a.MulNumber(2.));

  S21Matrix expected(4, 4);
  expected.SumNumber(6.);

  ASSERT_TRUE(a.EqMatrix(expected));
}

TEST(s21_matrix_suite, s21_matrix_mult_incorrect_null_size) {
  S21Matrix a(4, 4);
  S21Matrix b(0, 0);
  ASSERT_ANY_THROW(a.MulMatrix(b));
}

TEST(s21_matrix_suite, s21_matrix_mult_incorrect_size) {
  S21Matrix a(2, 2);
  S21Matrix b(4, 4);
  ASSERT_ANY_THROW(a.MulMatrix(b));
}

TEST(s21_matrix_suite, s21_matrix_mult_correct) {
  S21Matrix a(2, 3);
  S21Matrix b(3, 2);
  S21Matrix expected(2, 2);

  double** matrixA = a.GetMatrix();
  double** matrixB = b.GetMatrix();
  double** matrixE = expected.GetMatrix();

  matrixA[0][0] = 1.;
  matrixA[0][1] = 2.;
  matrixA[0][2] = 3.;
  matrixA[1][0] = 4.;
  matrixA[1][1] = 5.;
  matrixA[1][2] = 6.;

  matrixB[0][0] = 10.;
  matrixB[0][1] = 11.;
  matrixB[1][0] = 20.;
  matrixB[1][1] = 21.;
  matrixB[2][0] = 30.;
  matrixB[2][1] = 31.;

  ASSERT_NO_THROW(a.MulMatrix(b));

  matrixE[0][0] = 140.;
  matrixE[0][1] = 146.;
  matrixE[1][0] = 320.;
  matrixE[1][1] = 335.;

  ASSERT_TRUE(a.EqMatrix(expected));
}

TEST(s21_matrix_suite, s21_matrix_transpose_nullptr) {
  S21Matrix a(0, 0);
  ASSERT_NO_THROW(a.Transpose());
}

TEST(s21_matrix_suite, s21_matrix_transpose_incorrect_size) {
  S21Matrix a(1, 0);
  ASSERT_NO_THROW(a.Transpose());
}

TEST(s21_matrix_suite, s21_matrix_transpose_correct) {
  int arows = 4;
  int acolumns = 2;

  S21Matrix a(arows, acolumns);
  double** amatrix = a.GetMatrix();

  for (int i = 0, counter = 1; i < arows; i++)
    for (int j = 0; j < acolumns; j++, counter++) amatrix[i][j] = counter;

  S21Matrix c(a.Transpose());

  S21Matrix expect(acolumns, arows);
  double** ematrix = expect.GetMatrix();

  for (int i = 0; i < acolumns; i++)
    for (int j = 0, counter = i + 1; j < arows; j++, counter += 2)
      ematrix[i][j] = counter;

  ASSERT_TRUE(c.EqMatrix(expect));
}

TEST(s21_matrix_suite, s21_matrix_transpose_correct_square) {
  int arows = 5;
  int acolumns = 5;

  S21Matrix a(arows, acolumns);
  double** amatrix = a.GetMatrix();

  for (int i = 0, counter = 1; i < arows; i++)
    for (int j = 0; j < acolumns; j++, counter++) amatrix[i][j] = counter;

  S21Matrix c(a.Transpose());

  S21Matrix expect(acolumns, arows);
  double** ematrix = expect.GetMatrix();

  for (int i = 0; i < acolumns; i++)
    for (int j = 0, counter = i + 1; j < arows; j++, counter += 5)
      ematrix[i][j] = counter;

  ASSERT_TRUE(c.EqMatrix(expect));
}

TEST(s21_matrix_suite, s21_matrix_determinant_incorrent_null) {
  S21Matrix A(0, 0);
  ASSERT_ANY_THROW(A.Determinant());
}

TEST(s21_matrix_suite, s21_matrix_determinant_incorrent_size) {
  S21Matrix A(1, 0);
  ASSERT_ANY_THROW(A.Determinant());
}

TEST(s21_matrix_suite, s21_matrix_determinant_correct_1x1) {
  int arows = 1;
  int acolumns = 1;

  S21Matrix a(arows, acolumns);

  a.SumNumber(2.);
  double** amatrix = a.GetMatrix();
  for (int i = 0; i < arows; i++) amatrix[i][i] = -5.0;

  double expected = -5.0;
  ASSERT_NEAR(a.Determinant(), expected, 1e-6);
}

TEST(s21_matrix_suite, s21_matrix_determinant_correct_2x2) {
  int arows = 2;
  int acolumns = 2;

  S21Matrix a(arows, acolumns);

  double** amatrix = a.GetMatrix();

  amatrix[0][0] = 0.;
  amatrix[0][1] = 2.;
  amatrix[1][0] = 5.;
  amatrix[1][1] = 1.;

  double expected = -10.0;
  ASSERT_NEAR(a.Determinant(), expected, 1e-6);
}

TEST(s21_matrix_suite, s21_matrix_determinant_correct_3x3) {
  int arows = 3;
  int acolumns = 3;

  S21Matrix a(arows, acolumns);
  double** amatrix = a.GetMatrix();

  a.SumNumber(2.);
  for (int i = 0; i < arows; i++) amatrix[i][i] = 5.0;

  double expected = 81.0;
  ASSERT_NEAR(a.Determinant(), expected, 1e-6);
}

TEST(s21_matrix_suite, s21_matrix_determinant_correct_4x4) {
  int arows = 4;
  int acolumns = 4;

  S21Matrix a(arows, acolumns);
  double** amatrix = a.GetMatrix();

  a.SumNumber(2.);
  for (int i = 0; i < arows; i++) amatrix[i][i] = 0.0;

  double expected = -48.0;
  ASSERT_NEAR(a.Determinant(), expected, 1e-6);
}

TEST(s21_matrix_suite, s21_matrix_determinant_correct_5x5) {
  int arows = 5;
  int acolumns = 5;

  S21Matrix a(arows, acolumns);
  double** amatrix = a.GetMatrix();

  a.SumNumber(0.);
  for (int i = 0; i < arows; i++) amatrix[i][i] = 0.0;

  double expected = 0.0;
  ASSERT_NEAR(a.Determinant(), expected, 1e-6);
}

TEST(s21_matrix_suite, s21_matrix_determinant_correct_6x6) {
  int arows = 6;
  int acolumns = 6;

  S21Matrix a(arows, acolumns);
  double** amatrix = a.GetMatrix();

  a.SumNumber(2.);
  for (int i = 0; i < arows; i++) amatrix[i][i] = -5.0;
  amatrix[4][4] = -23.0;
  amatrix[0][0] = 17.0;

  double expected = 80605.0;
  ASSERT_NEAR(a.Determinant(), expected, 1e-6);
}

TEST(s21_matrix_suite, s21_matrix_minor_incorrent_null) {
  S21Matrix a(0, 0);
  ASSERT_ANY_THROW(a.CalcComplements());
}

TEST(s21_matrix_suite, s21_matrix_minor_incorrent_size) {
  S21Matrix a(5, 4);
  ASSERT_ANY_THROW(a.CalcComplements());
}

TEST(s21_matrix_suite, s21_matrix_minor_corrent_3x3) {
  int arows = 3;
  int acolumns = 3;

  S21Matrix a(arows, acolumns);
  double** amatrix = a.GetMatrix();
  amatrix[0][0] = 1.;
  amatrix[0][1] = 2.;
  amatrix[0][2] = 3.;
  amatrix[1][0] = 0.;
  amatrix[1][1] = 4.;
  amatrix[1][2] = 2.;
  amatrix[2][0] = 5.;
  amatrix[2][1] = 2.;
  amatrix[2][2] = 1.;

  S21Matrix expceted(arows, acolumns);
  double** ematrix = expceted.GetMatrix();
  ematrix[0][0] = 0.;
  ematrix[0][1] = 10.;
  ematrix[0][2] = -20.;
  ematrix[1][0] = 4.;
  ematrix[1][1] = -14.;
  ematrix[1][2] = 8.;
  ematrix[2][0] = -8.;
  ematrix[2][1] = -2.;
  ematrix[2][2] = 4.;

  ASSERT_TRUE(a.CalcComplements().EqMatrix(expceted));
}

TEST(s21_matrix_suite, s21_matrix_inverse_incorrent_null) {
  S21Matrix result(0, 0);
  ASSERT_ANY_THROW(result.InverseMatrix());
}

TEST(s21_matrix_suite, s21_matrix_inverse_incorrent_size) {
  S21Matrix a(5, 4);
  ASSERT_ANY_THROW(a.InverseMatrix());
}

TEST(s21_matrix_suite, s21_matrix_inverse_corrent_1x1) {
  int arows = 1;
  int acolumns = 1;
  S21Matrix a(arows, acolumns);
  double** amatrix = a.GetMatrix();
  S21Matrix expected(arows, acolumns);
  double** expcetedmatrix = expected.GetMatrix();

  amatrix[0][0] = -62.;

  expcetedmatrix[0][0] = -1. / 62.;

  ASSERT_TRUE(a.InverseMatrix().EqMatrix(expected));
}

TEST(s21_matrix_suite, s21_matrix_inverse_corrent_2x2) {
  int arows = 2;
  int acolumns = 2;
  S21Matrix a(arows, acolumns);
  double** amatrix = a.GetMatrix();
  S21Matrix expected(arows, acolumns);
  double** expcetedmatrix = expected.GetMatrix();

  amatrix[0][0] = 2.;
  amatrix[0][1] = 5.;
  amatrix[1][0] = 7.;
  amatrix[1][1] = 3.;
  expcetedmatrix[0][0] = -3. / 29.;
  expcetedmatrix[0][1] = 5. / 29.;
  expcetedmatrix[1][0] = 7. / 29.;
  expcetedmatrix[1][1] = -2. / 29.;

  ASSERT_TRUE(a.InverseMatrix().EqMatrix(expected));
}

TEST(s21_matrix_suite, s21_matrix_inverse_corrent_3x3) {
  int arows = 3;
  int acolumns = 3;
  S21Matrix a(arows, acolumns);
  double** amatrix = a.GetMatrix();
  S21Matrix expected(arows, acolumns);
  double** expcetedmatrix = expected.GetMatrix();

  amatrix[0][0] = 2.;
  amatrix[0][1] = 5.;
  amatrix[0][2] = 7.;
  amatrix[1][0] = 6.;
  amatrix[1][1] = 3.;
  amatrix[1][2] = 4.;
  amatrix[2][0] = 5.;
  amatrix[2][1] = -2.;
  amatrix[2][2] = -3.;
  expcetedmatrix[0][0] = 1.;
  expcetedmatrix[0][1] = -1.;
  expcetedmatrix[0][2] = 1.;
  expcetedmatrix[1][0] = -38.;
  expcetedmatrix[1][1] = 41.;
  expcetedmatrix[1][2] = -34.;
  expcetedmatrix[2][0] = 27.;
  expcetedmatrix[2][1] = -29.;
  expcetedmatrix[2][2] = 24.;

  ASSERT_TRUE(a.InverseMatrix().EqMatrix(expected));
}

TEST(s21_matrix_suite, s21_matrix_inverse_incorrent_4x4_det_0) {
  int arows = 4;
  int acolumns = 4;
  S21Matrix a(arows, acolumns);
  double** amatrix = a.GetMatrix();

  amatrix[0][0] = 2.;
  amatrix[0][1] = 5.;
  amatrix[0][2] = 7.;
  amatrix[0][3] = 7.;
  amatrix[1][0] = 6.;
  amatrix[1][1] = 3.;
  amatrix[1][2] = 4.;
  amatrix[1][3] = 4.;
  amatrix[2][0] = 5.;
  amatrix[2][1] = -2.;
  amatrix[2][2] = -3.;
  amatrix[2][3] = -3.;
  amatrix[3][0] = 5.;
  amatrix[3][1] = -2.;
  amatrix[3][2] = -3.;
  amatrix[3][3] = -3.;

  ASSERT_ANY_THROW(a.InverseMatrix());
}

TEST(s21_matrix_suite, s21_matrix_inverse_corrent_4x4) {
  int arows = 4;
  int acolumns = 4;
  S21Matrix a(arows, acolumns);
  double** amatrix = a.GetMatrix();
  S21Matrix expected(arows, acolumns);
  double** expcetedmatrix = expected.GetMatrix();

  amatrix[0][0] = 2.;
  amatrix[0][1] = 5.;
  amatrix[0][2] = 7.;
  amatrix[0][3] = 7.;
  amatrix[1][0] = 6.;
  amatrix[1][1] = 5.;
  amatrix[1][2] = 4.;
  amatrix[1][3] = 4.;
  amatrix[2][0] = 5.;
  amatrix[2][1] = -2.;
  amatrix[2][2] = 5.;
  amatrix[2][3] = -3.;
  amatrix[3][0] = 5.;
  amatrix[3][1] = -2.;
  amatrix[3][2] = -3.;
  amatrix[3][3] = 5.;
  expcetedmatrix[0][0] = -13. / 163.;
  expcetedmatrix[0][1] = 19. / 163.;
  expcetedmatrix[0][2] = 15. / 326.;
  expcetedmatrix[0][3] = 15. / 326.;
  expcetedmatrix[1][0] = -14. / 163.;
  expcetedmatrix[1][1] = 33. / 163.;
  expcetedmatrix[1][2] = -17. / 163.;
  expcetedmatrix[1][3] = -17. / 163.;
  expcetedmatrix[2][0] = 37. / 326.;
  expcetedmatrix[2][1] = -29. / 326.;
  expcetedmatrix[2][2] = 243. / 2608.;
  expcetedmatrix[2][3] = -83. / 2608.;
  expcetedmatrix[3][0] = 37. / 326.;
  expcetedmatrix[3][1] = -29. / 326.;
  expcetedmatrix[3][2] = -83. / 2608.;
  expcetedmatrix[3][3] = 243. / 2608.;

  ASSERT_TRUE(a.InverseMatrix().EqMatrix(expected));
}

TEST(s21_matrix_suite, s21_matrix_operator_index_incorrect_1) {
  S21Matrix a(2, 2);
  ASSERT_ANY_THROW(a(2, 2));
}

TEST(s21_matrix_suite, s21_matrix_operator_index_incorrect_2) {
  S21Matrix a(2, 2);
  ASSERT_ANY_THROW(a(1, -1));
}

TEST(s21_matrix_suite, s21_matrix_operator_index) {
  S21Matrix a(2, 2);
  a.SumNumber(2.);
  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 2; j++) ASSERT_EQ(a(i, j), 2.);
}

TEST(s21_matrix_suite, s21_matrix_operator_sum_n) {
  S21Matrix a(2, 2);
  S21Matrix b(a + 2.);
  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 2; j++) ASSERT_EQ(b(i, j), 2.);
}

TEST(s21_matrix_suite, s21_matrix_operator_sum_m) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);

  a = a + 2.;
  b = b + 2.;
  S21Matrix c(2, 2);
  c = a + b;

  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 2; j++) ASSERT_EQ(c(i, j), 4.);
}

TEST(s21_matrix_suite, s21_matrix_operator_sub_n) {
  S21Matrix a(2, 2);
  S21Matrix b(a - 2.);
  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 2; j++) ASSERT_EQ(b(i, j), -2.);
}

TEST(s21_matrix_suite, s21_matrix_operator_sub_m) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);

  a = a - 2.;
  b = b - 2.;
  S21Matrix c(2, 2);
  c = a + b;

  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 2; j++) ASSERT_EQ(c(i, j), -4.);
}

TEST(s21_matrix_suite, s21_matrix_operator_mul_n) {
  S21Matrix a(2, 2);
  a = a + 2.;
  S21Matrix b(a * 2.);
  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 2; j++) ASSERT_EQ(b(i, j), 4.);
}

TEST(s21_matrix_suite, s21_matrix_operator_mul_m) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);

  a = a + 2.;
  b = b + 3.;
  S21Matrix c(2, 2);
  c = a * b;

  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 2; j++) ASSERT_EQ(c(i, j), 12.);
}

TEST(s21_matrix_suite, s21_matrix_operator_sumeq_n) {
  S21Matrix a(2, 2);
  a += 2.;
  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 2; j++) ASSERT_EQ(a(i, j), 2.);
}

TEST(s21_matrix_suite, s21_matrix_operator_sumeq_m) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);

  a += 2.;
  b += 3.;
  S21Matrix c(2, 2);
  c += a + b;

  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 2; j++) ASSERT_EQ(c(i, j), 5.);
}

TEST(s21_matrix_suite, s21_matrix_operator_subeq_n) {
  S21Matrix a(2, 2);
  a -= 2.;
  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 2; j++) ASSERT_EQ(a(i, j), -2.);
}

TEST(s21_matrix_suite, s21_matrix_operator_subeq_m) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);

  a -= 2.;
  b -= 3.;
  S21Matrix c(2, 2);
  c -= a + b;

  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 2; j++) ASSERT_EQ(c(i, j), 5.);
}

TEST(s21_matrix_suite, s21_matrix_operator_muleq_n) {
  S21Matrix a(2, 2);
  a = a + 2.;
  S21Matrix b(a *= 2);
  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 2; j++) ASSERT_EQ(b(i, j), 4.);
}

TEST(s21_matrix_suite, s21_matrix_operator_muleq_m) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);

  a += 2.;
  b += 3.;
  S21Matrix c(2, 2);
  c += 1.;
  c *= a * b;

  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 2; j++) ASSERT_EQ(c(i, j), 24.);
}

TEST(s21_matrix_suite, s21_matrix_operator_eq_m) {
  S21Matrix a(2, 2);
  a = a + 2.;
  S21Matrix b(a *= 2);
  ASSERT_TRUE(a == b);
}

TEST(s21_matrix_suite, s21_matrix_operator_neq_m) {
  S21Matrix a(2, 2);
  a = a + 2.;
  S21Matrix b(a *= 2);
  a += 1.;
  ASSERT_TRUE(a != b);
}

TEST(s21_matrix_suite, s21_matrix_set_rows) {
  S21Matrix a(1, 2);
  a.SetRows(2);
  a += 1.;
  S21Matrix b(2, 2);
  b += 1.;
  ASSERT_TRUE(a.EqMatrix(b));
}

TEST(s21_matrix_suite, s21_matrix_set_cols) {
  S21Matrix a(2, 1);
  a.SetCols(2);
  a += 1.;
  S21Matrix b(2, 2);
  b += 1.;
  ASSERT_TRUE(a.EqMatrix(b));
}

TEST(s21_matrix_suite, s21_matrix_set_matrix_value) {
  S21Matrix a(1, 1);
  a.SetMatrixValue(0, 0, 20.);
  ASSERT_EQ(a(0, 0), 20.);
}