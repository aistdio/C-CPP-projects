#include "s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  int error = 1;
  if (result != NULL) {
    error = 0;
    big_decimal big_value = s21_to_big_decimal(value);
    int scale = s21_get_scale(value.bits[3]);
    int have_minus = s21_get_sign(value.bits[3]);

    big_decimal big_value_copy = big_value;
    s21_div_10_container(&big_value, scale);
    for (int i = 0; i < scale; i++) s21_mul_10(&big_value);
    big_decimal remainder = s21_bitwise_sub(big_value_copy, big_value);
    int is_zero = 1;
    for (int i = 0; i < 3 && is_zero == 1; i++) {
      if (remainder.bits[i]) is_zero = 0;
    }
    s21_div_10_container(&big_value, scale);
    big_decimal big_one = {{1}};
    if (!is_zero && have_minus) big_value = s21_bitwise_add(big_value, big_one);

    for (int i = 0; i < 3; i++) result->bits[i] = big_value.bits[i];
    result->bits[3] = have_minus << 31;
  }
  return error;
}

int s21_round(s21_decimal value, s21_decimal *result) {
  int error = 0;
  if (result != NULL) {
    big_decimal big_value = s21_to_big_decimal(value);
    s21_round_big(&big_value, s21_get_scale(value.bits[3]));
    s21_set_scale_and_sign(&big_value, 0, s21_get_sign(value.bits[3]));
    s21_to_decimal(big_value, result);
  } else {
    error = 1;
  }
  return error;
}

void s21_round_big(big_decimal *big_value, int size) {
  big_decimal result = *big_value;
  while (size > 0) {
    big_decimal temp = result;
    s21_div_10_container(&temp, 1);
    s21_mul_10(&temp);
    int remainder = s21_bitwise_sub(result, temp).bits[0];
    result = temp;
    s21_div_10_container(&result, 1);
    if (remainder >= 5) {
      big_decimal one = {{1}};
      result = s21_bitwise_add(result, one);
    }
    size--;
  }
  *big_value = result;
}

void s21_bank_rounding(big_decimal *big_value) {
  big_decimal temp = *big_value;
  big_decimal temp_2 = temp;
  s21_div_10_container(&temp, 1);
  s21_mul_10(&temp);
  big_decimal remainder_1 = s21_bitwise_sub(*big_value, temp);
  s21_div_10_container(&temp, 1);
  s21_div_10_container(&temp_2, 2);
  s21_mul_10(&temp_2);
  big_decimal remainder_2 = s21_bitwise_sub(temp, temp_2);
  if (s21_get_bit(remainder_2, 0) || remainder_1.bits[0] > 5) {
    s21_round_big(big_value, 1);
  } else {
    s21_div_10_container(big_value, 1);
  }
}