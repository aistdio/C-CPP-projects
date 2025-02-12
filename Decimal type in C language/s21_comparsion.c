#include "s21_decimal.h"

int s21_is_null(big_decimal big_value_1) {
  int flag = 0;
  big_decimal it_is_null = {{0}};
  if (s21_WO_sign_is_greater_or_equal(big_value_1, it_is_null) == 2) {
    flag = 1;
  }
  return flag;
}

int s21_WO_sign_is_greater(big_decimal big_value_1, big_decimal big_value_2) {
  int ans = 0;
  if (s21_WO_sign_is_greater_or_equal(big_value_1, big_value_2) == 1) {
    ans = 1;
  }
  return ans;
}

int s21_WO_sign_is_greater_or_equal(big_decimal big_value_1,
                                    big_decimal big_value_2) {
  int ans = 2;
  s21_normalize(&big_value_1, &big_value_2);
  for (int i = 223; i >= 0 && ans == 2; i--) {
    int bit_1 = s21_get_bit(big_value_1, i);
    int bit_2 = s21_get_bit(big_value_2, i);
    if (bit_2 > bit_1) {
      ans = 0;
    } else if (bit_1 > bit_2) {
      ans = 1;
    }
  }
  return ans;
}

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  big_decimal big_value_1 = s21_to_big_decimal(value_1);
  big_decimal big_value_2 = s21_to_big_decimal(value_2);
  s21_normalize(&big_value_1, &big_value_2);
  int ans = 0;
  if (s21_get_sign(value_1.bits[3]) == s21_get_sign(value_2.bits[3])) {
    if (s21_WO_sign_is_greater_or_equal(big_value_1, big_value_2) == 2) {
      ans = 1;
    }
  }
  return ans;
}

int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
  int sign_1 = s21_get_sign(value_1.bits[3]);
  int sign_2 = s21_get_sign(value_2.bits[3]);
  int ans = 0;
  if (sign_1 == sign_2) {
    big_decimal big_value_1 = s21_to_big_decimal(value_1);
    big_decimal big_value_2 = s21_to_big_decimal(value_2);
    s21_normalize(&big_value_1, &big_value_2);
    if (sign_1 == 0) {
      if (s21_WO_sign_is_greater_or_equal(big_value_1, big_value_2) == 1) {
        ans = 1;
      }
    } else {
      if (s21_WO_sign_is_greater_or_equal(big_value_2, big_value_1) == 1) {
        ans = 1;
      }
    }
  } else {
    if (sign_2 > sign_1) {
      ans = 1;
    }
  }
  return ans;
}

int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
  int ans = 1;
  if (s21_is_greater(value_1, value_2) || s21_is_equal(value_1, value_2)) {
    ans = 0;
  }
  return ans;
}

int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2) {
  int ans = 0;
  if (s21_is_equal(value_1, value_2)) {
    ans = 1;
  } else if (s21_is_greater(value_1, value_2)) {
    ans = 1;
  }
  return ans;
}

int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2) {
  int ans = 0;
  if (s21_is_equal(value_1, value_2)) {
    ans = 1;
  } else if (s21_is_less(value_1, value_2)) {
    ans = 1;
  }
  return ans;
}

int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2) {
  int ans = 1;
  if (s21_is_equal(value_1, value_2)) {
    ans = 0;
  }
  return ans;
}