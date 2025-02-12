#include "s21_decimal.h"

big_decimal s21_bitwise_add(big_decimal big_value_1, big_decimal big_value_2) {
  big_decimal result = {0};
  int carry = 0;
  for (int i = 0; i < 224; i++) {
    int bit_1 = s21_get_bit(big_value_1, i);
    int bit_2 = s21_get_bit(big_value_2, i);
    int result_bit = bit_1 + bit_2 + carry;
    carry = result_bit / 2;
    result_bit %= 2;
    if (result_bit) {
      result.bits[i / 32] |= (1 << (i % 32));
    }
  }
  return result;
}

big_decimal s21_bitwise_sub(big_decimal big_value_1, big_decimal big_value_2) {
  s21_invert(&big_value_2);
  big_decimal one = {{1}};
  big_decimal big_result =
      s21_bitwise_add(big_value_1, s21_bitwise_add(big_value_2, one));
  return big_result;
}

void s21_bitwise_mul(big_decimal big_value_1, big_decimal big_value_2,
                     big_decimal *big_result) {
  big_decimal shift = big_value_1;
  for (int i = 0; i < 96; i++) {
    if (s21_get_bit(big_value_2, i)) {
      *big_result = s21_bitwise_add(*big_result, shift);
    }
    s21_shift_left(&shift);
  }
}

void s21_bitwise_division(big_decimal dec1, big_decimal dec2,
                          big_decimal *big_result) {
  big_decimal remainder = dec1;
  int scale = 0;
  while (!s21_is_null(remainder) && scale <= 28) {
    big_decimal divisor = dec2;
    while (!s21_WO_sign_is_greater_or_equal(remainder, divisor)) {
      s21_mul_10(&remainder);
      s21_mul_10(big_result);
      scale++;
    }
    big_decimal one = {{1}};
    int diff_scale =
        s21_get_oldest_bit(remainder) - s21_get_oldest_bit(divisor);
    for (int i = 0; i < diff_scale; i++) {
      big_decimal temp = divisor;
      s21_shift_left(&temp);
      if (s21_WO_sign_is_greater(temp, remainder)) {
        diff_scale--;
      } else {
        s21_shift_left(&divisor);
        s21_shift_left(&one);
      }
    }
    *big_result = s21_bitwise_add(*big_result, one);
    remainder = s21_bitwise_sub(remainder, divisor);
  }
  s21_set_scale_and_sign(big_result, scale, 0);
}

big_decimal s21_div_10(big_decimal dec1) {
  big_decimal result = {{0}};
  big_decimal to_compare = {{10}};
  while (s21_WO_sign_is_greater_or_equal(dec1, to_compare)) {
    big_decimal divisor = {{10}};
    int diff_scale = s21_get_oldest_bit(dec1) - s21_get_oldest_bit(divisor);
    for (int i = 0; i < diff_scale; i++) {
      big_decimal temp = divisor;
      s21_shift_left(&temp);
      if (s21_WO_sign_is_greater(temp, dec1)) {
        diff_scale--;
      } else {
        s21_shift_left(&divisor);
      }
    }
    dec1 = s21_bitwise_sub(dec1, divisor);
    big_decimal one = {{1}};
    for (int i = 0; i < diff_scale; i++) {
      s21_shift_left(&one);
    }
    result = s21_bitwise_add(result, one);
  }
  return result;
}

void s21_div_10_container(big_decimal *big_value, int times_to_round) {
  if (s21_get_scale(big_value->bits[7]) - times_to_round >= 0) {
    big_value->bits[7] -= times_to_round << 16;
  }
  unsigned int sign = big_value->bits[7] >> 31 << 31;
  big_value->bits[7] = 0;
  while (times_to_round) {
    *big_value = s21_div_10(*big_value);
    times_to_round--;
  }
  big_value->bits[7] = sign;
}