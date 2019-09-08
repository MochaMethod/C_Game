#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    char *name;

    int health, attack, defense;
} Entity;

Entity *createEntity(char *name, int health, int attack, int defense) {
    Entity *e = malloc(sizeof(Entity));

    e->health = health;
    e->attack = attack;
    e->defense = defense;

    e->name = strdup(name);
    
    return e;
};

int randint(int lower, int upper, int count) {
    int i;
    int num;

    srand(time(0));
    int randomNum = rand();

    for (i=0;i<count;i++) {
        num = (randomNum % (upper - lower + 1)) + lower;
    }

    return num;
}

void takeDamage(Entity *e1, Entity *e2) {
    int lower = 0+(e1->defense);
    int upper = e2->attack+e2->health;
    int totalDamage = randint(lower, upper, 1);
    e1->health -= totalDamage;
    printf("%s has taken %d damage. His health is now at %d\n", e1->name, totalDamage, e1->health);
};

int createMap(int x, int y) {
    int map[x][y], count, i;

    count = 0;
    for (int i=0; i<x*y; i++) {
        count++;

        /*
            TODO: 
            Since `srand()` is dependant on time, I cannot rely on the randint function to create random numbers quickly. 
            I will need to change this logic -- or the logic for the srand seed -- for time-independent random numbers.

            Because of this issue, the map will be fully populated with either 1's or 0's.
        */
        map[i][i] = randint(0, 1, 1);
        if (count >= x) {
            count = 0;
            printf("%d\n", map[i][i]);
        } else {
            printf("%d", map[i][i]);
        }
    }
}

int main() {
    Entity *player = createEntity("Bryce", 25, 5, 2);
    Entity *enemy = createEntity("Mark the Goblin", 15, 3, 1);

    takeDamage(player, enemy);

    createMap(10, 5);

    free(player);
    free(enemy);
    return 0;
}




