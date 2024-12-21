#include "s21_grep.h"

// grep [options] template [file_name]

// Остановился на -f file
// Нуждается в дебаге -o

// доделать регулярные, потом остальное.

int parse(int argc, char *argv[], int opts[], int file_ind[], int patterns[],
          int filesToGet[], int *error);
int patternsInFiles(const int filesToGet[], char *argv[]);
// char **read_file(char fileN, char **patternsFile);
// regex_t *regs(char *argv[], int patterns[], int opts[], int *error);
void print_files(int filesC, const int file_ind[], regex_t *patterns,
                 char *argv[], int opts[], int pSize, int *error);
int check(char line[], regex_t *patterns, int opts[], int pSize,
          regmatch_t *sub);
// int check(char line[], regex_t *patterns, char *argv[], int optI, int optV,
//           int optH, char *fName, int filesC, int pSize, int flagO);
// char *strstrI(char *line, regex_t *newPatterns, char *fName, int filesC, int
// counter,
//               int patterns[], char *argv[], int flagO);
// char *strstrD(char *line, regex_t *patterns, char *fName, int filesC, int
// counter, char *argv[], int flagO);
void print_num(int counter);

void print_err(int error);

int main(int argc, char *argv[]) {
  enum flags { E, I, V, C, L, N, H, S, F, O };
  argc--;
  int error = 0;
  int filesCount;
  int opts[OPTS_SUM];
  int file_ind[argc];
  int patterns[argc];
  int filesToGet[argc];
  int pSize = 0;

  for (int i = 0; i < OPTS_SUM; i++) opts[i] = 0;
  for (int i = 0; i < argc; i++) {
    file_ind[i] = 0;
    filesToGet[i] = 0;
    patterns[i] = 0;
  }

  if (argc < 2) {
    error = 1;
  } else {
    filesCount =
        parse(argc, argv, opts, file_ind, patterns, filesToGet, &error);

    for (int j = 0; patterns[j] != 0; j++) pSize++;

    int fSize = patternsInFiles(filesToGet, argv);

    if (!error && (pSize != 0 || fSize > 0)) {
      char *line = NULL;
      size_t len = 0;
      ssize_t read;

      int flagI = opts[I] ? REG_ICASE : 0;
      regex_t newPatterns[pSize + fSize];
      fSize = 0;

      for (int i = 0; i < pSize; i++) {
        regcomp(newPatterns + i, argv[patterns[i]], flagI);
      }

      // -f
      for (int j = 0; filesToGet[j] != 0; j++) {
        FILE *fp = fopen(argv[filesToGet[j]], "r");
        if (fp != NULL) {
          while ((read = getline(&line, &len, fp)) != -1) {
            char tmpL[read + 1];

            strcpy(tmpL, line);
            if (tmpL[read - 1] == '\n') tmpL[read - 1] = '\0';

            regcomp(newPatterns + pSize + fSize, tmpL, flagI);

            fSize++;
          }
          fclose(fp);
        }
      }

      if (line != NULL) free(line);
      line = NULL;

      print_files(filesCount, file_ind, newPatterns, argv, opts, pSize + fSize,
                  &error);

      for (int i = 0; i < pSize; i++) {
        regfree(newPatterns + i);
      }
      for (int i = 0; i < fSize; i++) {
        regfree(newPatterns + pSize + i);
      }
    } else if (!error)
      error = 4;
  }

  if (error) {
    print_err(error);
    error = 1;
  }
  return error;
}

int patternsInFiles(const int filesToGet[], char *argv[]) {
  int fSize = 0;
  char *line = NULL;
  size_t len = 0;
  ssize_t read;
  for (int j = 0; filesToGet[j] != 0; j++) {
    FILE *fp = fopen(argv[filesToGet[j]], "r");

    if (fp != NULL) {
      while ((read = getline(&line, &len, fp)) != -1) {
        fSize++;
      }

      fclose(fp);
    }
  }

  if (line != NULL) free(line);
  line = NULL;

  return fSize;
}

int parse(int argc, char *argv[], int opts[], int file_ind[], int patterns[],
          int filesToGet[], int *error) {
  enum flags { E, I, V, C, L, N, H, S, F, O };
  int filesC = 0, patternsC = 0, fReadC = 0;

  for (int i = 1; !(*error) && i < argc + 1; i++) {
    int flag = -1;
    int len = strlen(argv[i]);

    if (len >= 2 && argv[i][0] == '-') {
      for (int j = 1; flag != 0 && j < len; j++) {
        flag = 0;
        for (int k = 0; k < OPTS_SUM; k++) {
          if (argv[i][j] == OPTS[k] && OPTS[k] == 'e') {
            opts[k] = 1;
            flag = 2;
          } else if (argv[i][j] == OPTS[k] && OPTS[k] == 'f') {
            opts[k] = 1;
            flag = 3;
          } else if (argv[i][j] == OPTS[k]) {
            opts[k] = 1;
            flag = 1;
          }
        }
      }
    }
    if (!(*error) && flag == 0) {
    } else if (!(*error) && flag == -1 && !opts[F] && !patternsC &&
               patterns[0] == 0) {
      patterns[0] = i;
    } else if (!(*error) && flag == -1) {
      file_ind[filesC] = i;
      filesC++;
    } else if (!(*error) && flag == 2) {
      if (argv[i + 1] == NULL) {
        *error = 5;
      } else if (patternsC == 0 && patterns[0] != 0) {
        file_ind[filesC] = patterns[0];
        filesC++;
        i++;
        patterns[patternsC] = i;
        patternsC++;
      } else {
        i++;
        patterns[patternsC] = i;
        patternsC++;
      }
    } else if (!(*error) && flag == 3) {
      if (argv[i + 1] == NULL) {
        *error = 6;
      } else {
        i++;
        FILE *fp = NULL;
        if ((fp = fopen(argv[i], "r")) == NULL)
          *error = 4;
        else
          fclose(fp);
        filesToGet[fReadC] = i;
        fReadC++;
      }
    }
  }

  // Debug
  // for (int i = 0; i < OPTS_SUM; i++) {
  //   printf("Option %i: %i\n", i + 1, opts[i]);
  // }
  // fflush(stdout);
  // for (int i = 0; patterns[i] != 0; i++) {
  //   printf("Pattern %i: %s\n", i + 1, argv[patterns[i]]);
  // }
  // for (int i = 0; file_ind[i] != 0; i++) {
  //   printf("File %i: %s\n", i + 1, argv[file_ind[i]]);
  // }
  // fflush(stdout);

  if (!(*error) && filesC == 0) *error = 4;

  return filesC;
}

// regex_t *regs(char *argv[], int patterns[], int opts[], int *error) {
//   enum flags { E, I, V, C, L, N, H, S, F, O };
//   regex_t *newPatterns = NULL;

//   if (!(*error)) {
//     int flagI = opts[I] ? REG_ICASE : 0;

//     int size = 0;
//     for (int i = size; patterns[i] != 0; i++) size++;

//     if (size != 0) newPatterns = malloc(sizeof(regex_t) * size);
//     if (newPatterns == NULL)
//       *error = 4;

//     else {
//       for (int i = 0; !(*error) && i < size; i++) {
//         regcomp(newPatterns + i, argv[patterns[i]], flagI);
//       }
//     }
//   }

//   return newPatterns;
// }

// char **read_file(char fileN, char **patternsFile) {
//   fileN = fileN;
//   return patternsFile;
// }

void print_files(int filesC, const int file_ind[], regex_t *patterns,
                 char *argv[], int opts[], int pSize, int *error) {
  enum flags { E, I, V, C, L, N, H, S, F, O };
  int flag = 0;
  int lastPrinted = -1;
  int found;

  for (int i = 0; !(*error) && file_ind[i] != 0; i++) {
    FILE *fp = NULL;
    int ind = file_ind[i];
    int counter = 1;
    found = 0;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    regmatch_t sub = {0};
    // regmatch_t sub[pSize];
    // for (int j = 0; j < pSize; j++) {
    //   sub[j].rm_eo = 0;
    //   sub[j].rm_so = 0;
    // }

    fp = fopen(argv[ind], "r");

    if (fp == NULL) {
      if (!opts[S])
        printf("s21_grep: %s: No such file or directory\n", argv[ind]);
      flag = 1;
    } else {
      while ((read = getline(&line, &len, fp)) != -1) {
        if (!opts[C] && !opts[L] && !opts[O] &&
            check(line, patterns, opts, pSize, NULL)) {
          if (filesC >= 2 && !opts[H]) printf("%s:", argv[ind]);
          if ((opts[N])) print_num(counter);
          printf("%s", line);
          lastPrinted = line[strlen(line) - 1];
          found++;
        }

        else if (!opts[C] && !opts[L] && opts[O] &&
                 check(line, patterns, opts, pSize, NULL)) {
          char *ptr = NULL;
          if (line != NULL) ptr = line;
          while (ptr != NULL && check(ptr, patterns, opts, pSize, &sub)) {
            if (filesC >= 2 && !opts[H]) printf("%s:", argv[ind]);
            if ((opts[N])) print_num(counter);

            printf("%.*s\n", (int)(sub.rm_eo - sub.rm_so), ptr + sub.rm_so);

            lastPrinted = *(ptr + sub.rm_eo);

            ptr += sub.rm_eo;
            found++;
          }
        }

        else if (opts[C] && !opts[L] &&
                 check(line, patterns, opts, pSize, NULL)) {
          found++;
        }

        else if (opts[L] && check(line, patterns, opts, pSize, NULL)) {
          found++;
        }

        counter++;
      }
      // if (lastPrinted > 32 && lastPrinted < 127) {
      //   if (!opts[C] && !opts[L] && !opts[O] && found && !opts[V])
      //   printf("\n");
      // }
      if (lastPrinted > 32 && lastPrinted < 127) {
        if (!opts[C] && !opts[L] && !opts[O] && found && !opts[V])
          printf("\n");
        else if (!opts[C] && !opts[L] && !opts[O] && found)
          printf("\n");
      }

      if (lastPrinted != -1 && !(lastPrinted > 32 && lastPrinted < 127) &&
          lastPrinted != '\n') {
        if (file_ind[i + 1] != 0)
          if (!opts[C] && !opts[L] && !opts[O] && opts[V]) printf("\n");
      }

      if (opts[L]) {
        if (found) printf("%s\n", argv[ind]);
      } else if (opts[C]) {
        if (filesC >= 2 && !opts[H]) printf("%s:", argv[ind]);
        printf("%d\n", found);
      }
      // else if (opts[V] && found && !opts[O]) {
      //   // if spec char
      //   if (((lastPrinted >= 0 && lastPrinted <= 32) || lastPrinted == 127)
      //   &&
      //       lastPrinted != '\n') {
      //     if (file_ind[i + 1] != 0) printf("\n11");
      //   } else {
      //   }
      // }

      // Here:
      // if ((lastPrinted == 0 && (lastPrinted > 32 && lastPrinted < 127) &&
      //      lastPrinted == 10))
      //   if (file_ind[i + 1] != 0)
      //     if ((opts[V] && found && !opts[O] && !opts[L] && !opts[C]))
      //       printf("\n");

      if (line != NULL) free(line);
      line = NULL;
      fclose(fp);
      fflush(stdout);
    }
  }

  if (lastPrinted != -1 && !(lastPrinted > 32 && lastPrinted < 127) &&
      lastPrinted != '\n') {
    if (!opts[C] && !opts[L] && !opts[O]) printf("\n");
  }

  // Here:
  // if (!(opts[V] && found && !opts[O] && !opts[L] && !opts[C]))
  //   if (((lastPrinted >= 0 && lastPrinted <= 32) || lastPrinted == 127) &&
  //       lastPrinted != '\n')
  //     printf("\n");

  // if spec char
  // if (((lastPrinted >= 0 && lastPrinted <= 32) || lastPrinted == 127) &&
  //     lastPrinted != '\n') {
  //   if (opts[V] && found && !opts[O] && !opts[L] && !opts[C]) printf("\n22");
  //   // else
  //   //   printf("\n");
  // } else if (!opts[V] && found && !opts[O] && !opts[L] && !opts[C])
  //   printf("\n");

  if (flag) *error = 10;
  //   Debug
  //   for (int i = 0; !(*error) && i < filesC; i++) {
  //     printf("File %i: %s\n", i, argv[file_ind[i]]);
  //   }
}

int check(char line[], regex_t *patterns, int opts[], int pSize,
          regmatch_t *sub) {
  enum flags { E, I, V, C, L, N, H, S, F, O };

  int result = 0;
  // int i = 0;

  // if (optI) {
  //   if (!flag) {
  //     while (patterns[i] != 0) {
  //       if (optH) filesC = 1;
  //       if (strstrI(line, argv[patterns[i]], fName, filesC, counter,
  //       patterns,
  //                   argv, flag) != NULL)
  //         result = 1;
  //       i++;
  //     }
  //   } else {
  //     if (optH) filesC = 1;
  //     if (strstrI(line, argv[patterns[i]], fName, filesC, counter, patterns,
  //                 argv, flag) != NULL)
  //       result = 1;
  //   }
  // }

  // else {
  // if (!flagO) {
  size_t nmatch = (sub != NULL) ? 1 : 0;

  if (nmatch == 0) {
    for (int i = 0; i < pSize && result != 1; i++) {
      if (regexec(patterns + i, line, nmatch, sub, 0) == 0) {
        result = 1;
      }
    }
  } else if (line != NULL) {
    regoff_t lowest = -1;
    int tmpS = 0;
    int tmp[pSize];
    for (int i = 0; i < pSize; i++) tmp[i] = -1;

    for (int i = 0; i < pSize; i++) {
      if (regexec(patterns + i, line, nmatch, sub, 0) == 0) {
        if (lowest == -1)
          lowest = sub->rm_so;
        else if (sub->rm_so < lowest)
          lowest = sub->rm_so;

        tmp[tmpS] = i;
        tmpS++;
        result = 2;
      }
    }

    for (int i = 0; tmpS - i > 0 && result == 2; i++) {
      if (regexec(patterns + tmp[i], line, nmatch, sub, 0) == 0) {
        if (sub->rm_so == lowest) result = 1;
      }
    }
    if (result > 1) result = 1;
  }

  // if (optH) filesC = 1;
  // if (strstrD(line, argv[patterns[i]], fName, filesC, counter, patterns,
  //             argv, flagO) != NULL)
  //   result = 1;
  // i++;
  // } else {
  // regmatch_t sub = {0};
  // sub.rm_eo

  // // Что с флагом V
  // for (int i = 0; i < pSize; i++) {
  //   if (regexec(patterns + i, line, 0, NULL, 0) == 0) {

  //     result = 1;
  //   }
  // }

  // if (optH) filesC = 1;
  // if (strstrD(line, argv[patterns[i]], fName, filesC, counter, patterns,
  //             argv, flagO) != NULL)
  //   result = 1;
  // }
  // }

  if (opts[V]) {
    result = !result;
    if (opts[O] && !opts[L] && !opts[C]) result = 0;
  }

  return result;
}

// char *strstrD(char *line, regex_t *patterns, char *fName, int filesC, int
// counter, char *argv[], int flagO) {
//   char *result = NULL;
//   size_t len = strlen(pattern);
//   int flag = 0;

//   char *ptr = line;
//   if (ptr + len - 1 == NULL) flag = 1;

//   while (!flagO && !flag) {
//     if (strlen(ptr) < len)
//       flag = 1;
//     else if (strncmp(ptr, pattern, len) == 0) {
//       result = ptr;
//       flag = 1;
//     } else if (!flag)
//       ptr++;
//   }

//   int i = 0;
//   while (patterns[i] != 0) {
//     len = strlen(argv[patterns[i]]);
//     while (flagO && !flag) {
//       if (strlen(ptr) < len)
//         flag = 1;
//       else if (strncmp(ptr, argv[patterns[i]], len) == 0) {
//         if (filesC >= 2) printf("%s:", fName);
//         if (counter != 0) print_num(counter);
//         printf("%.*s\n", (int)len, ptr);
//         result = ptr;
//         ptr += len;
//       } else if (!flag)
//         ptr++;
//     }
//     i++;
//   }

//   return result;
// }

// char *strstrI(char *line, char *pattern, char *fName, int filesC, int
// counter,
//               int patterns[], char *argv[], int flagO) {
//   char *result = NULL;
//   size_t len = strlen(pattern);
//   int flag = 0;

//   char *ptr = line;
//   if (ptr + len - 1 == NULL) flag = 1;

//   while (!flagO && !flag) {
//     if (strlen(ptr) < len)
//       flag = 1;
//     else if (strncasecmp(ptr, pattern, len) == 0) {
//       result = ptr;
//       flag = 1;
//     } else if (!flag)
//       ptr++;
//   }

//   int i = 0;
//   while (patterns[i] != 0) {
//     len = strlen(argv[patterns[i]]);
//     while (flagO && !flag) {
//       if (strlen(ptr) < len)
//         flag = 1;
//       else if (strncasecmp(ptr, argv[patterns[i]], len) == 0) {
//         if (filesC >= 2) printf("%s:", fName);
//         if (counter != 0) print_num(counter);
//         printf("%.*s\n", (int)len, ptr);
//         result = ptr;
//         ptr += len;
//       } else if (!flag)
//         ptr++;
//     }
//     i++;
//   }

//   return result;
// }

void print_num(int counter) { printf("%d:", counter); }

void print_err(int error) {
  if (error != 10) {
    error--;
    char *texts[] = {"Not enough arguments provided, minimum 2",
                     "Provided ivalid options",
                     "No such file or directory",
                     "No patterns or files provided",
                     "No pattern provided after flag -e",
                     "No pattern provided after flag -f"};
    if (error <= 4) fprintf(stderr, "%s\n", texts[error]);
  }
}