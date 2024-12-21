#include <stdio.h>
#define NMAX 10

int input(int *a, int *n);
void output(int *a, int n, int error);
int max(int *a, int n);
int min(int *a, int n);
double mean(int *a, int n);
double variance(int *a, int n);

void output_result(int max_v, int min_v, double mean_v, double variance_v);

int main() {
    int n = 0, data[NMAX];
    int error = input(data, &n);
    output(data, n, error);
    if (!error) {
        output_result(max(data, n), min(data, n), mean(data, n), variance(data, n));
    }
    return 0;
}

int input(int *a, int *n) {
    int error = 0;
    char tmp;
    if (scanf("%d%c", n, &tmp) != 2 || tmp != '\n' || *n > NMAX || *n <= 0) {
        error = 1;
    } else {
        for (int i = 0; i < *n; i++) {
            if (scanf("%d%c", &a[i], &tmp) != 2 || (tmp != '\n' && tmp != ' ')) {
                error = 1;
                break;
            }
        }
    }
    return error;
}

void output(int *a, int n, int error) {
    if (error) {
        printf("n/a");
    } else {
        for (int i = 0; i < n - 1; i++) {
            printf("%d ", a[i]);
        }
        printf("%d\n", a[n - 1]);
    }
}

int max(int *a, int n) {
    int max = 0;
    for (int i = 0; i < n; i++) {
        max = (max > a[i]) ? max : a[i];
    }
    return max;
}

int min(int *a, int n) {
    int min = *a;
    for (int i = 0; i < n; i++) {
        min = (min < a[i]) ? min : a[i];
    }
    return min;
}

double mean(int *a, int n) {
    double sum = 0;
    for (int i = 0; i < n; i++) {
        sum += a[i];
    }
    return sum / n;
}

double variance(int *a, int n) {
    double sum = 0;
    double m = mean(a, n);
    for (int i = 0; i < n; i++) {
        sum += (a[i] - m) * (a[i] - m);
    }
    return sum / n;
}

void output_result(int max_v, int min_v, double mean_v, double variance_v) {
    printf("%d %d %.6lf %.6lf", max_v, min_v, mean_v, variance_v);
}