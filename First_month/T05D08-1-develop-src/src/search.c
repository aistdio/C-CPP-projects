/*
    Search module for the desired value from data array.

    Returned value must be:
        - "even"
        - ">= mean"
        - "<= mean + 3 * sqrt(variance)"
        - "!= 0"

        OR

        0
*/
#include <math.h>
#include <stdio.h>
#define NMAX 30

int input(int *a, int *n);
void output(int n, int error);
double mean(int *a, int n);
double variance(int *a, int n);
int compare(int *a, int length);
int check(int a, double mean_v, double variance_v);

int main() {
    int n = 0, s = 0, data[NMAX];
    int error = input(data, &n);
    if (!error) {
        s = compare(data, n);
    }
    output(s, error);
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

int compare(int *a, int length) {
    int result = 0;
    double m = mean(a, length);
    double v = variance(a, length);
    for (int i = 0; i < length; i++) {
        if (check(a[i], m, v)) {
            result = a[i];
            break;
        }
    }
    return result;
}

int check(int a, double mean_v, double variance_v) {
    int result = 0;
    if (a % 2 == 0 && a >= mean_v && a <= mean_v + 3 * sqrt(variance_v) && a != 0) {
        result = 1;
    }
    return result;
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

void output(int n, int error) {
    if (error) {
        printf("n/a");
    } else {
        printf("%d", n);
    }
}