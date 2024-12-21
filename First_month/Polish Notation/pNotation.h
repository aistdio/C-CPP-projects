#ifndef PNOTATION_H
#define PNOTATION_H
#ifndef STACK_H
#include "stack.h"
#endif

void input_stack(node *root, char *test_input1);
double notation(node *root, double x);
int prior(char *value);

#endif