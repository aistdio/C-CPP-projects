#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>

typedef struct tests {
    int id;
    int age;
} tests;

struct node {
    tests test;
    struct node *next;
};

struct node *init(tests test);
struct node *push(tests test, struct node *root);
struct node *pop(struct node *root);
void destroy(struct node *root);

#endif