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

#define NOISY 1

// check all properties of the previous state against all properties of the current state
int checkStates(struct gameState prevState, struct gameState state)
{
    int k; 
    int supplyCards[4] = {curse, estate, duchy, province};

    assert(prevState.numPlayers == state.numPlayers);
    if (NOISY)
        printf("Number of players is the same.\n");

    for (k = 0; k < 4; k++)
    {
        assert(prevState.supplyCount[supplyCards[k]] == state.supplyCount[supplyCards[k]]);
        assert(prevState.embargoTokens[k] == state.embargoTokens[k]);
    }

    if (NOISY)
        printf("Supply cards are the same.\n");
        printf("Embargo tokens are the same.\n");
    
    assert(prevState.outpostPlayed == state.outpostPlayed);
    if (NOISY)
        printf("Outpost played is the same.\n");

    assert(prevState.outpostTurn == state.outpostTurn);
    if (NOISY)
        printf("Outpost turn is the same.\n");

    assert(prevState.whoseTurn == state.whoseTurn);
    if (NOISY)
        printf("Whose turn is the same.\n");

    assert(prevState.phase == state.phase);
    if (NOISY)
        printf("Phase is the same.\n");

    assert(prevState.numActions == state.numActions);
    if (NOISY)
        printf("Num actions are the same.\n");

    return 0;
}

int main()
{
    // declare variables
    int seed = 1000;
    int numPlayers = 2;
    int cards[10] = {adventurer, outpost, salvager, village, minion, mine, cutpurse,
           sea_hag, estate, smithy};
    struct gameState state, prevState;
    int i;

    // initialize the game
    memset(&state, 23, sizeof(struct gameState));
    initializeGame(numPlayers, cards, seed, &state);

    printf("\n*********** Testing Outpost Card Function ***********\n\n");

    // copy previous game state to check later
    memcpy(&prevState, &state, sizeof(struct gameState));

    // play the Outpost card for both players
    for (i = 0; i < numPlayers; i++) 
    {
        playOutpost(&state, i, 0);
        // if first player, after play, outpostPlayed should only have incremented by 1
        if (i == 0)
        {
            printf("Test 1: +1 outpostPlayed after player 1 plays card\n");
            printf("Expected state.outpostPlayed: %d, Actual state.outpostPlayed: %d\n\n", prevState.outpostPlayed + 1, state.outpostPlayed);
            assert(state.outpostPlayed == prevState.outpostPlayed + 1);
            printf("Test 1: PASS\n\n");
        }
    }

    // after play, outpostPlayed state should be increased by 1 for each player
    printf("Test 2: +2 outpostPlayed after both players play card\n");
    printf("Expected state.outpostPlayed: %d, Actual state.outpostPlayed: %d\n\n", prevState.outpostPlayed + numPlayers, state.outpostPlayed);
    assert(state.outpostPlayed == prevState.outpostPlayed + numPlayers);
    printf("Test 2: PASS\n\n");

    // after play, no other properties of state should be adjusted
    printf("Test 3: State not otherwise adjusted\n");
    checkStates(prevState, state);
    printf("Test 3: PASS\n\n");

    // after play, each player should have one fewer card in hand
    printf("Test 4: -1 card in each player's hand after playing Outpost card\n");
    printf("Expected hand count for player 1: %d, Actual hand count for player 1: %d\n", prevState.handCount[0] - 1, state.handCount[0]);
    printf("Expected hand count for player 2: %d, Actual hand count for player 2: %d\n\n", prevState.handCount[1] - 1, state.handCount[1]);
    assert(prevState.handCount[0] - 1 == state.handCount[0]);
    assert(prevState.handCount[1] - 1 == state.handCount[1]);
    printf("Test 4: PASS\n\n");

    printf("Outpost Card Function: all tests passed!\n\n");

    return 0;
}