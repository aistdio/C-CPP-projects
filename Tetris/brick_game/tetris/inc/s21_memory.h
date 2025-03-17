#ifndef S21_MEMORY_H_
#define S21_MEMORY_H_

#include <stdlib.h>

int allocate_matrix(int ***matrix, int width, int height);
void free_matrix(int ***matrix, int width);

#endif  // S21_MEMORY_H_