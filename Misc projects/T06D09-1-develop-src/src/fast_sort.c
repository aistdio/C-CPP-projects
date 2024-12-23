#include <stdio.h>
#define NMAX 10

int read(int *a, int *b);
void bubble_sort(int *a);
void merge_sort();
void output(int *a, int *b, int er);

int main() {
    int data1[NMAX], data2[NMAX], error = 0;
    error = read(data1, data2);
    if (!error) {
        bubble_sort(data1);
        merge_sort(data2);
    }
    output(data1, data2, error);
    return 0;
}

int read(int *a, int *b) {
    int result = 0;
    char tmp;
    for (int i = 0; i < NMAX && !result; i++) {
        if (scanf("%d%c", a + i, &tmp) != 2 || (tmp == '\n' && a + i < a + NMAX - 1) ||
            (tmp != '\n' && a + i == a + NMAX - 1)) {
            result = 1;
        }
    }
}

void merge_sort() {}

void bubble_sort(int *a) {
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

void output(int *a, int *b, int er) {
    if (er) {
        printf("n/a");
    } else {
        for (int i = 0; i < NMAX - 1; i++) {
            printf("%d ", *(a + i));
        }
        printf("%d\n", *(b + NMAX - 1));
        for (int i = 0; i < NMAX - 1; i++) {
            printf("%d ", *(b + i));
        }
        printf("%d", *(b + NMAX - 1));
    }
}