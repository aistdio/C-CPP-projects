#include "data_io.h"

int input(double **data, int *n) {
    int error = 0;

    if (scanf("%d", n) != 1 || *n <= 0) error = 1;

    if (error || (*data = (double *)malloc(*n * sizeof(double))) == NULL) error = 1;

    for (int i = 0; i < *n; i++) {
        if (scanf("%lf", *(data) + i) != 1) error = 1;
    }
    return error;
}

void output(double *data, int n) {
    for (int i = 0; i < n - 1; i++) {
        printf("%.2lf ", data[i]);
    }
    printf("%.2lf", data[n - 1]);
}