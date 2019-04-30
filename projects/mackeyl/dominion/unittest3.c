/**********************************************************************************
* Unit test for the playSalvager refactored function in dominion.c
* Sources: assignment 3 assistance (2) code, cardtest4.c provided code
* To run, makefile should include:
* playSalvagerTest: unittest3.c dominion.o rngs.o
*     gcc -o playSalvagerTest -g unittest3.c dominion.o rngs.o $(CFLAGS)
* (where CFLAGS must equal -fprofile-arcs -ftest-coverage)
***********************************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "rngs.h"

#define NOISY 0

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
    {
        printf("Supply cards are the same.\n");
        printf("Embargo tokens are the same.\n");
    }
    
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
    int numTests = 20;
    int cards[10] = {adventurer, outpost, salvager, village, minion, mine, cutpurse,
           sea_hag, estate, smithy};
    struct gameState state, prevState;
    int handPos = 0;
    int i;
    int card;
    int cardCost;
    int test1Pass, test2Pass, test3Pass, test4Pass, test5Pass, test6Pass = 0;

    srand(seed);

    printf("\n*********** Testing Salvager Card Function ***********\n\n");

    for (i = 0; i < numTests; i++)
    {
        int cardPos = rand() % 5;

        // initialize the game
        memset(&state, 23, sizeof(struct gameState));
        initializeGame(numPlayers, cards, seed, &state);

        // copy previous game state to check later
        memcpy(&prevState, &state, sizeof(struct gameState));    

        // play the Salvager card for player 1, using a randomly assigned card for each iteration
        card = state.hand[0][cardPos];
        cardCost = getCost( handCard(card, &state) );
        playSalvager(&state, 0, handPos, card);   
        
        // numBuys should go up by 1
        assert(state.numBuys == prevState.numBuys + 1);
        if (state.numBuys == prevState.numBuys + 1)
            test1Pass++;

        // coins should go up by cost of card played
        assert(state.coins == prevState.coins + cardCost);
        if (state.coins == prevState.coins + cardCost)
            test2Pass++;

        // hand should be 2 fewer than before
        assert(state.handCount[0] == prevState.handCount[0] - 2);
        if (state.handCount[0] == prevState.handCount[0] - 2)
            test3Pass++;

        // nothing else in the state should change besides what was already tested for
        if (checkStates(prevState, state) == 0)
            test4Pass++;

        // hand should no longer have the chosen coin card
        assert(state.hand[0][state.handCount[0] + 1] == -1);
        if (state.hand[0][state.handCount[0] + 1] == -1)
        {
            test5Pass++;
        }

        // hand should no longer have the handPos card
        assert(state.hand[0][state.handCount[0]] == -1);
        if (state.hand[0][state.handCount[0]] == -1)
        {
            test6Pass++;
        }
    }

    // check that all tests passed
    printf("Test 1: +1 numBuys after player 1 plays card\n");
    printf("Expected pass number: %d, Actual pass number: %d\n", numTests, test1Pass);
    assert(numTests == test1Pass);
    printf("Test 1: PASS\n\n");

    printf("Test 2: Coins increment by cost of chosen card\n");
    printf("Expected pass number: %d, Actual pass number: %d\n", numTests, test2Pass);
    assert(numTests == test2Pass);
    printf("Test 2: PASS\n\n");

    printf("Test 3: -2 in hand after player 1 plays card\n");
    printf("Expected pass number: %d, Actual pass number: %d\n", numTests, test3Pass);
    assert(numTests == test3Pass);
    printf("Test 3: PASS\n\n");

    printf("Test 4: State not otherwise adjusted\n");
    printf("Expected pass number: %d, Actual pass number: %d\n", numTests, test4Pass);
    assert(numTests == test4Pass);
    printf("Test 4: PASS\n\n");

    printf("Test 5: Hand no longer has chosen coin card\n");
    printf("Expected pass number: %d, Actual pass number: %d\n", numTests, test5Pass);
    assert(numTests == test5Pass);
    printf("Test 5: PASS\n\n");

    printf("Test 6: Hand no longer has played card\n");
    printf("Expected pass number: %d, Actual pass number: %d\n", numTests, test6Pass);
    assert(numTests == test6Pass);
    printf("Test 6: PASS\n\n");

    printf("Salvager Card Function: all tests passed!\n\n");

    return 0;
}