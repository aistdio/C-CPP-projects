#include <stdio.h>

int fib(int a, int f, int l);

int main() {
    int a = 0;
    char tmp;
    if (scanf("%d%c", &a, &tmp) != 2 || tmp != '\n' || a <= 0) {
        printf("n/a");
        return 0;
    } else if (a == 1 || a == 2) {
        printf("1");
        return 0;
    }
    printf("%d", fib(a - 2, 1, 0));
    return 0;
}

int fib(int a, int f, int l) {
    if (a != 0) {
        return fib(a - 1, f + l, f);
    }
    return f + l;
}