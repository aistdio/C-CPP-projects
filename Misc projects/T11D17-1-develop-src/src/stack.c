#include "stack.h"

/*
typedef struct tests {
    int id;
    int age;
} tests;

struct node {
    tests test;
    struct node *next;
};
*/

struct node *init(tests test) {
    struct node *root = (struct node *)malloc(sizeof(struct node));
    root->test.age = test.age;
    root->test.id = test.id;
    root->next = NULL;
    return root;
}

struct node *push(tests test, struct node *root) {
    if (root != NULL) {
        struct node *new = (struct node *)malloc(sizeof(struct node));
        new->test.age = test.age;
        new->test.id = test.id;

        new->next = root->next;
        root->next = new;
    }
    return root;
}

struct node *pop(struct node *root) {
    // if null | empty
    struct node *tmp = root->next;
    root->next = root->next->next;
    free(tmp);
    return root;
}

void destroy(struct node *root) {
    struct node *tmp = NULL;
    while (root->next != NULL) {
        tmp = root->next;
        free(root);
        root = tmp;
    }
    free(root);

    // struct node *ptr = root->next;
    // for (; ptr != NULL; ptr = ptr->next) {
    //     free(root);
    // }
}