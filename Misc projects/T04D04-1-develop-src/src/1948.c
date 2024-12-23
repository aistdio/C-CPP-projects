/*
Outputs biggest prime divider number.
No division or remainder operators.
*/

#include <math.h>
#include <stdio.h>

int divider(int i, int a);
int prime(int a);
int biggestDivider(int a);

int main() {
    int a = 0;
    char tmp;
    if (scanf("%d%c", &a, &tmp) != 2 || tmp != '\n' || (a >= -1 && a <= 1)) {
        printf("n/a");
        return 0;
    }
    printf("%d", biggestDivider(a));
    return 0;
}

int biggestDivider(int a) {
    a = (a > 0) ? a : -a;

    int b = 0;
    for (int i = a - 1; i > 1; i--) {
        if (divider(i, a) && prime(i)) {
            if (b < i) {
                b = i;
            }
        }
    }
    return b;
}
int divider(int i, int a) {
    while (a > 0) {
        a -= i;
    }
    if (a == 0) {
        return 1;
    }
    return 0;
}
int prime(int a) {
    for (int i = 2; i < a; i++) {
        if (divider(i, a)) {
            return 0;
        }
    }
    return 1;
}