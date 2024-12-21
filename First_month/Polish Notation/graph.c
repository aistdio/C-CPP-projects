#include "pNotation.h"
// #include <math.h>

#define PI M_PI
#define MAX_X 1.0
#define MIN_X -1.0
#define MAX_Y 4 * M_PI
#define MIN_Y 0
#define WIDTH 80
#define HEIGHT 25
/*

ИЗ STACK.h


typedef struct node {
    char *value;
    struct node *next;
} node;

---
node *init();
void push(node *root, char *value);
char *pop(node *root);
// void destroy(node *root);
void output(node *root);
double calculate(node *root, double x);
double getNearest(double *matrix, double num);

---


    Print
    for (node *ptr = root; ptr != NULL; ptr = ptr->next)
        printf("%s\n", ptr->value);

---
Для pop всегда нужно присвоение выходных значений
Нельзя:
pop(root);
    output(root);

    destroy(root);
Нужно:
char *test = pop(root);

---
При создании "char *" смотрите, чтобы последний элемент был "\0"
*/

// void calculate(node *root, int x, char *test_input);
void output(node *root);
double calculate(node *root, double x);
int getNearest(double *matrix, double num);

int main() {
    node *root = init();

    // char *test_input = "2 + 2 + 3x";

    // if (test_input) {
    //     int test_x = 1;

    //     calculate(root, test_x, test_input);
    // }

    // char test_input1[] = "tan(x)*ctg(x)/ln(x)*cos(sin(2*x))";
    char *input = (char *)malloc(sizeof(char) * 1000);
    input[0] = 0;
    int i = 0;
    while (input[i] != '\n') {
        scanf("%c", input);
    }
    input_stack(root, input);

    output(root);

    free(input);
    destroy(root);

    return 0;
}

void output(node *root) {
    double values[WIDTH] = {0};
    double defines[HEIGHT] = {0};

    for (int i = 0; i < WIDTH; i++) {  //
        double X = (double)i * MAX_Y / WIDTH;
        values[i] = calculate(root, X);
        // printf("%lf %lf\n", values[i], X);
    }

    int i = 0;
    for (int j = -12; j <= 12; j++) {  //
        double Y = (double)j * 2 / (HEIGHT - 1);
        defines[i] = Y;
        i++;
        // printf("%lf %d\n", defines[i -1], i - 1);
    }

    for (i = 0; i < HEIGHT; i++) {  // SWITCH HEIGHT WIDTH
        for (int j = 0; j < WIDTH; j++) {
            int nearest = getNearest(defines, values[j]);
            // printf("val:%lf near:%lf\n", values[j], nearest);
            // printf(":x:%d values[i]:%lf y:%d defines[j]:%lf nearest:%d\n", i, values[i], j, defines[j],
            // nearest);
            if (nearest == i) {
                // if ((int)nearest == i && values[j] <= MAX_Y && values[j] >= MIN_Y) {
                printf("*");
            } else {
                printf(".");
            }
        }
    }
}

// Вывести парсинг в отдельную функцию, файл с нотацией

double calculate(node *root, double x) {
    // printf("%s|%d| ", root->value, y);

    // char *test_input1 = "sin(cos(2*x))";
    // char *test_input1 = "sin(cos(2*x))";

    // char *test_input = (char *)malloc(sizeof(char) * strlen(test_input1));
    // strcpy(test_input, test_input1);

    double result = notation(root, x);

    // double result = sin(cos(2 * x));
    // printf("RESULT: %lf\n", result);
    // free(test_input);
    return result;
}

// void destroy(node *root) {
//     printf("%s", root->value);
//     for (node *ptr = root->next; ptr->next != NULL; root = ptr, ptr = ptr->next)
//         free(root);
//     free(root);
// }

int getNearest(double *defines, double num) {
    double min_diff = fabs(defines[0] - num);
    int result = 0;

    for (int i = 0; i < HEIGHT; i++) {
        // printf("val:%lf num:%lf\n", defines[i], num);
    }

    for (int i = 0; i < HEIGHT; i++) {
        double current_diff = fabs(defines[i] - num);

        if (current_diff < min_diff) {
            min_diff = current_diff;
            result = i;
        }
    }

    // return result * (-1.0 + HEIGHT) / 2.0;
    return result;
}