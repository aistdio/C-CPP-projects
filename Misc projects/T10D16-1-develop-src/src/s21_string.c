/*
From Chapter 2. List 1. .md
    Chapter 1 - size_t   strlen(const char *);
    Chapter 2 - int      strcmp(const char *, const char *);
    Chapter 3 - char    *strcpy(char *restrict, const char *restrict);
    Chapter 4 - char    *strcat(char *restrict, const char *restrict);
    Chapter 5 - char    *strchr(const char *, int);
    Chapter 6 - char    *strstr(const char *, const char *);
    Chapter 7 - size_t   strnlen(const char *, size_t);
    Chapter 8 - int      strncmp(const char *, const char *, size_t);
*/

#include "s21_string.h"

size_t s21_strlen(const char *str) {
    size_t len = 0;
    if (str != NULL) {
        while (*(str + len) != '\0') {
            len++;
        }
    }
    return len;
}

int s21_strcmp(const char *str1, const char *str2) {
    int result = 1;
    if (str2 != NULL && str1 != NULL) {
        size_t size1 = s21_strlen(str1);
        size_t size2 = s21_strlen(str2);
        if (size1 == size2) {
            for (size_t i = 0; result != 0 && i < size1; i++) {
                if (str1[i] != str2[i]) result = 0;
            }
        } else
            result = 0;
    } else
        result = 0;
    return result;
}

char *s21_strcpy(char *restrict str1, const char *restrict str2) {
    if (str2 != NULL) {
        int i = 0;
        for (; str2[i] != '\0'; i++) str1[i] = str2[i];
        str1[i + 1] = '\0';
    }
    return str1;
}

char *s21_strcat(char *restrict str1, const char *restrict str2) {
    if (str2 != NULL) {
        int len1 = s21_strlen(str1);
        int len2 = s21_strlen(str2);

        for (int i = 0; i < len2; i++) str1[i + len1] = str2[i];
    }
    return str1;
}

char *s21_strchr(char *str, int n) {
    int end = 0;
    int i = 0;
    char *ptr = NULL;

    for (; !end && i < (int)s21_strlen(str); i++) {
        if (str[i] == (char)n) {
            ptr = &(str[i]);
            end = 1;
        }
    }
    return ptr;
}
