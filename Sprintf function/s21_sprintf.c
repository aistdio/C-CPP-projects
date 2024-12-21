#include "s21_string.h"

int s21_sprintf(char *str, const char *format, ...) {
  va_list arg;
  va_start(arg, format);
  int printed = 0;

  int i = printed, has_specifier = 0;
  for (; format[i] != '\0'; i++) {
    struct_settings settings =
        s21_sprintf_set_settings(&format, &str, &i, &has_specifier);

    if (has_specifier) {
      s21_sprintf_check_specifiers(&str, &format, &printed, &i, &settings,
                                   &arg);
    }

    else
      str[i] = format[i];
  }
  str[i] = '\0';
  printed += i;

  va_end(arg);

  return printed;
}

/*
  Проверяем каждый символ на '%'. Если находим, то парсим на точность
  и ширину (По типу %2 / %.2 / %2.2).
*/
struct_settings s21_sprintf_set_settings(const char **format, char **str,
                                         int *i, int *has_specifier) {
  struct_settings settings = {.precision.flt = DEFAULT_PRECISION_F,
                              .precision.dec = DEFAULT_PRECISION_D,
                              .precision.str = DEFAULT_PRECISION_S,
                              .width.num = 0,
                              .add_plus = 0,
                              .add_space = 0,
                              .minus_width = 0,
                              .length.h_short = 0,
                              .length.l_long = 0,
                              .length.L_double = 0};

  if ((*format)[*i] == '%')
    *has_specifier = 1;
  else
    *has_specifier = 0;

  if (*has_specifier) {
    s21_sprintf_parse_flags(format, i, &settings);

    if (s21_is_number((*format)[*i + 1]))
      s21_sprintf_setting_width(format, i, &settings);

    if ((*format)[*i + 1] == '.')
      s21_sprintf_setting_precision(format, i, &settings);

    s21_sprintf_parse_length(format, str, i, &settings, has_specifier);
  }

  return settings;
}

void s21_sprintf_parse_flags(const char **format, int *i,
                             struct_settings *settings) {
  int count = 1;

  while (s21_sprintf_is_flag((*format)[*i + count])) {
    if ((*format)[*i + count] == '+')
      (*settings).add_plus = 1;

    else if ((*format)[*i + count] == ' ')
      (*settings).add_space = 1;

    else if ((*format)[*i + count] == '-')
      (*settings).minus_width = 1;

    count++;
  }

  (*format) += count - 1;
}

int s21_sprintf_is_flag(char c) {
  const char *flags = "+ -";

  return s21_strchr(flags, c) != NULL;
}

/*
  Тут парсится ширина (%2), после она сразу переводится в int.
  Записываем её в структуру настроек settings.precision
*/
void s21_sprintf_setting_width(const char **format, int *i,
                               struct_settings *settings) {
  int count = 0;
  char *buff = s21_sprintf_get_numbers_from_string(format, i, &count);

  (*settings).width = s21_sprintf_str_to_int_width(buff, count);

  // Сдвинули на след. символ после цифр
  if (s21_sprintf_parse_specifier(format, i, count)) *format += count;

  if (buff != S21_NULL) free(buff);
}

/*
  Парсит 'l' и 'h' в %ld / %lc / %ls / %hd / %lu / %hu
  h - только int
  l - int, char и строки
  L - float

  found != 2 нужно для отработки %ll / %hh
*/
void s21_sprintf_parse_length(const char **format, char **str, int *i,
                              struct_settings *settings, int *has_specifier) {
  int found = 0;

  while (found != 2 && (*format)[*i + 1] == 'h') {
    (*settings).length.h_short = 1;
    (*format)++;
    found++;
  }

  if ((*settings).length.h_short == 0) {
    while (found != 2 && (*format)[*i + 1] == 'l') {
      (*settings).length.l_long = 1;
      (*format)++;
      found++;
    }
  }

  if ((*settings).length.h_short == 0 && (*settings).length.l_long == 0) {
    while (found != 2 && (*format)[*i + 1] == 'L') {
      (*settings).length.L_double = 1;
      (*format)++;
      found++;
    }
  }

  if (found && !s21_sprintf_is_valid_spec_or_length((*format)[*i + 1])) {
    (*str)[*i] = (*format)[*i - found];
    (*i)++;

    *has_specifier = 0;
  }
}

/*
  Проверяем на наличие валидного символа спецификатора
*/
int s21_sprintf_parse_specifier(const char **format, int *i, int count) {
  int result = 0;
  int have_dot = 0;

  while (s21_is_number((*format)[*i + count]) ||
         ((*format)[*i + count] == '.' && !have_dot)) {
    if ((*format)[*i + count] == '.') have_dot = 1;
    count++;
  }
  if (s21_sprintf_is_valid_spec_or_length((*format)[*i + count])) result = 1;

  return result;
}

/*
  Тут парсится точность (%.2), после она сразу переводится в int.
  Записываем её в структуру настроек settings.precision
*/
void s21_sprintf_setting_precision(const char **format, int *i,
                                   struct_settings *settings) {
  int count = 1;  // нужно для сдвига индекса в функции ниже (из-за точки)
  char *buff = s21_sprintf_get_numbers_from_string(format, i, &count);

  if (count)
    (*settings).precision = s21_sprintf_str_to_int_precision(buff, count);
  else
    s21_memset(&((*settings).precision), 0, sizeof(struct_precision));

  // Сдвинули на след. символ после '.' и цифр за ней
  if (s21_sprintf_is_valid_spec_or_length((*format)[*i + 2 + count]))
    *format += count + 1;

  if (buff != S21_NULL) free(buff);
}

/*
  Получаем цифры ширины/точности из строки format и записываем в строку buff
*/
char *s21_sprintf_get_numbers_from_string(const char **format, int *i,
                                          int *count) {
  int bsize = 12;
  char *buff = calloc(bsize, sizeof(char));
  int shift = 1;
  if (*count) shift = 2, (*count)--;

  while (s21_is_number((*format)[*i + shift + *count])) {
    if (*count % 10 == 0) {
      buff = realloc(buff, (bsize + *count) * sizeof(char));
      s21_memset(buff + *count, '\0', bsize * sizeof(char));
    }
    buff[*count] = (*format)[*i + shift + *count];

    (*count)++;
  }

  return buff;
}

int s21_sprintf_is_valid_spec_or_length(char c) {
  return c == 'd' || c == 'i' || c == 'o' || c == 'u' || c == 'x' || c == 'X' ||
         c == 'g' || c == 'G' || c == 'e' || c == 'E' || c == 'f' || c == 's' ||
         c == 'c' || c == 'l' || c == 'h' || c == 'L';
}

int s21_is_number(char c) { return (c >= '0' && c <= '9'); }

int s21_is_letter(char c) {
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

/*
  Переводим строку в int. Используется для настройки width / precision
*/
struct_width s21_sprintf_str_to_int_width(char *buff, int count) {
  int result = 0;

  int multiplier = 1;
  int i = 0;
  s21_reverse_string(&buff, 0, count);
  while (buff[i]) {
    result += (buff[i] - '0') * multiplier;

    multiplier *= 10;
    i++;
  }

  struct_width width = {.num = result};

  return width;
}

struct_precision s21_sprintf_str_to_int_precision(char *buff, int count) {
  int result = 0;

  int multiplier = 1;
  int i = 0;
  s21_reverse_string(&buff, 0, count);
  while (buff[i]) {
    result += (buff[i] - '0') * multiplier;

    multiplier *= 10;
    i++;
  }

  struct_precision precision = {.flt = result, .dec = result, .str = result};

  return precision;
}

/*
  Если символ был '%', значит след. символ должен определять тип аргумента,
  который нам передан. Вызываемые здесь функции конвертируют
  аргумент в строку, форматируют его и записывают в строку str.

  Переменная 'i' (из главного цикла в main'е) в функциях всегда держится на
  последнем записанном символе в str и последнем записываемом символе из format.
  Указатели на str и format двигаются при необходимости, чтобы поддерживать
  'i' (индекс массивов str и format) на последнем записанном и записываемом
  символе.
*/
void s21_sprintf_check_specifiers(char **str, const char **format, int *printed,
                                  int *i, struct_settings *settings,
                                  va_list *arg) {
  if ((*format)[*i + 1] == '%')
    (*str)[*i] = (*format)[*i], (*format)++;

  else if ((*format)[*i + 1] == 'c')
    s21_sprintf_spec_c((char)va_arg(*arg, int), str, format, printed, *i,
                       *settings);

  else if ((*format)[*i + 1] == 's')
    s21_sprintf_spec_s(va_arg(*arg, char *), str, format, printed, *i,
                       *settings);

  else if ((*format)[*i + 1] == 'd' || (*format)[*i + 1] == 'i')
    if ((*settings).length.l_long)
      s21_sprintf_spec_d_long(va_arg(*arg, long int), str, format, printed, *i,
                              *settings);
    else
      s21_sprintf_spec_d(va_arg(*arg, int), str, format, printed, *i,
                         *settings);

  else if ((*format)[*i + 1] == 'u')
    s21_sprintf_spec_u(va_arg(*arg, long unsigned int), str, format, printed,
                       *i, *settings);

  else if ((*format)[*i + 1] == 'f')
    s21_sprintf_spec_f(va_arg(*arg, double), str, format, printed, *i,
                       *settings);

  else
    s21_sprintf_invalid_spec(str, format, i);
}

/*
  Дальше идёт отработка спецификаторов по типу
  "%c". Точность и прочее передаются через структуру struct_settings.
  Почти все функции отработки создают временную строку, в которую форматируется
  полученный аргумент. После эта строка записывается в str.
*/
void s21_sprintf_spec_c(int arg, char **str, const char **format, int *printed,
                        int i, struct_settings settings) {
  if (!settings.width.num) {
    (*str)[i] = arg;
    (*format)++;
  }

  else {
    char *tmp = calloc(2, sizeof(int));
    tmp[0] = arg;
    tmp[1] = '\0';

    s21_sprintf_fill_width(&tmp, settings);

    s21_sprintf_copy_str(&tmp, str, format, printed, i);

    if (tmp != S21_NULL) free(tmp);
  }
}

void s21_sprintf_spec_s(char *tmp, char **str, const char **format,
                        int *printed, int i, struct_settings settings) {
  if (tmp != S21_NULL) {
    int len = s21_strlen(tmp);

    if (settings.precision.str != -1 && settings.precision.str < len)
      tmp[settings.precision.str] = '\0';

    char *tmpCopy = calloc(len + 1 + settings.width.num, sizeof(char));
    s21_strncpy(tmpCopy, tmp, s21_strlen(tmp) + 1);
    s21_sprintf_fill_width(&tmpCopy, settings);

    s21_sprintf_copy_str(&tmpCopy, str, format, printed, i);

    if (tmpCopy != S21_NULL) free(tmpCopy);
  }
}

/*
  Выгодно взять как основу для спецификаторов ("%x, %X, %o, %p)
  int arg - полученный аргумент. Эта функция вызывается (и получает аргумент)
  из s21_sprintf_check_specifiers()

  Этапы:
  s21_sprintf_int_to_str() - конвертируем int arg в строку tmp
  s21_sprintf_fill_precision() - форматируем, заполняем нулями спереди в
  зависимости от полученной настройки точности
  s21_sprintf_fill_width() - форматируем, заполняем пробелами спереди в
  зависимости от полученной настройки ширины
  s21_sprintf_add_minus() - делается в особом случае, пока не работает но
  отсутствие этой функции не помешает s21_sprintf_copy_str() - копируем
  отформатированную строку tmp в str
*/
void s21_sprintf_spec_d(int arg, char **str, const char **format, int *printed,
                        int i, struct_settings settings) {
  char *tmp = s21_sprintf_int_to_str(arg, settings);

  s21_sprintf_fill_precision(&tmp, settings.precision.dec);
  s21_sprintf_fill_width(&tmp, settings);

  if (arg < 0 && (s21_size_t)settings.precision.dec + 1 > s21_strlen(tmp))
    s21_sprintf_add_minus(&tmp);

  if (settings.add_plus == 1 && arg >= 0)
    s21_sprintf_add_plus(&tmp);
  else if (settings.add_space == 1 && arg >= 0)
    s21_sprintf_add_space(&tmp);

  s21_sprintf_copy_str(&tmp, str, format, printed, i);

  if (tmp != S21_NULL) free(tmp);
}

/*
  Описание то же, что и у s21_sprintf_spec_d
*/
void s21_sprintf_spec_d_long(long int arg, char **str, const char **format,
                             int *printed, int i, struct_settings settings) {
  char *tmp = s21_sprintf_long_int_to_str(arg, settings);

  s21_sprintf_fill_precision(&tmp, settings.precision.dec);
  s21_sprintf_fill_width(&tmp, settings);

  if (arg < 0 && (s21_size_t)settings.precision.dec + 1 > s21_strlen(tmp))
    s21_sprintf_add_minus(&tmp);

  if (settings.add_plus == 1 && arg >= 0)
    s21_sprintf_add_plus(&tmp);
  else if (settings.add_space == 1 && arg >= 0)
    s21_sprintf_add_space(&tmp);

  s21_sprintf_copy_str(&tmp, str, format, printed, i);

  if (tmp != S21_NULL) free(tmp);
}

/*
  Выгодно взять как основу для спецификаторов ("%e, %E, %g, %G")
  Описание то же самое, что и у s21_sprintf_spec_d().

  Основная разница в конвертации float в string. Тут гораздо более
  сложная конвертация

  fill_precision() тут не используется, так как
  внутри функции s21_sprintf_flt_to_str() есть своя функиця
  обработки точности
*/
void s21_sprintf_spec_f(double arg, char **str, const char **format,
                        int *printed, int i, struct_settings settings) {
  char *tmp = s21_sprintf_flt_to_str(arg, settings);
  s21_sprintf_fill_width(&tmp, settings);

  if (settings.add_plus == 1 && arg >= 0)
    s21_sprintf_add_plus(&tmp);
  else if (settings.add_space == 1 && arg >= 0)
    s21_sprintf_add_space(&tmp);

  s21_sprintf_copy_str(&tmp, str, format, printed, i);

  if (tmp != S21_NULL) free(tmp);
}

void s21_sprintf_spec_u(long unsigned int arg, char **str, const char **format,
                        int *printed, int i, struct_settings settings) {
  char *tmp = s21_sprintf_uint_to_str(arg);
  s21_sprintf_fill_precision(&tmp, settings.precision.dec);
  s21_sprintf_fill_width(&tmp, settings);
  s21_sprintf_copy_str(&tmp, str, format, printed, i);
  if (tmp != S21_NULL) free(tmp);
}

/*
  Копируем строку из format в src.
*/
void s21_sprintf_copy_str(char **src, char **dst, const char **format,
                          int *printed, int i) {
  s21_strncpy(*dst + i, *src, s21_strlen(*src) + 1);
  int len = s21_strlen(*src) - 1;
  *printed += len;
  *dst += len, (*format)++;
}

/*
  Нужно если строка была отформатирована по точности
*/
void s21_sprintf_add_minus(char **tmp) { s21_sprintf_add_symbol(tmp, '-'); }

/*
  Нужно если было "%+"
*/
void s21_sprintf_add_plus(char **tmp) { s21_sprintf_add_symbol(tmp, '+'); }

/*
  Нужно если было "% "
*/
void s21_sprintf_add_space(char **tmp) { s21_sprintf_add_symbol(tmp, ' '); }

/*
  Добавляет символ в начале строки
*/
void s21_sprintf_add_symbol(char **tmp, char c) {
  s21_size_t len = s21_strlen(*tmp);
  *tmp = realloc(*tmp, len + 2);

  (*tmp)[len] = c;
  s21_str_shift(tmp, len + 1, 1);
  (*tmp)[len + 1] = '\0';
}

/*
  Переводим uint в строку (с помощью модуля)
  Потом переворачиваем строку, так как строка записывалась наоборот
*/
char *s21_sprintf_uint_to_str(long unsigned int arg) {
  int dst_size = 11;
  char *dst = calloc(dst_size, sizeof(char));
  int i = 0, j = 0;

  if (arg == 0) {
    dst[i] = '0';
    i++;
  } else {
    while (arg > 0) {
      if (i % 10 == 0) {
        dst = realloc(dst, sizeof(char) * (i + dst_size));
      }
      dst[i] = '0' + arg % 10;
      arg /= 10;
      i++;
    }
  }
  dst[i] = '\0';

  s21_reverse_string(&dst, j, i);

  return dst;
}

/*
  Переводим int в строку (с помощью модуля)
  Потом переворачиваем строку, так как строка записывалась наоборот
*/
char *s21_sprintf_int_to_str(int arg, struct_settings settings) {
  int dst_size = 11;
  char *dst = calloc(dst_size, sizeof(char));
  int i = 0, have_minus = 0;

  if (arg < 0) {
    dst[i] = '-';
    arg = -arg;
    i++, have_minus = 1;
  }

  if (arg == 0) {
    dst[i] = '0';
    i++;
  }

  else {
    while (arg > 0) {
      if (i % 10 == 0) {
        dst = realloc(dst, sizeof(char) * (i + dst_size));
      }
      dst[i] = '0' + arg % 10;
      arg /= 10;
      i++;
    }
  }
  dst[i] = '\0';

  s21_sprintf_int_to_str_end(have_minus, settings, i, dst_size, &dst);

  return dst;
}

/*
  Описание то же, что и у s21_sprintf_int_to_str
*/
char *s21_sprintf_long_int_to_str(long int arg, struct_settings settings) {
  int dst_size = 11;
  char *dst = calloc(dst_size, sizeof(char));
  int i = 0, have_minus = 0;

  if (arg < 0) {
    dst[i] = '-';
    arg = -arg;
    i++, have_minus = 1;
  }

  if (arg == 0) {
    dst[i] = '0';
    i++;
  }

  else {
    while (arg > 0) {
      if (i % 10 == 0) {
        dst = realloc(dst, sizeof(char) * (i + dst_size));
      }
      dst[i] = '0' + arg % 10;
      arg /= 10;
      i++;
    }
  }
  dst[i] = '\0';

  s21_sprintf_int_to_str_end(have_minus, settings, i, dst_size, &dst);

  return dst;
}

/*
  Завершение функций int_to_str - переворот строки в зависимости от того,
  был ли минус до этого или не было
*/
void s21_sprintf_int_to_str_end(int have_minus, struct_settings settings, int i,
                                int dst_size, char **dst) {
  if (have_minus == 1 && settings.precision.dec > (int)s21_strlen((*dst))) {
    (*dst) = realloc((*dst), sizeof(char) * (i + dst_size) + 1);
    **dst = '0';
    (*dst)[i + 1] = '\0';
    s21_reverse_string(dst, 1, i);
  }

  else {
    s21_reverse_string(dst, 0, i);
  }
}

/*
  Заполняем начало строки пробелами в зависимости от ширины
*/
void s21_sprintf_fill_width(char **dst, struct_settings settings) {
  int len = s21_strlen(*dst);

  if (settings.width.num > len) {
    *dst = realloc(*dst, (len + 1 + (settings.width.num - len)) * sizeof(char));
    s21_memset(*dst + len, ' ', settings.width.num - len);

    while (settings.width.num > len) {
      if (settings.minus_width == 0)
        s21_str_shift(dst, len + 1, 1);
      else
        s21_str_shift(dst, len + 1, len + 1);

      len++;
    }

    (*dst)[len] = '\0';
  }
}

/*
  Заполняем начало строки dst нулями в размере precision
*/
void s21_sprintf_fill_precision(char **dst, int precision_decimal) {
  int len = s21_strlen(*dst);

  if (precision_decimal > len) {
    *dst = realloc(*dst, (len + 1 + (precision_decimal - len)) * sizeof(char));
    s21_memset(*dst + len, '0', precision_decimal - len);

    s21_str_shift(dst, precision_decimal, precision_decimal - len);
    (*dst)[precision_decimal] = '\0';
  }
}

/*
  Сдвигает строку 'dst' размера 'dst_size' на 'steps' раз вправо
*/
void s21_str_shift(char **dst, int dst_size, int steps) {
  dst_size--;
  for (int i = 0; i < steps; i++) {
    for (int j = 0; j < dst_size; j++) {
      char tmp = (*dst)[dst_size - j];
      (*dst)[dst_size - j] = (*dst)[dst_size - j - 1];
      (*dst)[dst_size - j - 1] = tmp;
    }
  }
}

/*
  Запись в строку идет с конца:

  Дробная часть -> целая часть -> переворачиваем строку
  -> заполняем остаток нулями

  Для примера, изначально получили float = 123.4567
  Запись пойдет так:

  7654 (записали дробную часть)
  . (сами поставили точку)
  321 (записали целую части)
  (в итоге получили 7654.321)

  После переворачиваем строку через s21_reverse_string
  и получаем 123.4567

  Основная методика получения дробной и целой части идёт через получения модуля
  от оригинального float/double
*/
char *s21_sprintf_flt_to_str(double arg, struct_settings settings) {
  if (settings.precision.flt == 0) arg = round(arg);
  int dst_size = 13;
  char *dst = calloc(dst_size, sizeof(char));
  int i = 0, j = 0, integersC = 0, floatingsC = 0;

  s21_flt_to_str_entry(&arg, &dst, &i);

  // modf() выделяет дробную часть числа в float_values
  // и целую часть в rounded_values
  double rounded_values = 0;
  double float_values = modf(arg, &rounded_values);

  s21_flt_to_str_write_floats(float_values, &floatingsC, &i, &dst, &dst_size,
                              settings);

  s21_flt_to_str_write_integers(rounded_values, &integersC, &i, &dst,
                                &dst_size);

  s21_reverse_string(&dst, j, i);

  s21_flt_to_str_set_precision(&dst, dst_size, settings, floatingsC);

  return dst;
}

/*
  Если отрицательное, то меняем на положительное и проставляем минус
*/
void s21_flt_to_str_entry(double *arg, char **dst, int *i) {
  if (*arg < 0) {
    (*dst)[*i] = '-';
    *arg = -(*arg);
    (*i)++;
  }
}

/*
  Функция записи дробной части в строку

  Все цифры будут записаны в обратном порядке, поэтому сначала пишем
  дробную часть и ставим точку

  float_values - дробная часть (в виде 0.658xxx)
  floatingsC - кол-во цифр в дробной части
  i - индекс в строке для записи
  dst - сама строка
  dst_size - размер массива строки
  precision - точность, кол-во цифр в дробной части для вывода
*/
void s21_flt_to_str_write_floats(double float_values, int *floatingsC, int *i,
                                 char **dst, int *dst_size,
                                 struct_settings settings) {
  int have_precision = settings.precision.flt;
  while (trunc(float_values) != float_values) {
    float_values *= 10;
    (*floatingsC)++;
  }
  long tmp = trunc(float_values);
  int floatingsCopy = *floatingsC;

  if (floatingsCopy > settings.precision.flt) {
    for (int j = 0; j < floatingsCopy - settings.precision.flt; j++) {
      float_values /= 10;
      tmp = lround(float_values);
    }
  }

  while (!(tmp < 1)) {
    *dst_size += *i;
    if (*i % 10 == 0) {
      *dst = realloc(*dst, sizeof(char) * (*dst_size));
    }
    (*dst)[*i] = '0' + tmp % 10;
    tmp /= 10;
    (*i)++, floatingsCopy--;
  }
  if (have_precision) (*dst)[(*i)++] = '.';
}

/*
  Функция записи целой части в строку

  Работает со значением, не превышающим
  макс. размера типа данных float

  rounded_values - целая часть (в виде 1234xxx.0)
  integersC - кол-во цифр в целой части
  i - индекс в строке для записи
  dst - сама строка
  dst_size - размер массива строки
*/
void s21_flt_to_str_write_integers(double rounded_values, int *integersC,
                                   int *i, char **dst, int *dst_size) {
  if (rounded_values >= 0 && rounded_values < 1) {
    (*dst)[*i] = '0';
    (*i)++, (*integersC)++;
  }

  while (!(rounded_values < 1)) {
    *dst_size += *i + 1;
    if (*i % 10 == 0) {
      *dst = realloc(*dst, sizeof(char) * (*dst_size));
    }
    (*dst)[*i] = '0' + (int)fmod(trunc(rounded_values), 10.0);
    rounded_values /= 10.0;
    (*i)++;
  }
  (*dst)[*i] = '\0';
}

/*
  Переворот строки, нужен после конвертаций чисел в строки
  j --- начало строки
  i --- конец строки
*/
void s21_reverse_string(char **dst, int j, int i) {
  if ((*dst)[0] == '-') {
    j++;
  }

  for (i--; j < i; j++, i--) {
    char tmp = (*dst)[j];
    (*dst)[j] = (*dst)[i];
    (*dst)[i] = tmp;
  }
}

/*
  Если указана точность (precision) больше, чем дробная часть,
  то заполняем остаток места нулями.
*/
void s21_flt_to_str_set_precision(char **dst, int dst_size,
                                  struct_settings settings, int floatingsC) {
  *dst = realloc(*dst, sizeof(char) * (dst_size + settings.precision.flt + 1));
  char *tmp = S21_NULL;
  if (dst != S21_NULL) tmp = s21_strchr(*dst, '.');

  if (tmp != S21_NULL) {
    s21_memset(tmp + 1 + floatingsC, '0', settings.precision.flt);
    tmp++;
    tmp[settings.precision.flt] = '\0';
  }
}

/*
  Если format '%' без валидного спецификатора (%r / %.r)
*/
void s21_sprintf_invalid_spec(char **str, const char **format, int *i) {
  // str = '%'
  (*str)[*i] = (*format)[*i], (*i)++;
  // str = '.'
  (*str)[*i] = (*format)[*i], (*i)++;
  // Пропускаем нули
  while ((*format)[*i] == '0') (*format)++;

  // Это срабатывает при невалидной точности
  if ((*str)[*i - 1] == '.' && !s21_is_number((*format)[*i])) {
    (*str)[*i] = '0';
    (*i)++, (*format)--;
  }

  // Это при невалидной ширине и точности
  for (; (*format)[*i] != 0 && (*format)[*i] != '%'; (*i)++) {
    (*str)[*i] = (*format)[*i];
  }
  (*i)--;
}