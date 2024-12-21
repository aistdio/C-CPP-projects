#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "door_struct.h"

#define DOORS_COUNT 15
#define MAX_ID_SEED 10000

void initialize_doors(struct door* doors);
void sort(struct door* doors);
void output(struct door* doors);

int main() {
    struct door doors[DOORS_COUNT];

    initialize_doors(doors);

    sort(doors);

    output(doors);

    return 0;
}

// Doors initialization function
// ATTENTION!!!
// DO NOT CHANGE!
void initialize_doors(struct door* doors) {
    srand(time(0));

    int seed = rand() % MAX_ID_SEED;
    for (int i = 0; i < DOORS_COUNT; i++) {
        doors[i].id = (i + seed) % DOORS_COUNT;
        doors[i].status = rand() % 2;
    }
}

void sort(struct door* doors) {
    int stop = 0;
    while (!stop) {
        stop = 1;
        for (int i = 0; i < DOORS_COUNT - 1; i++) {
            doors[i].status = 0;
            doors[i + 1].status = 0;
            if (doors[i].id > doors[i + 1].id) {
                stop = 0;
                int tmp = doors[i].id;
                doors[i].id = doors[i + 1].id;
                doors[i + 1].id = tmp;
            }
        }
    }
}

void output(struct door* doors) {
    for (int i = 0; i < DOORS_COUNT - 1; i++) {
        printf("%i, %i\n", doors[i].id, doors[i].status);
    }
    printf("%i, %i", doors[DOORS_COUNT - 1].id, doors[DOORS_COUNT - 1].status);
}