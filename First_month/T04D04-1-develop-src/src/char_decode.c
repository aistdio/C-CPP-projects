#include <stdio.h>

/*
Выводит только только значение первого символа.
*/

void encode();
void decode();

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("n/a");
    } else if (argv[1][0] == '0') {
        encode();
    } else if (argv[1][0] == '1') {
        decode();
    } else {
        printf("n/a");
    }
    return 0;
}

void encode() {
    char in;
    char tmp = ' ';

    while (tmp != '\n') {
        if (scanf("%c%c", &in, &tmp) != 2) {
            printf("n/a");
            return;
        }
    }
    printf("%i", in);
}

void decode() {
    int in = 0;
    char tmp = ' ';

    while (tmp != '\n') {
        if (scanf("%x%c", &in, &tmp) != 2) {
            printf("n/a");
            return;
        }
    }
    printf("%c", in);
}