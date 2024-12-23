/*------------------------------------
        Здравствуй, человек!
        Чтобы получить ключ
        поработай с комментариями.
-------------------------------------*/

#include <stdio.h>
#define NMAX 10

int input(int *buffer, int *length);
void output(int *buffer, int error, int number, int size);
int sum_numbers(const int *buffer, int length, int *error);
int find_numbers(const int *buffer, int length, int number, int *numbers, int error);

/*------------------------------------
        Функция получает массив данных
        через stdin.
        Выдает в stdout особую сумму
        и сформированный массив
        специальных элементов
        (выбранных с помощью найденной суммы):
        это и будет частью ключа
-------------------------------------*/
int main() {
    int data[NMAX], result[NMAX], size = 0, n, error = 0, sum = 0;
    error = input(data, &n);
    if (!error) {
        sum = sum_numbers(data, n, &error);
        size = find_numbers(data, n, sum, result, error);
    }
    output(result, error, sum, size);
    return 0;
}

int input(int *buffer, int *length) {
    int error = 0;
    if (scanf("%d", length) != 1 || *length > NMAX || *length <= 0) {
        error = 1;
    }
    for (int i = 0; i < *length && !error; i++) {
        if (scanf("%d", buffer + i) != 1) {
            error = 1;
        }
    }
    return error;
}

/*------------------------------------
        Функция должна находить
        сумму четных элементов
        с 0-й позиции.
-------------------------------------*/
int sum_numbers(const int *buffer, int length, int *error) {
    int sum = 0;
    *error = 1;
    for (int i = 0; i < length; i++) {
        if (buffer[i] % 2 == 0) {
            sum += buffer[i];
            *error = 0;
        }
    }

    return sum;
}

/*------------------------------------
        Функция должна находить
        все элементы, на которые нацело
        делится переданное число и
        записывает их в выходной массив.
-------------------------------------*/
int find_numbers(const int *buffer, int length, int number, int *numbers, int error) {
    int size = 0;
    if (!error) {
        for (int i = 0; i < length; i++) {
            if (buffer[i] != 0 && number % buffer[i] == 0) {
                numbers[size] = buffer[i];
                size++;
            }
        }
    }
    return size;
}

void output(int *buffer, int error, int number, int size) {
    if (error) {
        printf("n/a");
    } else {
        printf("%d\n", number);
        for (int i = 0; i < size - 1; i++) {
            printf("%d ", *(buffer + i));
        }
        printf("%d", buffer[size - 1]);
    }
}