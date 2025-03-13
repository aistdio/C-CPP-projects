#ifndef SRC_S21_DECIMAL_H_
#define SRC_S21_DECIMAL_H_

#define BIT32 0xFFFFFFFF
#define MINUS 1 << 31

#ifndef INT_MAX
#define INT_MAX 2147483647
#endif
#ifndef INT_MIN
#define INT_MIN -2147483647 - 1
#endif

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  unsigned int bits[4];
} s21_decimal;

typedef struct {
  unsigned int bits[8];
} big_decimal;

// s21_conversion.c
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);
void s21_from_decimal_to_float_division(big_decimal *src, float *dst,
                                        int scale);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

// s21_helper
int s21_get_scale(unsigned int bits);
int s21_get_sign(unsigned int bits);
int s21_get_bit(big_decimal big_value, int pos);
void s21_shift_left(big_decimal *big_value);
big_decimal s21_to_big_decimal(s21_decimal value);
void s21_mul_10(big_decimal *big_value);
void s21_normalize(big_decimal *big_value_1, big_decimal *big_value_2);
big_decimal s21_bitwise_add(big_decimal big_value_1, big_decimal big_value_2);
int s21_get_oldest_bit(big_decimal big_value);
void s21_invert(big_decimal *big_value);
int s21_to_decimal(big_decimal big_result, s21_decimal *result);
void s21_set_scale_and_sign(big_decimal *big_result, int scale, int sign);

// s21_comparsion
int s21_WO_sign_is_greater_or_equal(big_decimal big_value_1,
                                    big_decimal big_value_2);
int s21_WO_sign_is_greater(big_decimal big_value_1, big_decimal big_value_2);
int s21_is_less(s21_decimal, s21_decimal);
int s21_is_less_or_equal(s21_decimal, s21_decimal);
int s21_is_greater(s21_decimal, s21_decimal);
int s21_is_greater_or_equal(s21_decimal, s21_decimal);
int s21_is_equal(s21_decimal, s21_decimal);
int s21_is_not_equal(s21_decimal, s21_decimal);
int s21_is_null(big_decimal big_value_1);

// s21_bitwise_aritmetic
big_decimal s21_bitwise_add(big_decimal big_value_1, big_decimal big_value_2);
big_decimal s21_bitwise_sub(big_decimal big_value_1, big_decimal big_value_2);
void s21_bitwise_mul(big_decimal big_value_1, big_decimal big_value_2,
                     big_decimal *big_result);
void s21_bitwise_division(big_decimal dec1, big_decimal dec2,
                          big_decimal *result);
big_decimal s21_div_10(big_decimal dec1);
void s21_div_10_container(big_decimal *big_value, int times_to_round);

// s21_aritmetic
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

// s21_round
int s21_floor(s21_decimal value, s21_decimal *result);
void s21_floor_big(big_decimal *big_value, int step);
int s21_round(s21_decimal value, s21_decimal *result);
void s21_round_big(big_decimal *big_value, int step);
void s21_bank_rounding(big_decimal *big_value);
#endif
