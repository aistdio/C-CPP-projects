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

char *add_door_tests(struct node *root);
char *remove_door_tests(struct node *root);

int main() {
    struct door first;
    first.id = 0;
    first.status = 0;
    struct node *root = init(&first);

    printf("%s\n", add_door_tests(root));

    printf("%s", remove_door_tests(root));

    destroy(root);

    return 0;
}

char *add_door_tests(struct node *root) {
    int check = 1;
    char *s = "SUCCESS";
    char *f = "FAIL";

    struct door test[3];
    test[0].id = 1;
    test[0].status = 0;
    test[1].id = 2;
    test[1].status = 0;
    test[2].id = 3;
    test[2].status = 0;

    root = add_door(root, &test[0]);
    root = add_door(root, &test[1]);
    root = add_door(root, &test[2]);

    struct node *ptr = root;
    ptr = ptr->next;

    int i = 2;
    while (ptr != NULL) {
        // printf("%p\n", ptr);
        // printf("%i  %i\n", ptr->door.id, test[i].id);
        if (ptr->door.id != test[i].id) check = 0;
        ptr = ptr->next;
        i--;
    }

    return check == 1 ? s : f;
}

char *remove_door_tests(struct node *root) {
    int check = 1;
    char *s = "SUCCESS";
    char *f = "FAIL";

    int findit = 2;
    struct node *found = find_door(findit, root);
    remove_door(found, root);

    struct node *ptr = root;
    while (ptr != NULL) {
        if (findit == ptr->door.id) check = 0;
        ptr = ptr->next;
    }

    return check == 1 ? s : f;
}

/*
struct node *init(struct door *door);
struct node *add_door(struct node *elem, struct door *door);
struct node *find_door(int door_id, struct node *root);
struct node *remove_door(struct node *elem, struct node *root);
void destroy(struct node *root);
*/