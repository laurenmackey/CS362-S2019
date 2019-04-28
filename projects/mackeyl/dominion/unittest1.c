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
    int numPlayers = 2;
    int cards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, estate, smithy};
    struct gameState state;
    int deckSize = 10;
    int i, j, k, l, m, n, o;
    int numTreasurePre[2] = {0, 0};
    int numTreasurePost[2] = {0, 0};

    // initialize the game
    memset(&state, 23, sizeof(struct gameState));
    initializeGame(numPlayers, cards, seed, &state);

    // manually set the deck to have: no treasure, 2 treasure, 3 treasure
    for (i = 0; i < numPlayers; i++)
    {
        state.deckCount[i] = 0;
        for (j = 0; j < 3; j++)
        {
            state.deck[i][j] = estate;
            state.deckCount[i]++;
        }
        for (j = 3; j < deckSize; j++)
        {
            state.deck[i][j] = minion;
            state.deckCount[i]++;    
        }
    }

    // get number of treasure cards in hand before play
    for (k = 0; k < numPlayers; k++) 
    {
        for (l = 0; l < deckSize; l++)
        {
            if (state.deck[k][l] == copper || state.deck[k][l] == silver || state.deck[k][l] == gold)
            {
                numTreasurePre[k]++;
            }
        } 
    }

    // play the Adventurer card for both players
    for (m = 0; m < numPlayers; m++) 
    {
        printf("About to play adventurer\n");
        playAdventurer(&state, m);
        printf("Played adventurer\n");
        // to do: run gdb to figure out where error is from
        // could also write a function to print the state of the game at any time
    }

    // at end, hand should have +2 treasure cards
    for (n = 0; n < numPlayers; n++) 
    {
        for (o = 0; o < deckSize; o++)
        {
            if (state.deck[n][o] == copper || state.deck[n][o] == silver || state.deck[n][o] == gold)
            {
                numTreasurePost[n]++;
            }
        } 
    }

    printf("Post treasure for player 1 is: %d\n Post treasure for player 2 is: %d\n", numTreasurePost[0], numTreasurePost[1]);

    // at end, anything before treasure cards should be in discard pile

    // do positive test for this (just make sure 2 treasures works), then boundary test for the next (no treasure, 10 treasure)

}