/**
 * @file s21_time_management.c
 * @author aminaall (aminaall@student.21-school.ru)
 * @brief Функции для определения прошедшего времени, генерации случайного числа
 * @version 1.0
 * @date 2025-02-24
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "s21_time_management.h"

/**
 * @brief Получаем текущие сек + наносек время через clock_gettime() и сверяем
 * его с static предыдущее записанное время, определяя прошло ли достаточно
 * времени и можем ли мы совершить действие с фигурой, зависящее от прошедшего
 * времени.
 *
 * Отдельно предусмотрена ситуация, при которой разница в текущем времени и
 * предыдуще записанном времени отличается слишком сильно (это происходит из-за
 * приостановления игры на паузу). Благодаря этому предусмотрению, игра после
 * паузы не ускоряется, "добирая" получившуюся большую разницу в текущем и ранее
 * записанном времени
 *
 * if (difference_ns >= nspeed * 1.1) {}
 * На случай, если была слишком большая разница по времени между вызывами
 * функции (из-за паузы)
 *
 * @param level
 * @param uspeed
 * @return int
 */
int speed_time_passed(int level, int uspeed) {
  int has_enough_time_passed = 0;

  long long nspeed = (uspeed - level * (uspeed / 13)) * 1000000LL;
  static long long overall_ns = 0;
  static struct timespec previous_time = {0};
  struct timespec current_time = {0};

  clock_gettime(CLOCK_MONOTONIC, &current_time);
  if (previous_time.tv_sec == 0 && previous_time.tv_nsec == 0)
    previous_time = current_time;

  long long current_ns =
      current_time.tv_sec * NANO_TO_SECONDS + current_time.tv_nsec;
  long long preious_ns =
      previous_time.tv_sec * NANO_TO_SECONDS + previous_time.tv_nsec;
  long long difference_ns = current_ns - preious_ns;
  overall_ns += difference_ns;
  previous_time = current_time;

  if (difference_ns >= nspeed * 1.1) {
    overall_ns = 0;
  } else if (overall_ns >= nspeed) {
    has_enough_time_passed = 1;
    overall_ns -= nspeed;
  }

  return has_enough_time_passed;
}

/**
 * @brief Получение случайного числа от нуля до max
 *
 * @param max максимальное возвращаемое число
 * @return int случайное число
 */
int get_random_from_zero(int max) {
#ifdef ___USED_BY_DARWIN___
  int result = arc4random_uniform(max + 1);
  return result;
#else
  struct timespec current_time = {0};
  clock_gettime(CLOCK_MONOTONIC, &current_time);
  srand(current_time.tv_nsec);
  int result = rand() % (max + 1);
  return result;
#endif
}