#include <stdio.h>

void sum(int a, int b);
void difference(int a, int b);
void product(int a, int b);
void quotient(int a, int b);

int main() {
    int n = 0;
    int x = 0;

    char tmp;
    if (scanf("%d%d%c", &n, &x, &tmp) != 3 && tmp != '\n') {
        printf("n/a");
        return 1;
    }

    sum(n, x);
    difference(n, x);
    product(n, x);
    quotient(n, x);

    return 0;
}

void sum(int a, int b) { printf("%i ", a + b); }

void difference(int a, int b) { printf("%i ", a - b); }
void product(int a, int b) { printf("%i ", a * b); }
void quotient(int a, int b) {
    if (b != 0) {
        printf("%i", a / b);
    } else {
        printf("n/a");
    }
}