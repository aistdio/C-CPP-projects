#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int n = 0;
    int error = 0;
    char *docN = (char *)malloc(sizeof(char *));
    if (docN == NULL) error = 2;
    while (n != -1) {
        error = 0;
        FILE *fp = NULL;
        char tmp = 0;
        if (n != 1) {
            n = 0;
            tmp = 0;
            if (scanf("%d", &n) != 1 || (n != 1 && n != -1 && n != 2)) error = 1;
            while ((tmp = getchar()) != '\n' && tmp != ' ') {
            };
        }

        if (error) {
            printf("n/a\n");
        } else if (n == 1) {
            int i = 0, flag = 0;
            for (; !error && !flag; i++) {
                if ((docN = (char *)realloc(docN, sizeof(char) * (i + 2))) == NULL) error = 3;
                if (scanf("%c", &(docN[i])) != 1) error = 3;
                if (docN[i] == '\n' || docN[i] == ' ') flag = 1;
            }
            if (!error && i != 0) docN[i - 1] = '\0';

            if (!error && (fp = fopen(docN, "r")) == NULL) error = 4;

            char *stream = malloc(sizeof(char));

            i = 0;
            while (!error && fread(stream + i, sizeof(char), 1, fp) == 1) {
                if ((stream = (char *)realloc(stream, sizeof(char) * (i + 2))) == NULL) error = 1;
                i++;
            }
            stream[i] = '\0';

            error ? printf("n/a\n") : printf("%s\n", stream);
            // n = error ? -1 : n;

            if (stream != NULL) free(stream);
            stream = NULL;

            n = 0;
            tmp = 0;
            if (scanf("%d", &n) != 1 || (n != 1 && n != -1 && n != 2)) error = 1;
            while ((tmp = getchar()) != '\n' && tmp != ' ') {
            };
            if (error) printf("n/a\n");
            if (fp != NULL) fclose(fp);
            fp = NULL;
        }
        if (n == 2) {
            int i = 0, flag = 0, error = 0;
            if (fp == NULL) {
                error = 1;
                printf("n/a\n");
            }
            char *text = (char *)malloc(sizeof(char));
            while (!flag && !error) {
                if (scanf("%c", text + i) != 1) error = 1;
                if (text[i] == '\n') flag = 1;
            }

            i = 0;
            char *stream = malloc(sizeof(char));
            if (!error && (fp = fopen(docN, "r")) == NULL) error = 1;
            while (!error && fread(stream, sizeof(char), 1, fp) == 1) {
                if ((stream = (char *)realloc(stream, sizeof(char) * (i + 2))) == NULL) error = 1;
                i++;
            }
            stream[i] = '\0';
            printf("%s", (error ? "n/a" : stream));

            if (!error) {
                if (fp != NULL) fclose(fp);
                if ((fopen(docN, "a")) == NULL) error = 1;
            }
            while (!error && (fwrite(stream, sizeof(char), 1, fp) == 1)) {
            }

            if (stream != NULL) free(stream);
            stream = NULL;
            if (text != NULL) free(text);
            text = NULL;
            if (fp != NULL) fclose(fp);
            fp = NULL;
        }
        if (fp != NULL) fclose(fp);
        if (docN != NULL) free(docN);
        docN = NULL;
    }
    return 0;
}