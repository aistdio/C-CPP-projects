#include <ncurses.h>
#include <unistd.h>
#include <stdio.h>

#define HMAX 25
#define WMAX 80
#define LIVE 'o'
#define DEAD ' '

void render(int a[][WMAX], int flag, int field_status, int speed, int counter);
int count_neighbours(int a[][WMAX], int x, int y);
void write_neighbours(int a[][WMAX], int b[][WMAX]);
void update(int a[][WMAX], int b[][WMAX]);
int input(int a[][WMAX]);
void key_input(int *flag, int *speed);
int check_end(int a[][WMAX]);

int main(void) {
    int field[HMAX][WMAX] = {0};
    int friends[HMAX][WMAX] = {0};
    int speed = 1000000;
    int field_status = 1;
    int counter = 0;
    int flag = input(field);

    if (!freopen("/dev/tty", "r", stdin)) flag = 0;

    initscr();
    nodelay(stdscr, TRUE);
    noecho();
    cbreak();
    curs_set(FALSE);
    keypad(stdscr, TRUE);

    while (flag && field_status) {
        counter++;
        key_input(&flag, &speed);
        field_status = check_end(field);
        render(field, flag, field_status, speed, counter);
        write_neighbours(field, friends);
        update(field, friends);
        usleep(speed);
    }

    nocbreak();
    nodelay(stdscr, FALSE);
    endwin();

    return 0;
}

int input(int a[][WMAX]) {
    int i, j, ans = 1;
    for (i = 0; i < HMAX; i++) {
        for (j = 0; j < WMAX; j++) {
            if (!(scanf("%1d", &a[i][j]))) ans = 0;
        }
    }
    return ans;
}

void render(int a[][WMAX], int flag, int field_status, int speed, int counter) {
    clear();
    int i, j;
    for (i = 0; i < HMAX; i++) {
        for (j = 0; j < WMAX; j++) {
            if (a[i][j])
                mvprintw(i + 1, j + 1, "%c", LIVE);
            else
                mvprintw(i + 1, j + 1, "%c", DEAD);
        }
        printw("\n");
    }
    printw("\n");
    for (j = 1; j < WMAX + 1; j++) {
        mvprintw(0, j, "-");
        mvprintw(HMAX + 1, j, "-");
    }
    for (i = 0; i < HMAX + 2; i++) {
        mvprintw(i, 0, "|");
        mvprintw(i, WMAX + 1, "|");
    }
    mvprintw(HMAX + 3, 0,
             "Press \"Q\" to quit the game.\nPress \"0\" to slow down the game.\nPress \"1\" to speed up the "
             "game.");
    mvprintw(HMAX + 7, 0, "Field status = %d, Current cycle = %d\nCurrent speed = %d (1==fast, 15==slow)\n",
             field_status, counter, speed / 100000);
    if (field_status == 0) {
        clear();
        mvprintw(8, 32, "Game over! All cells are dead.");
        refresh();
    }
    if (flag == 0) {
        clear();
        mvprintw(8, 32, "Goodbye!");
        refresh();
    }
    refresh();
}

void write_neighbours(int a[][WMAX], int b[][WMAX]) {
    int i, j;
    for (i = 0; i < HMAX; i++) {
        for (j = 0; j < WMAX; j++) {
            b[i][j] = count_neighbours(a, i, j);
        }
    }
}

int count_neighbours(int a[][WMAX], int x, int y) {
    int dx, dy;
    int count = 0;
    for (dx = -1; dx < 2; dx++) {
        for (dy = -1; dy < 2; dy++) {
            if (a[(HMAX + x + dx) % HMAX][(WMAX + y + dy) % WMAX]) count++;
        }
    }
    if (a[x][y]) count--;
    return count;
}

void update(int a[][WMAX], int b[][WMAX]) {
    int i, j;
    for (i = 0; i < HMAX; i++) {
        for (j = 0; j < WMAX; j++) {
            if (a[i][j]) {
                if ((b[i][j] > 3) || (b[i][j] < 2)) a[i][j] = 0;
            } else if (b[i][j] == 3)
                a[i][j] = 1;
        }
    }
}

void key_input(int *flag, int *speed) {
    char key = getch();
    if (key == 'q' || key == 'Q')
        *flag = 0;
    else if (key == '1' && *speed > 100000)
        *speed -= 100000;
    else if (key == '0' && *speed < 1500000)
        *speed += 100000;
}

int check_end(int a[][WMAX]) {
    int i, j, ans = 0;
    for (i = 0; i < HMAX; i++) {
        for (j = 0; j < WMAX; j++) {
            ans += a[i][j];
        }
    }
    return ans;
}
