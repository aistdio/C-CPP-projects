#include "s21_cat.h"

// cat [OPTION] [FILE]

int parse(int argc, char *argv[], int opts[], int file_ind[], int *error);
void print_files(int filesC, const int file_ind[], char *argv[], int opts[],
                 int *error);
void checkopts(int prev, int tmp, int *flag, int *counter, int *special,
               const int opts[]);
void print_num(int counter);

void print_err(int error);

int main(int argc, char *argv[]) {
  argc--;
  int error = 0;
  int filesCount;
  int opts[OPTS_TOTAL];
  int file_ind[argc];

  for (int i = 0; i < OPTS_TOTAL; i++) opts[i] = 0;

  if (argc < 1) {
    error = 1;
  } else {
    for (int i = 0; i < argc; i++) file_ind[i] = 0;
    filesCount = parse(argc, argv, opts, file_ind, &error);
    print_files(filesCount, file_ind, argv, opts, &error);
  }

  if (error) {
    print_err(error);
    error = 1;
  }
  return error;
}

int parse(int argc, char *argv[], int opts[], int file_ind[], int *error) {
  int options = 0;
  int filesC = 0;

  char *longs_options[] = {B_LONG, N_LONG, S_LONG};

  for (int i = 1; !(*error) && i < argc + 1; i++) {
    int flag = -1;
    int len = strlen(argv[i]);
    if (len > 2 && argv[i][0] == '-' && argv[i][1] == '-') {
      flag = 0;
      for (int k = 0; k < LOPTS_SUM; k++) {
        if (strcmp(*(argv + i) + 2, longs_options[k]) == 0 &&
            opts[OPTS_SUM + k] != 1) {
          opts[OPTS_SUM + k] = 1;
          options++;
          flag = 1;
        } else if (strcmp(*(argv + i) + 2, longs_options[k]) == 0)
          flag = 1;
      }
    } else if (len >= 2 && argv[i][0] == '-') {
      for (int j = 1; flag != 0 && j < len; j++) {
        flag = 0;
        for (int k = 0; k < OPTS_SUM; k++) {
          if (argv[i][j] == OPTS[k] && opts[k] != 1) {
            opts[k] = 1;
            options++;
            flag = 1;
          } else if (argv[i][j] == OPTS[k])
            flag = 1;
        }
      }
    }
    if (flag == 0)
      *error = 2;
    else if (flag == -1) {
      file_ind[filesC] = i;
      filesC++;
    }
  }

  // Delete
  //   for (int i = 0; i < OPTS_TOTAL; i++) {
  //     printf("Option %i: %i\n", i, opts[i]);
  //   }
  //   fflush(stdout);

  if (filesC == 0) *error = 4;
  return filesC;
}

void print_files(int filesC, const int file_ind[], char *argv[], int opts[],
                 int *error) {
  enum flags { b, e, E, n, s, t, T, v, longB, longN, longS };

  int opt = -1;
  for (int i = 0; i < OPTS_TOTAL && opt == -1; i++)
    if (opts[i] == 1) {
      opt = i;
    }

  for (int i = 0; !(*error) && i < filesC; i++) {
    FILE *fp = NULL;
    int ind = file_ind[i];
    int prev = '\n', counter = 1, flag = 0, tmp = 1000;
    fp = fopen(argv[ind], "r");

    if (opts[b]) opts[n] = 0;

    if (fp == NULL) {
      *error = 3;
    } else {
      tmp = fgetc(fp);

      while (!feof(fp)) {
        int special = 0;

        if (!((opts[s] || opts[longS]) && prev == '\n' && tmp == '\n' &&
              flag)) {
          checkopts(prev, tmp, &flag, &counter, &special, opts);
        }
        prev = tmp;
        tmp = fgetc(fp);
      }

      fclose(fp);
      fflush(stdout);
    }
  }

  //   Delete
  //   for (int i = 0; !(*error) && i < filesC; i++) {
  //     printf("File %i: %s\n", i, argv[file_ind[i]]);
  //   }
}

void checkopts(int prev, int tmp, int *flag, int *counter, int *special,
               const int opts[]) {
  enum flags { b, e, E, n, s, t, T, v, longB, longN, longS };

  if (prev == '\n' && tmp == '\n')
    *flag = 1;
  else
    *flag = 0;

  if ((opts[e] || opts[E]) && tmp == '\n') printf("$");

  if ((opts[b] || opts[longB]) && (prev == '\n' || prev == 1000) &&
      tmp != '\n') {
    print_num(*counter);
    (*counter)++;
  }

  if ((opts[n] || opts[longN]) && (prev == '\n' || prev == 1000)) {
    print_num(*counter);
    (*counter)++;
  }

  if ((opts[t] || opts[T]) && tmp == '\t') {
    printf("^I");
    *special = 1;
  }

  if ((opts[e] || opts[t] || opts[v]) &&
      ((tmp >= 0 && tmp <= 31) || tmp == 127) && tmp != '\t' && tmp != '\n') {
    printf("^");
    if (tmp >= 0 && tmp <= 31)
      putchar(tmp + 'A' - 1);
    else if (tmp == 127)
      putchar('?');
    *special = 1;
  }

  if (!(*special)) {
    putchar((char)tmp);
  }
}

void print_num(int counter) { printf("%6d\t", counter); }

void print_err(int error) {
  error--;
  char *texts[] = {"Not enough arguments provided, minimum 2",
                   "Provided ivalid options", "Provided invalid files",
                   "No files provided"};
  fprintf(stderr, "%s\n", texts[error]);
}