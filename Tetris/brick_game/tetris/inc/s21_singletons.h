#ifndef S21_SINGLETONS_H_
#define S21_SINGLETONS_H_

#include "s21_back_defines.h"
#include "s21_back_objects.h"
#include "s21_memory.h"

GameInfo_t *getSetGameInfo(GameInfo_t *gameInfo);
FieldSize_t getFieldSize(int *width, int *height);
Figures_t getSetFigures(Figures_t *figures);
Figure_t getSetFigure(Figure_t *figure, int setting);

#endif  // S21_SINGLETONS_H_