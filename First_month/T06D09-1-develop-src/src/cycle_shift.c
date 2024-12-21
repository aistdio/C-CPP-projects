#include <stdio.h>

#define NMAX 10

int input(int *buffer, int *length, int *steps);
void swapper(int *result, int length, int steps);
void copy_array(const int *buffer, int *result, int size);
void output(int *result, int size, int error);

int main() {
    int data[NMAX], result[NMAX], n, steps = 0, error = 0;
    error = input(data, &n, &steps);
    if (!error) {
        copy_array(data, result, n);
        swapper(result, n, steps);
    }
    output(result, n, error);
}

int input(int *buffer, int *length, int *steps) {
    int error = 0;
    if (scanf("%d", length) != 1 || *length > NMAX || *length <= 0) {
        error = 1;
    }
    for (int i = 0; i < *length && !error; i++) {
        if (scanf("%d", buffer + i) != 1) {
            error = 1;
        }
    }
    if (!error && scanf("%d", steps) != 1) {
        error = 1;
    }
    return error;
}

void copy_array(const int *buffer, int *result, int size) {
    for (int i = 0; i < size; i++) {
        result[i] = buffer[i];
    }
}

void swapper(int *result, int length, int steps) {
    while (steps > 0 && length != 1) {
        for (int i = 0; i < length - 1; i++) {
            int tmp = result[i + 1];
            result[i + 1] = result[i];
            result[i] = tmp;
        }
        steps--;
    }
    while (steps < 0 && length != 1) {
        for (int i = length - 1; 0 < i; i--) {
            int tmp = result[i - 1];
            result[i - 1] = result[i];
            result[i] = tmp;
        }
        steps++;
    }
}

void output(int *result, int size, int error) {
    if (error) {
        printf("n/a");
    } else {
        for (int i = 0; i < size - 1; i++) {
            printf("%d ", result[i]);
        }
        printf("%d", result[size - 1]);
    }
}