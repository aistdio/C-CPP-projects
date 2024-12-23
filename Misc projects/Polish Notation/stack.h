#ifndef STACK_H
#define STACK_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    char *value;
    struct node *next;
} node;

node *init();
void push(node *root, char *value, int lengthB);
char *pop(node *root);
void destroy(node *root);

#endif