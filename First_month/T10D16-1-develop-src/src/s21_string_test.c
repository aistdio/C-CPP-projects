#include "s21_string.h"

#define CASES 5

void s21_strlen_test();
void s21_strcmp_test();
void s21_strcpy_test();
void s21_strcat_test();
void s21_strchr_test();
void s21_strstr_test();

int main() {
#ifdef QUEST1
    s21_strlen_test();
#endif
#ifdef QUEST2
    s21_strcmp_test();
#endif
#ifdef QUEST3
    s21_strcpy_test();
#endif
#ifdef QUEST4
    s21_strcat_test();
#endif
#ifdef QUEST5
    s21_strchr_test();
#endif
#ifdef QUEST6
    s21_strstr_test();
#endif
    return 0;
}

void s21_strlen_test() {
    char *cases[] = {"Test!", "    ", "123", "", " Test"};
    size_t const results[] = {5, 4, 3, 0, 5};

    for (int i = 0; i < CASES; i++) {
        printf("\nINPUT:%s\n", cases[i]);
        size_t result = s21_strlen(cases[i]);
        printf("OUTPUT:%ld\n", result);
        printf("%s", (result == results[i]) ? "SUCCESS" : "FAIL");
    }
}

void s21_strcmp_test() {
    char *cases[][2] = {{"TEST", "TEST"}, {"tes t", "test"}, {"231", "231"}, {"", ""}, {"     ", "  "}};
    int const results[] = {1, 0, 1, 1, 0};

    for (int i = 0; i < CASES; i++) {
        printf("\nINPUT:%s\t%s\n", cases[i][0], cases[i][1]);
        int result = s21_strcmp(cases[i][0], cases[i][1]);
        printf("OUTPUT:%d\n", result);
        printf("%s", (result == results[i]) ? "SUCCESS" : "FAIL");
    }
}

void s21_strcpy_test() {
    char *cases[] = {"TestCPY!", "    ", "123", "", " Test"};
    char **outputs = (char **)malloc(CASES * sizeof(char *));

    for (int i = 0; i < CASES; i++) {
        outputs[i] = malloc(s21_strlen(cases[i]) * sizeof(char));
        printf("\nINPUT:%s\n", cases[i]);
        char *result = s21_strcpy(outputs[i], cases[i]);
        printf("OUTPUT:%s\n", result);
        printf("%s", (s21_strcmp(result, cases[i]) == 1) ? "SUCCESS" : "FAIL");
        free(outputs[i]);
    }
    free(outputs);
}

void s21_strcat_test() {
    char *cases1[] = {"Test", "tes t ", "1", "", "  "};
    char *cases2[] = {"tseT", "test", "a", "", "     "};
    char *results[] = {"TesttseT", "tes t test", "1a", "", "       "};
    char **output = (char **)malloc(CASES * sizeof(char *));

    for (int i = 0; i < CASES; i++) {
        output[i] = (char *)malloc((s21_strlen(cases1[i]) + s21_strlen(cases2[i]) + 1) * sizeof(char));
        s21_strcpy(output[i], cases1[i]);

        printf("\nINPUT:%s  %s\n", cases1[i], cases2[i]);
        char *result = s21_strcat(output[i], cases2[i]);
        printf("OUTPUT:%s\n", result);
        printf("%s", (s21_strcmp(result, results[i]) == 1) ? "SUCCESS" : "FAIL");

        free(output[i]);
    }
    free(output);
}

void s21_strchr_test() {
    char *cases[] = {"Test", "tes t ", "123"};
    int chars[] = {'e', 's', '2'};

    for (int i = 0; i < CASES - 2; i++) {
        printf("\nINPUT:%s  %c\n", cases[i], chars[i]);
        char *ptr = s21_strchr(cases[i], chars[i]);
        printf("OUTPUT:%c\n", *ptr);
        printf("%s", (chars[i] == *ptr) ? "SUCCESS" : "FAIL");
    }
}

void s21_strstr_test() {}