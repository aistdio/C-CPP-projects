#include "stack.h"

node *init() {
    node *root = (node *)malloc(sizeof(node));
    root->value = (char *)malloc(sizeof(char));
    root->next = NULL;
    return root;
}

void push(node *root, char *value, int lengthB) {
    node *new = (node *)malloc(sizeof(node));

    new->value = (char *)malloc(sizeof(char) * strlen(value) + 1);

    strncat(new->value, value, lengthB);
    new->value[lengthB] = '\0';

    new->next = root->next;
    root->next = new;
}

char *pop(node *root) {
    char *value = NULL;

    if (root->next != NULL) {
        int len = strlen(root->next->value);
        value = (char *)malloc(sizeof(char) * len + 1);

        strcpy(value, root->next->value);

        node *tmp = root->next;
        if (tmp->next != NULL) root->next = tmp->next;
        free(tmp->value);
        free(tmp);
    }

    return value;
}

void destroy(node *root) {
    for (node *ptr = root->next; ptr != NULL; free(root->value), free(root), root = ptr, ptr = ptr->next)
        ;

    if (root->value != NULL) free(root->value);
    if (root != NULL) free(root);
}