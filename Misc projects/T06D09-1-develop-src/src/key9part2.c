#include <stdio.h>

#define LEN 100

void input(int *buffer, int *length, int *error);
void sum(int *buff1, int len1, int *buff2, int len2, int *out, int *out_length, int *error);
void sub(int *buff1, int len1, int *buff2, int len2, int *out, int *out_length, int *error);
void output(int *buff1, int len1, int *buff2, int len2, int error);

/*
    Беззнаковая целочисленная длинная арифметика
    с использованием массивов.
    Ввод:
     * 2 длинных числа в виде массивов до 100 элементов
     * В один элемент массива нельзя вводить число > 9
    Вывод:
     * Результат сложения и разности чисел-массивов
    Пример:
     * 1 9 4 4 6 7 4 4 0 7 3 7 0 9 5 5 1 6 1
       2 9

       1 9 4 4 6 7 4 4 0 7 3 7 0 9 5 5 1 9 0
       1 9 4 4 6 7 4 4 0 7 3 7 0 9 5 5 1 3 2
*/

int main() {
    int a[LEN] = {0};
    int b[LEN] = {0};
    int alen = 0, blen = 0, error = 0;
    input(a, &alen, &error);
    input(b, &blen, &error);
    int sum_out[LEN + 1] = {0};
    int sum_len = 0;
    int sub_out[LEN] = {0};
    int sub_len = 0;
    sum(a, alen, b, blen, sum_out, &sum_len, &error);
    sub(a, alen, b, blen, sub_out, &sub_len, &error);
    output(sum_out, sum_len, sub_out, sub_len, error);
    return 0;
}

void input(int *buffer, int *length, int *error) {
    char tmp = 0;
    // for (int i = LEN; 0 < LEN && tmp != '\n' && !(*error); i--) {
    //     if (scanf("%d%c", buffer, &tmp) != 2 || (tmp != ' ' && tmp != '\n') || *buffer < 0 || *buffer > 9)
    //     {
    //         *error = 1;
    //     }
    //     (*length)++;
    // }
    // }
    while (tmp != '\n' && !(*error)) {
        if (scanf("%d%c", buffer, &tmp) != 2 || buffer == buffer + LEN || (tmp != ' ' && tmp != '\n') ||
            *buffer < 0 || *buffer > 9) {
            *error = 1;
        }
        buffer++;
        (*length)++;
    }
}

void sum(int *buff1, int len1, int *buff2, int len2, int *out, int *out_length, int *error) {
    if (!error) {
        int curr_buff1 = len1 - 1, curr_buff2 = len2 - 1, curr_out, tmp = 0;
        curr_out = (len1 > len2) ? len1 : len2;
        for (int i = 0; curr_buff1 >= i && curr_buff2 >= i; (*out_length)++) {
            out[curr_out] = (buff1[curr_buff1] + buff2[curr_buff2] + tmp) % 10;
            tmp = (buff1[curr_buff1] + buff2[curr_buff2] + tmp) / 10;
            curr_out--;
            curr_buff1--;
            curr_buff2--;
        }
        for (int i = 0; curr_buff1 >= i && len1 > len2; (*out_length)++) {
            out[curr_out] = (buff1[curr_buff1] + tmp) % 10;
            tmp = (buff1[curr_buff1] + tmp) / 10;
            curr_buff1--;
            curr_out--;
        }
        for (int i = 0; curr_buff2 >= i && len2 > len1; (*out_length)++) {
            out[curr_out] = (buff2[curr_buff1] + tmp) % 10;
            tmp = (buff2[curr_buff2] + tmp) / 10;
            curr_buff1--;
            curr_out--;
        }
        (*out_length)++;
        out[curr_out] += tmp;
    }
}
// int flag = 0;
// if (!(*error)) {
//     int tmp = (len1 > len2) ? len1 : len2;
//     for (int i = 0; i < tmp; i++) {
//         if (buff1[LEN - i - 1] + buff2[LEN - i - 1] <= 9) {
//             result[LEN * 2 - i] += buff1[LEN - i - 1] + buff2[LEN - i - 1];
//         } else {
//             result[LEN * 2 - i] += (buff1[LEN - i - 1] + buff2[LEN - i - 1]) % 10;
//             i++;
//             result[LEN * 2 - i] += 1;
//             flag = 1;
//         }
//         (*result_length)++;
//     }
// }
// if (flag == 1) {
//     (*result_length)++;
// }
// }

void sub(int *buff1, int len1, int *buff2, int len2, int *out, int *out_length, int *error) {
    *error = (len2 > len1) ? 1 : 0;
    if (!error) {
        int curr_buff1 = len1 - 1, curr_buff2 = len2 - 1, curr_out = len1 - 1, tmp = 0;
        *out_length = len1;
        for (int i = 0; !(*error) && curr_buff1 >= i && curr_buff2 >= 0; out_length--) {
            if (buff1[curr_buff1] < buff2[curr_buff2]) {
                if (curr_buff1 == 1) {
                    tmp = 10;
                    buff1[curr_buff1 - 1]--;
                } else {
                    *error = 1;
                }
            }
            out[curr_out] = tmp + buff1[curr_buff1] - buff2[curr_buff2];
            curr_buff1--;
            curr_buff2--;
            curr_out--;
            tmp = 0;
        }
        for (int i = 0; !(*error) && curr_buff1 >= i; curr_out--) {
            if (buff1[curr_buff1] < 0) {
                if (curr_buff1 == 1) {
                    tmp = 10;
                    buff1[curr_buff1 - 1] -= 1;
                } else {
                    *error = 1;
                }
            }
            out[curr_out] = tmp + buff1[curr_buff1] - buff2[curr_buff2];
            curr_buff1--;
            tmp = 0;
        }
    }
}

void output(int *buff1, int len1, int *buff2, int len2, int error) {
    if (!error) {
        for (int *p = &len1; *p > 1 && buff1[0] == 0; (*p)--) {
            buff1++;
        }
        for (int i = 0; i < len1 - 1; i++) {
            printf("%d ", buff1[i]);
        }
        printf("%d\n", buff1[len1 - 1]);

        for (int *p = &len2; *p > 1 && buff2[0] == 0; (*p)--) {
            buff2++;
        }
        for (int i = 0; i < len2 - 1; i++) {
            printf("%d ", buff2[i]);
        }
        printf("%d", buff2[len2 - 1]);
    } else {
        printf("n/a");
    }
}