#include "data_stat.h"

double max(double *data, int n) {
    double max = *data;

    for (int i = 0; i < n; i++) {
        max = (data[i] > max) ? data[i] : max;
    }
    return max;
}

double min(double *data, int n) {
    double min = *data;

    for (int i = 0; i < n; i++) {
        min = (data[i] > min) ? min : data[i];
    }
    return min;
}

double mean(double *data, int n) {
    double sum = 0;
    for (int i = 0; i < n; i++) {
        sum += data[i];
    }
    return sum / n;
}

double variance(double *data, int n) {
    double sum = 0;
    double m = mean(data, n);
    for (int i = 0; i < n; i++) {
        sum += (data[i] - m) * (data[i] - m);
    }
    return sum / n;
}

void sort(double *a, int n) {
    double tmp, stop = 0;
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
