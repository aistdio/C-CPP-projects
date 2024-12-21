#include <stdio.h>
#include <stdlib.h>

#define NMAX 100

void input(int (*a)[NMAX], int **array, int *row, int *col, int *k, int *error);
void staticA(int (*a)[NMAX], int row, int col, int *error);
void dynamic1(int ***array, int row, int col, int *error);
void output(int (*a)[NMAX], int **array, int row, int col, int k, int error);

int main() {
    int row = 0, col = 0, key = 0, error = 0, data[NMAX][NMAX] = {0}, **array = (int **)data;
    input(data, array, &row, &col, &key, &error);
    if (key == 1)
        output(data, array, row, col, key, error);
    else
        output(data, array, row, col, key, error);
    return 0;
}

void input(int (*a)[NMAX], int **array, int *row, int *col, int *k, int *error) {
    if (*error || scanf("%d", k) != 1 || *k <= 0 || *k >= 5) *error = 1;
    if (*error || scanf("%d", row) != 1 || *row <= 0 || (*k == 1 && *row > NMAX)) *error = 1;
    if (*error || scanf("%d", col) != 1 || *col <= 0 || (*k == 1 && *col > NMAX)) *error = 1;

    if (*error || *k == 1)
        staticA(a, *row, *col, error);
    else
        array = NULL;
    if (*error || *k == 2) dynamic1(&array, *row, *col, error);
}

void output(int (*a)[NMAX], int **array, int row, int col, int k, int error) {
    if (error)
        printf("n/a");
    else if (k != 1) {
        for (int i = 0; i < row - 1 && !error; i++) {
            for (int k = 0; k < col - 1 && !error; k++) printf("%d ", array[i][k]);
            printf("%d ", array[i][k - 1]);
            printf("\n");
        }
        for (int k = 0; k < col - 1 && !error; k++) printf("%d ", array[row - 1][k]);
        printf("%d", array[row - 1][col - 1]);
    }

    else {
        for (int i = 0; i < row - 1 && !error; i++) {
            for (int k = 0; k < col - 1 && !error; k++) printf("%d ", a[i][k]);
            printf("%d ", a[i][col - 1]);
            printf("\n");
        }
        for (int k = 0; k < col - 1 && !error; k++) printf("%d ", a[row - 1][k]);
        printf("%d", a[row - 1][col - 1]);
    }
}

void dynamic1(int ***array, int row, int col, int *error) {
    *array = calloc(row, sizeof(int));
    if (*array == NULL) *error = 1;
    for (int i = 0; i < row && !(*error); i++)
        if ((*array[i] = calloc(col, sizeof(int))) == NULL) *error = 1;

    // for (int i = 0; i < row && !(*error); i++)
    //     for (int k = 0; k < col && !(*error); k++, printf("%d", (*array)[i][k])) {
    //         if (scanf("%d", array[i][k]) != 1) {
    //             *error = 1;
    //         }

    //     }
}

void staticA(int (*a)[NMAX], int row, int col, int *error) {
    for (int i = 0; i < row && !(*error); i++)
        for (int k = 0; k < col && !(*error); k++)
            if (scanf("%d", &(a[i][k])) != 1) *error = 1;
}