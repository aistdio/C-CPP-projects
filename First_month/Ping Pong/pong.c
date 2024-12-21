#include <stdio.h>

void render();
void start();
int score();
void instruction();
int frame(int last_winner);
char get_input();
int move_racket1(char in);
int move_racket2(char in);
int move_ballX(int direction);
int move_ballY(int direction);
void win(int player);

int main() {
    render();
    return 0;
}

void render() {
    start();
    instruction();
    win(score());
}

void start() {
    printf("\n\n---\tEnter \"SPACE\" to the terminal to read instruction!\t---\n\n");
    char s = getchar();
    while (s != ' ') {
        s = getchar();
    }
}

void instruction() {
    printf("---\t\t\t INSTRUCTION: \t\t\t---\n\n");
    printf("---   Press corresponding key and hit \"ENTER\" to move   ---\n\n");
    printf("---\t\t\t PLAYER 1: \t\t\t---\n");
    printf("---\t Press 'A' or 'Z' to move the left racket \t---\n\n");
    printf("---\t\t\t PLAYER 2: \t\t\t---\n");
    printf("---\t Press 'K' or 'M' to move the right racket \t---\n\n");
    printf("---\t\tPress 'SPACE' to skip turn\t\t---\n\n\n");
    printf("---\tSend any of the described keys to start!\t---\n\n\n");
    printf("---\tPress \"CTRL + C\" to exit.\t---\n\n\n");
}

int frame(int last_winner) {
    int Height = 25;
    int Width = 80;
    int racket1x = 5;
    int racket1y = Height / 2;
    int racket2x = Width - 6;
    int racket2y = Height / 2;
    int ballx = Width / 2 + 2;
    int bally = Height / 2 + 2;
    int direction = (last_winner == 1) ? 1 : 3;
    int score1 = 0;
    while (score1 == 0) {
        char in = get_input();
        racket1y = (racket1y + move_racket1(in) < 0) ? 1 : racket1y + move_racket1(in);
        racket1y = (racket1y + move_racket1(in) > 22) ? 22 : racket1y + move_racket1(in);
        racket2y = (racket2y + move_racket2(in) < 0) ? 1 : racket2y + move_racket2(in);
        racket2y = (racket2y + move_racket2(in) > 22) ? 22 : racket2y + move_racket2(in);
        direction = (bally == 0) ? direction + 1 : direction;
        direction = (bally == Height - 1) ? direction - 1 : direction;
        if (ballx == racket1x + 1 && bally >= racket1y && bally <= racket1y + 2) {
            direction += 2;
        }
        if (ballx == racket2x - 1 && bally >= racket2y && bally <= racket2y + 2) {
            direction -= 2;
        }
        ballx += move_ballX(direction);
        bally += move_ballY(direction);
        printf("\033[H\033[J");
        for (int i = 0; i < Height; i++) {
            for (int k = 0; k < Width; k++) {
                if (i >= racket1y && i <= racket1y + 2 && k == racket1x) {
                    printf("|");
                } else if (i >= racket2y && i <= racket2y + 2 && k == racket2x) {
                    printf("|");
                } else if (i == bally && k == ballx) {
                    printf("*");
                } else {
                    printf(" ");
                }
            }
            printf("\n");
        }
        score1 = (ballx == 0) ? 2 : score1;
        score1 = (ballx == Width) ? 1 : score1;
    }
    printf("\n\n\t\t\tPlayer %i scored!\t\t\t\n\n", score1);
    return score1;
}

int score() {
    int max_score = 0;
    int score1 = 0;
    int score2 = 0;
    int player = 0;
    while (max_score != 21) {
        player = frame(player);
        if (player == 1) {
            score1++;
        } else if (player == 2) {
            score2++;
        }
        max_score = (score1 > score2) ? score1 : score2;
    }
    int winner = (score1 == max_score) ? 1 : 2;
    return winner;
}

char get_input() {
    char input = getchar();
    if (!(input == 'A' || input == 'a' || input == 'Z' || input == 'z' || input == 'K' || input == 'k' ||
          input == 'M' || input == 'm' || input == ' ')) {
        input = get_input();
    }
    return input;
}

int move_racket1(char in) {
    int result = 0;
    if (in == 'A' || in == 'a') {
        result--;
    } else if (in == 'Z' || in == 'z') {
        result++;
    }
    return result;
}

int move_racket2(char in) {
    int result = 0;
    if (in == 'K' || in == 'k') {
        result--;
    } else if (in == 'M' || in == 'm') {
        result++;
    }
    return result;
}

int move_ballX(int direction) {
    int result = 0;
    if (direction == 3 || direction == 4) {
        result++;
    } else if (direction == 1 || direction == 2) {
        result--;
    }
    return result;
}

int move_ballY(int direction) {
    int result = 0;
    if (direction == 1 || direction == 3) {
        result--;
    } else if (direction == 2 || direction == 4) {
        result++;
    }
    return result;
}

void win(int player) {
    printf("\033[H\033[J");
    printf("\n\n\n\n\n\n\n\n\n--- \t\t\t   WINNER IS PLAYER  %i!  \t\t\t  ---\n\n\n\n\n\n\n\n", player);
}