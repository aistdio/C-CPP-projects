#include <stdio.h>

int max(int a, int b);

int main() {
    int a = 0;
    int b = 0;

    char tmp;
    if (scanf("%d%d%c", &a, &b, &tmp) != 3 && tmp != '\n') {
        printf("n/a");
        return 1;
    }

    printf("%i", max(a, b));
}

int max(int a, int b) {
    if (a > b) {
        return a;
    } else {
        return b;
    }
}