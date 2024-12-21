#include <stdio.h>

int main() {
  FILE *fp = fopen("test.txt", "w");

  if (fp != NULL) {
    char *test_case =
        "\n 123    \ttest \n\n\n\n\nyor\ns2!\t\n\n2   asda    2a \t /f\nasds "
        "  "
        " "
        "asdzxc2"
        "asD"
        "a2\ndockerfg asd as!d\n\n43\ns\n\n\n\n\n\n  \t  ";

    fprintf(fp, "%s %c %s", test_case, (char)1, test_case);

    fclose(fp);
  }
  return 0;
}