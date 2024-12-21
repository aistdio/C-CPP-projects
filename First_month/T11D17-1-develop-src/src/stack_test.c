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

char *push_tests(struct node *root);
char *pop_tests(struct node *root);
void destroy(struct node *root);

int main() {
    tests test;
    test.id = 0;
    test.age = 20;

    struct node *root = init(test);

    printf("%s\n", push_tests(root));
    printf("%s", pop_tests(root));

    destroy(root);

    return 0;
}

char *push_tests(struct node *root) {
    int check = 1;
    char *s = "SUCCESS";
    char *f = "FAIL";

    tests test[3];
    test[0].id = 1;
    test[0].age = 22;
    test[1].id = 2;
    test[1].age = 24;
    test[2].id = 3;
    test[2].age = 26;

    root = push(test[0], root);
    root = push(test[1], root);
    root = push(test[2], root);

    struct node *ptr = root->next;

    int i = 2;
    while (ptr != NULL) {
        if (ptr->test.id != test[i].id) check = 0;
        ptr = ptr->next;
        i--;
    }

    return check == 1 ? s : f;
}

char *pop_tests(struct node *root) {
    int check = 1;
    char *s = "SUCCESS";
    char *f = "FAIL";

    root = pop(root);
    root = pop(root);

    if (root->test.id != 0 && root->next->test.id != 1) check = 0;

    return check == 1 ? s : f;
}