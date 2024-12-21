/*
Prints "Hello, (input)". Input only int.
*/

#include <stdio.h>

int main() {
    int n = 0;
    char tmp;

    if (scanf("%i%c", &n, &tmp) != 2 && tmp != '\n') {
        return 1;
    }

    printf("Hello, %i!", n);
    return 0;
}