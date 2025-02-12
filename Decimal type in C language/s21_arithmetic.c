#include "s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int sign_1 = s21_get_sign(value_1.bits[3]);
  int sign_2 = s21_get_sign(value_2.bits[3]);
  big_decimal big_value_1 = s21_to_big_decimal(value_1);
  big_decimal big_value_2 = s21_to_big_decimal(value_2);
  big_decimal big_result = {0};
  s21_normalize(&big_value_1, &big_value_2);
  if (sign_1 == sign_2) {
    big_result = s21_bitwise_add(big_value_1, big_value_2);
    s21_set_scale_and_sign(&big_result, s21_get_scale(big_value_1.bits[7]),
                           sign_1);
  } else {
    if (s21_WO_sign_is_greater_or_equal(big_value_1, big_value_2)) {
      big_result = s21_bitwise_sub(big_value_1, big_value_2);
      s21_set_scale_and_sign(&big_result, s21_get_scale(big_value_1.bits[7]),
                             sign_1);
    } else {
      big_result = s21_bitwise_sub(big_value_2, big_value_1);
      s21_set_scale_and_sign(&big_result, s21_get_scale(big_value_2.bits[7]),
                             sign_2);
    }
  }
  int flag = s21_to_decimal(big_result, result);
  return flag;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int sign_1 = s21_get_sign(value_1.bits[3]);
  int sign_2 = s21_get_sign(value_2.bits[3]);
  big_decimal big_value_1 = s21_to_big_decimal(value_1);
  big_decimal big_value_2 = s21_to_big_decimal(value_2);
  big_decimal big_result = {0};
  s21_normalize(&big_value_1, &big_value_2);
  if (sign_1 == sign_2) {
    if (s21_WO_sign_is_greater_or_equal(big_value_1, big_value_2)) {
      big_result = s21_bitwise_sub(big_value_1, big_value_2);
      s21_set_scale_and_sign(&big_result, s21_get_scale(big_value_1.bits[7]),
                             sign_1);
    } else {
      big_result = s21_bitwise_sub(big_value_2, big_value_1);
      s21_set_scale_and_sign(&big_result, s21_get_scale(big_value_2.bits[7]),
                             ~sign_2);
    }
  } else {
    big_result = s21_bitwise_add(big_value_1, big_value_2);
    s21_set_scale_and_sign(&big_result, s21_get_scale(big_value_1.bits[7]),
                           sign_1);
  }
  int flag = s21_to_decimal(big_result, result);
  return flag;
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  big_decimal big_value_1 = s21_to_big_decimal(value_1);
  big_decimal big_value_2 = s21_to_big_decimal(value_2);
  big_decimal big_result = {0};
  s21_bitwise_mul(big_value_1, big_value_2, &big_result);
  int scale = s21_get_scale(value_1.bits[3]) + s21_get_scale(value_2.bits[3]);
  int sign = 0;
  if (s21_get_sign(value_1.bits[3]) != s21_get_sign(value_2.bits[3])) {
    sign = 1;
  }
  s21_set_scale_and_sign(&big_result, scale, sign);
  int flag = s21_to_decimal(big_result, result);
  return flag;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  big_decimal big_value_1 = s21_to_big_decimal(value_1);
  big_decimal big_value_2 = s21_to_big_decimal(value_2);
  big_decimal big_result = {0};
  int flag = 3;
  if (!s21_is_null(big_value_2)) {
    s21_normalize(&big_value_1, &big_value_2);
    big_value_1.bits[7] = 0;
    big_value_2.bits[7] = 0;
    s21_bitwise_division(big_value_1, big_value_2, &big_result);
    int sign = 0;
    if (s21_get_sign(value_1.bits[3]) != s21_get_sign(value_2.bits[3])) {
      sign = 1;
    }
    s21_set_scale_and_sign(&big_result, s21_get_scale(big_result.bits[7]),
                           sign);
    flag = s21_to_decimal(big_result, result);
  }
  return flag;
}