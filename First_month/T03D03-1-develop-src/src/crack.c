#include <stdio.h>

void circle(int a, int b);

int main() {
    float a = 0;
    float b = 0;
    if (scanf("%f%f", &a, &b) != 2) {
        printf("n/a");
        return 1;
    }

    circle(a, b);

    return 0;
}

void circle(int a, int b) {
    if ((a * a) + (b * b) < 25.0) {
        printf("GOTCHA");
    } else {
        printf("MISS");
    }
}