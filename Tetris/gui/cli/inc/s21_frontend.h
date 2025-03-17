#ifndef S21_FRONTEND_H_
#define S21_FRONTEND_H_

#include "s21_frames.h"
#include "s21_process_input.h"

void init_frontend(ScreenInfo_t *screenInfo, int width, int height,
                   int width_scale, int height_scale);
void setup_main_window();
void setup_color();
void draw_frame(GameInfo_t gameInfo);
void exit_frontend();

#endif  // S21_FRONTEND_H_