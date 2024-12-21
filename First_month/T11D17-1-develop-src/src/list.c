#include "list.h"

/*
struct door {
    int id;
    int status;
};

struct node {
    struct door door;
    struct node *next;
};
*/

struct node *init(struct door *door) {
    struct node *root = NULL;
    if (door != NULL) {
        root = malloc(sizeof(struct node));

        root->door.id = door->id;
        root->door.status = door->status;
        root->next = NULL;
    }
    return root;
}

struct node *add_door(struct node *elem, struct door *door) {
    // struct node *new = NULL;
    if (elem != NULL && door != NULL) {
        struct node *new = malloc(sizeof(struct node));

        new->door.id = door->id;
        new->door.status = door->status;

        new->next = elem->next;

        elem->next = new;
    }
    return elem;
}

struct node *find_door(int door_id, struct node *root) {
    struct node *ptr = root;
    while (ptr != NULL && ptr->door.id != door_id) {
        ptr = ptr->next;
    }
    return ptr;
}

struct node *remove_door(struct node *elem, struct node *root) {
    struct node *ptr = root;
    while (ptr->next != elem) {
        ptr = ptr->next;
    }
    struct node *tmp = ptr->next;
    ptr->next = ptr->next->next;
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
}