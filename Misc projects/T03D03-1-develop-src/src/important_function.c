#include <math.h>
#include <stdio.h>

float func(int x);

int main() {
    float a = 0;
    if (scanf("%f", &a) != 1) {
        printf("n/a");
        return 1;
    }

    printf("%.1f", func(a));
}

float func(int x) {
    return 7e-3 * pow(x, 4) + ((22.8 * pow(x, 1.0 / 3) - 1e3) * x + 3.0) / (x * x / 2.0) -
           x * pow((10 + x), (2.0 / x)) - 1.01;
}