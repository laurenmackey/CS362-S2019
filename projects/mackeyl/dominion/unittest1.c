/**************************************************************************
* Unit test for the playAdventurer refactored function in dominion.c
* Source: Assignment 3 Assistance code
* To run, makefile should include:
* playAdventurerTest: unittest1.c dominion.o rngs.o
*     gcc -o playAdventurerTest -g unittest1.c dominion.o rngs.o $(CFLAGS)
* (where CFLAGS must equal -fprofile-arcs -ftest-coverage)
***************************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "rngs.h"

int main()
{
    // declare variables
    int seed = 1000;
    int numPlayer = 2;
    int cards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};
    struct gameState state;

    // initialize the game
    memset(&state, 23, sizeof(struct gameState));
    game = initializeGame(numPlayer, cards, seed, &state);

    // manually set the deck to have: no treasure, 2 treasure, 3 treasure
    // to do: write a function like the deck creation part of initialize game that sets 
    // deck to have random ordering of non-treasure, and then some treasure depending on scenario

    // get number of treasure cards in hand

    // at end, hand should have +2 treasure cards

    // at end, anything before treasure cards should be in discard pile

}