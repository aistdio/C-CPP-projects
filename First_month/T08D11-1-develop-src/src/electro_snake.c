#include <stdio.h>
#include <stdlib.h>
/*
    1 6 7
    2 5 8
    3 4 9
*/
void sort_vertical(int **a, int r, int c, int **result_matrix, int rn, int cn);

/*
    1 2 3
    6 5 4
    7 8 9
*/
void sort_horizontal(int **a, int r, int c, int **result_matrix);

int input(int *n, int *m, int *error);
void dalloc(int ***a, int r, int c);
void output(int **a, int r, int c, int error);
void memFree(int **a, int r, int error);

int main() {
    int **a = NULL, **b = NULL, **b1 = NULL;
    int r = 0;
    int c = 0;
    int error = input(&r, &c, &error);

    if (!error) {
        dalloc(&a, r, c);
        dalloc(&b, r, c);
        dalloc(&b1, r, c);

        for (int i = 0; !error && i < r; i++)
            for (int k = 0; !error && k < c; k++) {
                if (scanf("%d", &(a[i][k])) != 1) error = 1;
            }


        output(a, r, c, error);
        printf("\n\n");
        output(a, r, c, error);

        memFree(a, r, error);
        memFree(b, r, error);
        memFree(b1, r, error);
    } else
        output(a, r, c, error);

    return 0;
}

void dalloc(int ***a, int r, int c) {
    *a = (int **)malloc(r * sizeof(int *));
    for (int i = 0; i < r; i++) {
        (*a)[i] = (int *)malloc(c * sizeof(int));
    }
}


int input(int *n, int *m, int *error) {
    *error = 0;
    if (scanf("%d", n) != 1 || *n <= 0) {
        *error = 1;
    }
    if (scanf("%d", m) != 1 || *m <= 0) {
        *error = 1;
    }
    return *error;
}

void output(int **a, int r, int c, int error) {
    if (!error) {
        for (int i = 0; i < r - 1; i++) {
            for (int k = 0; k < c - 1; k++) {
                printf("%d ", a[i][k]);
            }
            printf("%d", a[i][c - 1]);
            printf("\n");
        }

        for (int k = 0; k < c - 1; k++) {
            printf("%d ", a[r - 1][k]);
        }
        printf("%d", a[r - 1][c - 1]);

    } else {
        printf("n/a");
    }
}

void memFree(int **a, int r, int error) {
    if (!error) {
        for (int i = 0; i < r; i++) {
            free(a[i]);
        }
        free(a);
    }
}