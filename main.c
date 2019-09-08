#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
int randomInteger(int seed, int lower, int upper, int count) {
    int i;
    int num;

    if (seed == 0) {
        srand(time(0)); 
    } else {
        srand(seed);
    }

    int randomNum = rand();

    for (i=0;i<count;i++) {
        num = (randomNum % (upper - lower + 1)) + lower;
    }

    return num;
}

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
}

typedef struct {
    int x, y;
    int **map;
} Map;

Map createMap(int size, int x, int y) {
    Map m;
    m.x = x;
    m.y = y;
    m.map = malloc(x * sizeof(int *));

    for (int i=0; i<x; i++) {
        m.map[i] = malloc(y * sizeof(int));
    }

    for (int i=0; i<x; i++) {
        for (int e=0; e<y; e++) {
            m.map[i][e] = randomInteger(i*x+e, 0, 1, 1);
        }
    }

    return m;
}

void takeDamage(Entity *e1, Entity *e2) {
    int lower = 0+(e1->defense);
    int upper = e2->attack+e2->health;
    int totalDamage = randomInteger(0, lower, upper, 1);
    e1->health -= totalDamage;
    printf("%s has taken %d damage. His health is now at %d\n", e1->name, totalDamage, e1->health);
};

    void printMap(Map map) {
        fprintf(stdout, "\n");
        int count = 0;
        for (int i=0; i<map.x; i++) {
            fprintf(stdout, "\n");
            for (int e=0; e<map.y; e++) {
                fprintf(stdout, "%d", map.map[i][e]);
            }
        }
    }

int main() {
    fprintf(stdout, "Determining map size...\n");
    int size, x, y;
    x = 10;
    y = 10;

    if (x > y) {
        size = x;
    } else {
        size = y;
    }

    Entity *player = createEntity("Bryce", 25, 5, 2);
    Entity *enemy = createEntity("Mark the Goblin", 15, 3, 1);
    Map map = createMap(size, x, y);

    fprintf(stdout, "Combat...\n");
    takeDamage(player, enemy);

    fprintf(stdout, "Printing map...\n");
    printMap(map);

    fprintf(stdout, "\nFreeing memory...\n");
    free(player);
    free(enemy);

    for (int i=0; i<x; i++) {
        free(map.map[i]);
    }
    free(map.map);

    return 0;
}