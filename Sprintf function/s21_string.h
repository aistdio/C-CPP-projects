#ifndef S21_STRING
#define S21_STRING

#include <math.h>
#include <stdarg.h>
#include <stdlib.h>

#define S21_NULL (void *)0
#define s21_size_t long int

#define S21_MAX_FLOAT 3.40282347e+38F

#define DEFAULT_PRECISION_F 6
#define DEFAULT_PRECISION_D 1
#define DEFAULT_PRECISION_S -1

typedef struct {
  int num;
} struct_width;

typedef struct {
  int flt;
  int dec;
  int str;
} struct_precision;

typedef struct {
  int h_short;
  int l_long;
  int L_double;
} struct_length;

typedef struct {
  int add_plus;
  int add_space;
  int minus_width;
  struct_width width;
  struct_precision precision;
  struct_length length;
} struct_settings;

int s21_sprintf(char *str, const char *format, ...);
struct_settings s21_sprintf_set_settings(const char **format, char **str,
                                         int *i, int *has_specifier);
void s21_sprintf_parse_flags(const char **format, int *i,
                             struct_settings *settings);
int s21_sprintf_is_flag(char c);
void s21_sprintf_setting_width(const char **format, int *i,
                               struct_settings *settings);
void s21_sprintf_setting_precision(const char **format, int *i,
                                   struct_settings *settings);
void s21_sprintf_parse_length(const char **format, char **str, int *i,
                              struct_settings *settings, int *has_specifier);
int s21_sprintf_parse_specifier(const char **format, int *i, int count);
char *s21_sprintf_get_numbers_from_string(const char **format, int *i,

                                          int *count);
struct_width s21_sprintf_str_to_int_width(char *buff, int count);
struct_precision s21_sprintf_str_to_int_precision(char *buff, int count);
void s21_sprintf_check_specifiers(char **str, const char **format, int *printed,
                                  int *i, struct_settings *settings,
                                  va_list *arg);
int s21_sprintf_is_valid_spec_or_length(char c);

int s21_is_number(char c);
int s21_is_letter(char c);
void s21_reverse_string(char **dst, int j, int i);
void s21_str_shift(char **dst, int dst_size, int steps);
void s21_sprintf_copy_str(char **src, char **dst, const char **format,
                          int *printed, int i);

void s21_sprintf_spec_s(char *tmp, char **str, const char **format,
                        int *printed, int i, struct_settings settings);
void s21_sprintf_spec_c(int arg, char **str, const char **format, int *printed,
                        int i, struct_settings settings);
void s21_sprintf_spec_d(int arg, char **str, const char **format, int *printed,
                        int i, struct_settings settings);
void s21_sprintf_spec_d_long(long int arg, char **str, const char **format,
                             int *printed, int i, struct_settings settings);
void s21_sprintf_spec_u(long unsigned int arg, char **str, const char **format,
                        int *printed, int i, struct_settings settings);
void s21_sprintf_spec_f(double arg, char **str, const char **format,
                        int *printed, int i, struct_settings settings);
void s21_sprintf_invalid_spec(char **str, const char **format, int *i);

void s21_sprintf_add_minus(char **tmp);
void s21_sprintf_add_plus(char **tmp);
void s21_sprintf_add_space(char **tmp);
void s21_sprintf_add_symbol(char **tmp, char c);
void s21_sprintf_fill_width(char **dst, struct_settings settings);

char *s21_sprintf_int_to_str(int arg, struct_settings settings);
char *s21_sprintf_long_int_to_str(long int arg, struct_settings settings);
void s21_sprintf_int_to_str_end(int have_minus, struct_settings settings, int i,
                                int dst_size, char **dst);
char *s21_sprintf_uint_to_str(long unsigned int arg);
void s21_sprintf_fill_precision(char **dst, int precision_decimal);

char *s21_sprintf_flt_to_str(double arg, struct_settings settings);
void s21_flt_to_str_entry(double *arg, char **dst, int *i);
void s21_flt_to_str_write_floats(double float_values, int *floatingsC, int *i,
                                 char **dst, int *dst_size,
                                 struct_settings settings);
void s21_flt_to_str_write_integers(double rounded_values, int *integersC,
                                   int *i, char **dst, int *dst_size);
void s21_flt_to_str_set_precision(char **dst, int dst_size,
                                  struct_settings settings, int floatingsC);

#endif