#include "s21_tetris.h"

int main() {
  game_loop();

  return SUCCESS;
}

void game_loop() {
  bool continue_loop = true;
  while (continue_loop) {
    UserAction_t action = process_input(getch());
    userInput(action, false);
    GameInfo_t gameInfo = updateCurrentState();
    draw_frame(gameInfo);
    if (action == Terminate) {
      continue_loop = false;
    }
  }
}