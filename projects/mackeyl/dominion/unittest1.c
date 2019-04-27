/************************************************************************
* Unit test for the updateCoins function in dominion.c
* Source: Assignment 3 Assistance code
* To run, makefile should include:
* updateCoinsTest: unittest1.c dominion.o rngs.o
*     gcc -o updateCoinsTest -g unittest1.c dominion.o rngs.o $(CFLAGS)
* (where CFLAGS must equal -fprofile-arcs -ftest-coverage)
************************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "rngs.h"

void fillAll(int i, int** csg)
{
    if (i % 3 == 0)
    {
        (*csg)[i] = copper;
    }

    else if (i % 3 == 1)
    {
        (*csg)[i] = silver;
    }

    else if (i % 3 == 2)
    {
        (*csg)[i] = gold;
    }
}

void fillTwo(int i, int** cs, int** gs, int** gc)
{
    if (i % 2 == 0)
    {
        (*cs)[i] = copper;
        (*gs)[i] = gold;
        (*gc)[i] = gold;
    }

    else
    {
        (*cs)[i] = silver;
        (*gs)[i] = silver;
        (*gc)[i] = copper;
    }
}

int main()
{
    // declare variables
    int seed = 1000;
    int numPlayer = 2;
    int bonusMax = 5;
    int handMax = 5;
    int bonus;
    int cards[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
    struct gameState state;
    int coppers[MAX_HAND];
    int silvers[MAX_HAND];
    int golds[MAX_HAND];
    int* csg = malloc(MAX_HAND * sizeof(int));
    int* cs = malloc(MAX_HAND * sizeof(int));
    int* gs = malloc(MAX_HAND * sizeof(int));
    int* gc = malloc(MAX_HAND * sizeof(int));


    // set number of treasure cards for this hand: 
    // copper and nothing, silver and nothing, gold and nothing, one of each, copper + silver, silver + gold, copper + gold
    for (int i = 0; i < MAX_HAND; i++)
    {
        coppers[i] = copper;
        silvers[i] = silver;
        golds[i] = gold;

        fillAll(i, &csg);
        fillTwo(i, &cs, &gs, &gc);
    }

    // set number of bonus for this hand: bonus = 0 up to bonus = 5

    // determine expected coins number based on that hand
    
    // check that expected coins equals actual coins

    free(csg);
    free(cs);
    free(gs);
    free(gc);

}