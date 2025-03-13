#include "s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int error = 1;
  if (dst != NULL) {
    error = 0;
    for (int i = 0; i < 4; i++) {
      (*dst).bits[i] = 0;
    }
    if (src < 0) {
      src = -src;
      (*dst).bits[3] = (unsigned int)1 << 31;
    }
    (*dst).bits[0] += src;
  }
  return error;
}

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int error = 0;
  if (result != NULL) {
    big_decimal big_value = s21_to_big_decimal(value);
    big_value.bits[7] = value.bits[3];
    s21_div_10_container(&big_value, s21_get_scale(value.bits[3]));
    s21_to_decimal(big_value, result);
  } else {
    error = 1;
  }
  return error;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int error = 0;
  if (dst == NULL)
    error = 0;
  else {
    int have_minus = (src.bits[3] >= (unsigned int)MINUS) ? 1 : 0;
    s21_truncate(src, &src);
    if (src.bits[0] >= (unsigned int)INT_MAX + 1 || src.bits[1] || src.bits[2])
      *dst = (have_minus) ? INT_MIN : INT_MAX;
    else
      *dst = (have_minus) ? -src.bits[0] : src.bits[0];
  }
  return error;
}

int s21_negate(s21_decimal value, s21_decimal *result) {
  int error = 0;
  if (result == NULL)
    error = 1;
  else
    *result = value, result->bits[3] ^= 1 << 31;
  return error;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int error = 1;
  if (fabsf(src) < 1e-28 && dst != NULL) {
    for (int i = 0; i < 4; i++) dst->bits[i] = 0;
  } else if (dst != NULL && isnan(src) == 0 && isinf(src) == 0 &&
             fabsf(src) <= 7.922816e+28f) {
    error = 0;
    int have_minus = 0;
    if (src < 0) {
      have_minus = 1;
      src = -src;
    }

    int string_size = 15;
    char holder[15];
    snprintf(holder, string_size, "%.6e", (double)src);
    for (int i = 1; i < 12; i++) holder[i] = holder[i + 1];

    holder[7] = '\0';
    unsigned int integers = (unsigned int)strtoul(holder, NULL, 10);
    holder[7] = 'e';

    int scale = 0;
    char *str_exponent = strchr(holder, 'e');
    if (str_exponent != NULL) {
      scale = 6;
      str_exponent++;
      int exponent = atoi(str_exponent + 1);
      if (*str_exponent == '-')
        scale += exponent;
      else if (*str_exponent == '+')
        scale -= exponent;
    }

    s21_decimal result = {{integers, 0, 0, ((have_minus) ? 1u << 31 : 0)}};
    if (scale >= 0)
      result.bits[3] += (unsigned int)scale << 16;
    else {
      scale = -scale;
      s21_decimal ten = {{10}};
      for (int i = 0; i < scale; i++) {
        s21_mul(result, ten, &result);
      }
    }
    if (scale > 28)
      result.bits[3] -= (scale - 28) << 16,
          result.bits[0] /= pow(10, (scale - 28));

    for (int i = 0; i < 4; i++) dst->bits[i] = result.bits[i];
  }
  return error;
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int error = 1;
  int scale = s21_get_scale(src.bits[3]);
  int have_minus = s21_get_sign(src.bits[3]);

  if (dst != NULL && scale <= 28) {
    error = 0;
    big_decimal big_value = s21_to_big_decimal(src);

    unsigned int eight_digits = 10000000u;
    while (big_value.bits[0] >= eight_digits || big_value.bits[1] ||
           big_value.bits[2])
      s21_bank_rounding(&big_value), scale--;
    s21_from_decimal_to_float_division(&big_value, dst, scale);

    if (have_minus) *dst = -(*dst);
  }
  return error;
}

void s21_from_decimal_to_float_division(big_decimal *src, float *dst,
                                        int scale) {
  *dst = src->bits[0];
  if (scale) {
    *dst /= powf(10.0f, scale);
  } else {
    scale = -scale;
    *dst *= powf(10.0f, scale);
  }
}