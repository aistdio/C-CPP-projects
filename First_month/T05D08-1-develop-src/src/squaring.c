#include <stdio.h>
#define NMAX 10

int input(int *a, int *n);
void output(int *a, int n, int error);
void squaring(int *a, int n);

int main() {
    int n, data[NMAX], error = 1;
    if (input(data, &n)) {
        squaring(data, n);
        error = 0;
    }
    output(data, n, error);

    return 0;
}

int input(int *a, int *n) {
    int result = 1;
    char tmp;
    if (scanf("%d%c", n, &tmp) != 2 || *n > NMAX || *n <= 0 || tmp != '\n') {
        result = 0;
    }
    if (result) {
        for (int i = 0; i < *n; i++) {
            if (!(scanf("%d%c", a + i, &tmp) == 2 && (tmp == '\n' || tmp == ' '))) {
                result = 0;
                break;
            }
        }
    }
    return result;
}

void output(int *a, int n, int error) {
    if (!error) {
        for (int i = 0; i < n - 1; i++) {
            printf("%d ", *(a + i));
        }
        printf("%d", *(a + n - 1));
    } else {
        printf("n/a");
    }
}

void squaring(int *a, int n) {
    for (int i = 0; i < n; i++) {
        *(a + i) *= *(a + i);
    }
}
