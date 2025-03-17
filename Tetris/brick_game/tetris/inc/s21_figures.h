#ifndef S21_FIGURES_H_
#define S21_FIGURES_H_

#include "s21_figures_default.h"

int init_Figures(int max_figure_size);
void spawn_figure(GameInfo_t *gameInfo, Figures_t *figures, Figure_t *figure,
                  int startX, int startY, int type);
void stopCurrentFigure();
void remove_Figures(Figures_t *figures);

#endif  // S21_FIGURES_H_