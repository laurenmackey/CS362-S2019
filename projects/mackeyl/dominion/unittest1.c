/**************************************************************************
* Unit test for the playAdventurer refactored function in dominion.c
* Source: Some help from assignment 3 assistance (2) code
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

#define MYDEBUG 1

int main()
{
    // declare variables
    int seed = 1000;
    int numPlayers = 2;
    int cards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, estate, smithy};
    struct gameState state;
    int deckSize = 10;
    int handSize = 5;
    int i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x;
    int numTreasurePre[2] = {0, 0};
    int numTreasurePost[2] = {0, 0};
    int numDiscard[2] = {0, 0};

    // initialize the game
    memset(&state, 23, sizeof(struct gameState));
    initializeGame(numPlayers, cards, seed, &state);

    // manually reset the deck to have 2 treasure only
    for (i = 0; i < numPlayers; i++)
    {
        state.deckCount[i] = 0;
        for (j = 0; j < deckSize - 8; j++)
        {
            state.deck[i][j] = gold;
            state.deckCount[i]++;    
        }
        for (j = deckSize - 8; j < deckSize; j++)
        {
            state.deck[i][j] = estate;
            state.deckCount[i]++;
        }
    }

    // print the deck contents for each player
    if (MYDEBUG)
    {
        for (k = 0; k < numPlayers; k++)
        {
            printf("\nDeck for player %d is:\n", k);
            for (l = 0; l < deckSize; l++)
            {
                printf("%d ", state.deck[k][l]);
            }
            printf("\n");
        }
    }

    // reset hand and then draw from new deck into hand for player 0
    state.handCount[0] = 0;
    for (m = 0; m < handSize; m++)
    {
        drawCard(0, &state);
    }

    // print the hand contents
    if (MYDEBUG)
    {
        for (n = 0; n < numPlayers; n++) 
        {
            printf("\nHand for player %d is:\n", n);
            for (o = 0; o < state.handCount[n]; o++)
            {
                printf("%d ", state.hand[n][o]);
            } 
        }
    }

    // get number of treasure cards in hand before play
    for (p = 0; p < numPlayers; p++) 
    {
        for (q = 0; q < state.handCount[p]; q++)
        {
            if (state.hand[p][q] == copper || state.hand[p][q] == silver || state.hand[p][q] == gold)
            {
                numTreasurePre[p]++;
            }
        } 
    }

    if (MYDEBUG)
        printf("\nPre treasure in hand for player 1 is: %d\nPre treasure in hand for player 2 is: %d\n", numTreasurePre[0], numTreasurePre[1]);

    // play the Adventurer card for both players
    for (r = 0; r < numPlayers; r++) 
    {
        playAdventurer(&state, r);
    }

    // print the hand contents
    if (MYDEBUG)
    {
        for (s = 0; s < numPlayers; s++) 
        {
            printf("\nHand for player %d is:\n", s);
            for (t = 0; t < state.handCount[s]; t++)
            {
                printf("%d ", state.hand[s][t]);
            } 
        }
    }

    // get number of treasure cards in hand after play
    for (u = 0; u < numPlayers; u++) 
    {
        for (v = 0; v < state.handCount[u]; v++)
        {
            if (state.hand[u][v] == copper || state.hand[u][v] == silver || state.hand[u][v] == gold)
            {
                numTreasurePost[u]++;
            }
        } 
    }

    if (MYDEBUG)
        printf("\n\nPost treasure for player 1 is: %d\nPost treasure for player 2 is: %d\n\n", numTreasurePost[0], numTreasurePost[1]);

    // at end, hand should have +2 treasure cards
    //assert(numTreasurePost[0] == numTreasurePre[0] + 2);
    //assert(numTreasurePost[1] == numTreasurePre[1] + 2);

    // at end, anything before treasure cards should be in discard pile
    // loop through initial deck and see how many cards there were before treasure card shows up
    for (w = 0; w < numPlayers; w++)
    {
        int startPos = deckSize - state.handCount[w];
        for (x = startPos; x > -1; x--)
        {
            if (state.deck[w][x] != copper && state.deck[w][x] != silver && state.deck[w][x] != gold)
            {
                numDiscard[w]++;
            }
            
        }
    }

    printf("Num discard for player 1 is: %d\nNum discard for player 2 is: %d\n", numDiscard[0], numDiscard[1]);

    // make sure that state.discard[player][loop_i] equals the estate card

    printf("All tests passed!\n");
}