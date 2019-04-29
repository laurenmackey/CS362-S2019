/**********************************************************************************
* Unit test for the playOutpost refactored function in dominion.c
* Sources: assignment 3 assistance (2) code, cardtest4.c provided code
* To run, makefile should include:
* playOutpostTest: unittest2.c dominion.o rngs.o
*     gcc -o playOutpostTest -g unittest2.c dominion.o rngs.o $(CFLAGS)
* (where CFLAGS must equal -fprofile-arcs -ftest-coverage)
***********************************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "rngs.h"

#define MYDEBUG 0

int main()
{
    // declare variables
    int seed = 1000;
    int numPlayers = 2;
    int cards[10] = {adventurer, outpost, salvager, village, minion, mine, cutpurse,
           sea_hag, estate, smithy};
    struct gameState state, prevState;
    int deckSize = 10;
    int handSize = 5;
    int i, j;
    int playedCard[2] = {0, 0};
    int handPos = 0;

    // initialize the game
    memset(&state, 23, sizeof(struct gameState));
    initializeGame(numPlayers, cards, seed, &state);

    printf("\n*********** Testing Outpost Card Function ***********\n\n");

    // tests: 
    // no other properties of state should be adjusted, including victory card piles and kingdom card piles
    // other player should not have state.outpostPlayed adjusted
    // should have one fewer card in hand after playOutpost, and that card should be equal to whatever card was in handPos (let's say at 0)
    // note: may have an issue with last one since player 2 doesn't have a hand yet

    // copy previous game state to check later
    memcpy(&prevState, &state, sizeof(struct gameState));

    // get card type of player's card that will be used to test playOutpost
    for (i = 0; i < numPlayers; i++)
    {
        playedCard[i] = state.hand[i][handPos];
    }

    // play the Outpost card for both players
    for (j = 0; j < numPlayers; j++) 
    {
        playOutpost(&state, j, 0);
    }

    // after play, outpostPlayed state should be increased by 1 for each player
    printf("Test 1: +1 outpostPlayed for each player\n");
    printf("Expected state.outpostPlayed: %d, Actual state.outpostPlayed: %d\n\n", prevState.outpostPlayed + numPlayers, state.outpostPlayed);
    assert(state.outpostPlayed == prevState.outpostPlayed + numPlayers);
    printf("Test 1: PASS\n\n");

    // // at end, hand should have +2 treasure cards
    // printf("Test 2: +2 treasure cards in hand for each player\n");
    // printf("Expected player 1 treasure count: %d, Actual player 1 treasure count: %d\n", numTreasurePre[0] + 2, numTreasurePost[0]);
    // printf("Expected player 2 treasure count: %d, Actual player 2 treasure count: %d\n\n", numTreasurePre[1] + 2, numTreasurePost[1]);
    // assert(numTreasurePost[0] == numTreasurePre[0] + 2);
    // assert(numTreasurePost[1] == numTreasurePre[1] + 2);
    // printf("Test 2: PASS\n\n");

    // // get number of cards that will need to be discarded for each player before play
    // for (w = 0; w < numPlayers; w++)
    // {
    //     int startPos = deckSize - state.handCount[w];
    //     for (x = startPos; x > -1; x--)
    //     {
    //         if (state.deck[w][x] != copper && state.deck[w][x] != silver && state.deck[w][x] != gold)
    //         {
    //             numDiscard[w]++;
    //         }
            
    //     }
    // }

    // if (MYDEBUG)
    //     printf("Num discard for player 1 is: %d\nNum discard for player 2 is: %d\n", numDiscard[0], numDiscard[1]);

    // // at end, anything before treasure cards should be in discard pile
    // printf("Test 3: All cards in deck before treasure cards now in discard pile\n");
    // for (y = 0; y < numPlayers; y++)
    // {
    //     for (z = 0; z < numDiscard[y]; z++)
    //     {
    //         assert(state.discard[y][z] == estate);
    //     }
    // }
    // printf("Test 3: PASS\n\n");

    // printf("Adventurer Card Function: all tests passed!\n\n");

    return 0;
}