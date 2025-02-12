#include "s21_decimal.h"

int s21_get_scale(unsigned int bits) {
  int scale = (bits << 1 >> 17);
  return scale;
}

int s21_get_sign(unsigned int bits) {
  int sign = (bits >> 31);
  return sign;
}

int s21_get_bit(big_decimal big_value, int pos) {
  int bit = big_value.bits[pos / 32] >> (pos % 32) & 1;
  return bit;
}

void s21_shift_left(big_decimal *big_value) {
  unsigned int carry = 0;
  for (int i = 0; i < 7; i++) {
    unsigned int temp = big_value->bits[i];
    big_value->bits[i] <<= 1;
    big_value->bits[i] |= carry;
    carry = temp >> (32 - 1);
  }
}

big_decimal s21_to_big_decimal(s21_decimal value) {
  big_decimal big_value = {0};
  for (int i = 0; i <= 2; i++) {
    big_value.bits[i] = value.bits[i];
  }
  big_value.bits[7] = value.bits[3];
  return big_value;
}

void s21_mul_10(big_decimal *big_value) {
  big_decimal big_res_1 = *big_value;
  big_decimal big_res_2 = *big_value;
  s21_shift_left(&big_res_1);
  for (int j = 0; j < 3; j++) {
    s21_shift_left(&big_res_2);
  }
  *big_value = s21_bitwise_add(big_res_1, big_res_2);
}

void s21_normalize(big_decimal *big_value_1, big_decimal *big_value_2) {
  int scale_1 = s21_get_scale(big_value_1->bits[7]);
  int scale_2 = s21_get_scale(big_value_2->bits[7]);
  if (scale_1 > scale_2) {
    for (int i = 0; i < scale_1 - scale_2; i++) {
      s21_mul_10(big_value_2);
    }
    big_value_2->bits[7] = scale_1 << 16;
  } else if (scale_1 < scale_2) {
    for (int i = 0; i < scale_2 - scale_1; i++) {
      s21_mul_10(big_value_1);
    }
    big_value_1->bits[7] = scale_2 << 16;
  }
}

int s21_get_oldest_bit(big_decimal big_value) {
  int oldest_bit = 0;
  int flag = 1;
  for (int i = 223; i >= 0 && flag; i--) {
    if (big_value.bits[i / 32] >> i % 32) {
      oldest_bit = i;
      flag = 0;
    }
  }
  return oldest_bit;
}

void s21_invert(big_decimal *big_value) {
  big_decimal temp = *big_value;
  for (int i = 0; i < 7; i++) {
    big_value->bits[i] = ~temp.bits[i];
  }
}

int s21_to_decimal(big_decimal big_result, s21_decimal *result) {
  int error = 0;
  int flag = 0;
  int scale = s21_get_scale(big_result.bits[7]);
  int sign = s21_get_sign(big_result.bits[7]);
  for (int i = 96; i < 224 && !flag; i++) {
    flag = s21_get_bit(big_result, i);
  }
  while ((scale > 0 && flag) || scale > 28) {
    flag = 0;
    scale -= 1;
    s21_bank_rounding(&big_result);
    for (int i = 96; i < 224 && !flag; i++) {
      flag = s21_get_bit(big_result, i);
    }
  }
  if (flag || error) {
    if (sign) {
      error = 2;
    } else {
      error = 1;
    }
  } else {
    for (int i = 0; i <= 2; i++) {
      result->bits[i] = big_result.bits[i];
    }
    result->bits[3] = (sign << 31) + (scale << 16);
  }
  return error;
}

void s21_set_scale_and_sign(big_decimal *big_result, int scale, int sign) {
  big_result->bits[7] |= scale << 16;
  big_result->bits[7] |= sign << 31;
}
