#include <stdio.h>
#define NMAX 10

int read(int *a);
void sort(int *a);
void output(int *a, int er);

int main() {
    int data[NMAX], error = 0;
    error = read(data);
    if (!error) {
        sort(data);
    }
    output(data, error);
    return 0;
}

int read(int *a) {
    int error = 0;
    for (int i = 0; i < NMAX && !error; i++) {
        if (scanf("%d", a + i) != 1) {
            error = 1;
        }
    }
    return error;
}

void sort(int *a) {
    int tmp, stop = 0;
    do {
        stop = 1;
        for (int i = 0; i < NMAX - 1; i++) {
            if (*(a + i) > *(a + i + 1)) {
                tmp = *(a + i + 1);
                *(a + i + 1) = *(a + i);
                *(a + i) = tmp;
                stop = 0;
            }
        }
    } while (!stop);
}

void output(int *a, int er) {
    if (er) {
        printf("n/a");
    } else {
        for (int i = 0; i < NMAX - 1; i++) {
            printf("%d ", *(a + i));
        }
        printf("%d", *(a + NMAX - 1));
    }
}