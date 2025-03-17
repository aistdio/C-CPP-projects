#ifndef S21_TIME_MANAGEMENT_H__
#define S21_TIME_MANAGEMENT_H__

#if !defined(_POSIX_C_SOURCE)
#define _POSIX_C_SOURCE 200809L
#endif
#include <time.h>

#if defined(darwin) || defined(__darwin) || defined(__darwin__)
#define ___USED_BY_DARWIN___
#undef _POSIX_C_SOURCE
#endif
#include <stdlib.h>

#include "s21_back_defines.h"

int speed_time_passed(int level, int uspeed);
int get_random_from_zero(int max);

#undef ___USED_BY_DARWIN___
#endif  // S21_TIME_MANAGEMENT_H__