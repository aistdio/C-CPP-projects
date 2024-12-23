#include "pNotation.h"

// Добавить обработку чисел с точкой double atof()

void input_stack(node *root, char *test_input) {
    // char test_input[inputLen + 1];
    // for (int i = 0; i < inputLen; i++) {  // Переворот строки для ввода в стэк    // Не нужен
    //     test_input[i] = test_input1[i];
    // }
    // test_input[inputLen] = '\0';

    // char *operators = "+-*/";
    // int operatorsLen = strlen(operators);
    // char *brackets = "()";
    // int bracketsLen = strlen(brackets);
    char *ops0 = "(U";
    char *ops0f = "sctl";
    char *ops1 = ")";
    char *ops2 = "+-";
    char *ops3 = "*/";
    // char *operations = "+-*/";

    // char postfix[strlen(test_input) * 10];
    // int pSize = 0;

    node *ops = init();

    int flag = 0;
    int skip = 0;
    for (int i = 0, j = strlen(test_input); i < j; i++, i += skip) {
        flag = 0;
        skip = 0;

        for (int k = 0, m = strlen(ops0); !flag && k < m; k++) {
            if (test_input[i] == ops0[k]) {
                push(ops, test_input + i, 1);
                push(root, " ", 1);
                flag = 1;
            }

            for (int k = 0, m = strlen(ops0f); !flag && !skip && k < m; k++) {
                if (test_input[i] == ops0[k]) {
                    if (test_input[i + 1] == 'i')  // Записываем sIn, если второй символ 'i'
                    {
                        push(ops, (test_input + i + 1), 1);
                        push(root, " ", 1);
                        skip = 3;
                    }

                    else if (test_input[i + 1] == 'o')  // Записываем cOs, если второй символ 'o'
                    {
                        push(ops, (test_input + i + 1), 1);
                        push(root, " ", 1);
                        skip = 3;
                    }

                    else if (test_input[i + 1] == 'n')  // Только lN(), нужно для скипа 1-го символа
                    {
                        push(ops, (test_input + i + 1), 1);
                        push(root, " ", 1);
                        skip = 2;
                    }

                    else if (test_input[i + 1] == 'q')  // Только sQrt, нужно для скипа 3-ёх символов
                    {
                        push(ops, (test_input + i + 1), 1);
                        push(root, " ", 1);
                        skip = 4;
                    }

                    else {
                        push(ops, (test_input + i), 1);
                        push(root, " ", 1);
                        skip = 3;  // Скип на все остальные функции два шага
                    }
                }
            }

            for (int k = 0, m = strlen(ops1); !flag && !skip && k < m; k++) {
                if (test_input[i] == ops1[k]) {
                    while (ops->next->value != NULL && prior(ops->next->value) != 0) {
                        char *tmp0 = pop(ops);
                        push(root, tmp0, 1);
                        if (tmp0 != NULL) free(tmp0);
                    }
                    char *toGarbage = pop(root);
                    if (toGarbage != NULL) free(toGarbage);
                    flag = 1;
                }
                // else {
                //     push(ops, test_input + i, 1);
                //     push(root, " ", 1);
                //     flag = 1;
                // }
            }
        }

        for (int k = 0, m = strlen(ops2); !flag && !skip && k < m; k++) {
            if (test_input[i] == ops2[k]) {
                // if (ops->next->value != NULL && prior(ops->next->value) == 3) {
                //     char *tmp0 = pop(ops);
                //     push(root, tmp0, 1);
                //     if (tmp0 != NULL) free(tmp0);
                //     push(ops, test_input + i, 1);
                //     flag = 1;
                // } else {
                push(ops, test_input + i, 1);
                push(root, " ", 1);
                flag = 1;
                // }
            }
        }

        for (int k = 0, m = strlen(ops3); !flag && !skip && k < m; k++) {
            if (test_input[i] == ops3[k]) {
                push(ops, test_input + i, 1);
                push(root, " ", 1);
                flag = 1;
            }
        }

        if (!skip && !flag) {
            char *tmp = (char *)malloc(sizeof(char));
            tmp[0] = test_input[i];
            int size = 1;

            while ((test_input[i + size] >= '0' && test_input[i + size] <= '9') ||
                   test_input[i + size] == '.') {
                tmp[size] = test_input[i + size];
                size++;
            }
            push(root, tmp, size);
            skip += size - 1;
            if (tmp != NULL) free(tmp);
        }
    }

    // int size = 0;
    // char *tmp = NULL;
    // for (node *ptr = ops->next; ptr != NULL; ptr = ptr->next) {
    //     pop(ops)
    // }
    // for (node *ptr = root->next; ptr != NULL; ptr = ptr->next) {

    // }
    // free(tmp);

    // if (ops->next != NULL && ops->next->value != NULL) {
    //     char *tmp = pop(ops);
    //     push(root, tmp, 1);
    //     if (tmp != NULL) free(tmp);
    // }

    // for (node *ptr = ops->next; ptr != NULL && ptr->value != NULL; ptr = ptr->next) {
    //     char *tmp = pop(ops);
    //     push(root, tmp, 1);
    //     if (tmp != NULL) free(tmp);
    // }

    for (node *ptr = ops->next; ptr != NULL; ptr = ptr->next) printf("TEST: %s\n", ptr->value);
    for (node *ptr = root->next; ptr != NULL; ptr = ptr->next) printf("TEST2: %s\n", ptr->value);
    destroy(ops);

    // postfix[pSize + 1] = '0';
    // printf("\n\nTEST END: %s\n", postfix);
}
double notation(node *root, double x) {
    root->next->value = root->next->value;
    // printf("%s", root->next->value);

    double result = cos(2 * x);
    return result;
}

int prior(char *value) {
    int priority = -1;

    if (value != NULL) {
        int flag = 0;
        char *ops0 = "(U";
        char *ops0f = "sctl";
        char *ops1 = ")";
        char *ops2 = "+-";
        // char *ops3 = "*/";

        for (int k = 0, m = strlen(ops0); !flag && k < m; k++) {
            if (value[0] == ops0[k]) {
                flag = 1;
            }
        }

        for (int k = 0, m = strlen(ops0f); !flag && k < m; k++) {
            if (value[0] == ops0f[k]) {
                flag = 1;
            }
        }

        if (!flag) priority = 1;

        for (int k = 0, m = strlen(ops1); !flag && k < m; k++) {
            if (value[0] == ops1[k]) {
                flag = 1;
            }
        }

        if (!flag) priority = 2;

        for (int k = 0, m = strlen(ops2); !flag && k < m; k++) {
            if (value[0] == ops2[k]) {
                flag = 1;
            }
        }

        if (!flag) priority = 3;
    }

    return priority;
}