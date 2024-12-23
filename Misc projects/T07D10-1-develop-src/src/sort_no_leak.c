#include <stdio.h>
#include <stdlib.h>

int read(int **a, int *n);
void sort(int *a, int n);
void output(int *a, int n, int er);

int main() {
    int n, *data = NULL, error = 0;
    error = read(&data, &n);
    if (!error && n > 1) sort(data, n);
    output(data, n, error);
    if (!error) free(data);
    return 0;
}

int read(int **a, int *n) {
    int error = 0;
    if (scanf("%d", n) != 1 || *n <= 0)
        error = 1;
    else if ((*a = (int *)calloc(*n, sizeof(int))) == NULL)
        error = 1;
    for (int i = 0; i < *n && !error; i++)
        if (scanf("%d", *a + i) != 1) {
            error = 1;
            free(*a);
        }
    return error;
}

void sort(int *a, int n) {
    int tmp, stop = 0;
    do {
        stop = 1;
        for (int i = 0; i < n - 1; i++)
            if (*(a + i) > *(a + i + 1)) {
                tmp = *(a + i + 1);
                *(a + i + 1) = *(a + i);
                *(a + i) = tmp;
                stop = 0;
            }
    } while (!stop);
}

void output(int *a, int n, int er) {
    if (er)
        printf("n/a");
    else {
        for (int i = 0; i < n - 1; i++) {
            printf("%d ", *(a + i));
        }
        printf("%d", *(a + n - 1));
    }
}