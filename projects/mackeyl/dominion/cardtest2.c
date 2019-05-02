/**********************************************************************************
* Unit test for the Smithy card implementation in dominion.c
* Sources: assignment 3 assistance (2) code, cardtest4.c provided code
* To run, makefile should include:
* testSmithy: cardtest2.c dominion.o rngs.o
*     gcc -o testSmithy -g cardtest2.c dominion.o rngs.o $(CFLAGS)
***********************************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "rngs.h"

// check all properties of the previous state against all properties of the current state
int statesSame(struct gameState prevState, struct gameState state)
{
    int k; 
    int supplyCards[4] = {curse, estate, duchy, province};
    int statesSame = 1;

    if ((prevState.numPlayers != state.numPlayers) || (prevState.outpostTurn != state.outpostTurn) || (prevState.outpostPlayed != state.outpostPlayed) ||
        (prevState.phase != state.phase) || (prevState.numActions != state.numActions) || (prevState.coins != state.coins) || (prevState.numBuys != state.numBuys))
        statesSame = 0;

    for (k = 0; k < 4; k++)
    {
        if ((prevState.supplyCount[supplyCards[k]] != state.supplyCount[supplyCards[k]]) || (prevState.embargoTokens[k] != state.embargoTokens[k]))
            statesSame = 0;
    }

    return statesSame;
}

int main()
{
    // declare variables
    int seed = 1000;
    int numPlayers = 2;
    int cards[10] = {adventurer, outpost, salvager, village, minion, mine, cutpurse,
           sea_hag, estate, smithy};
    struct gameState state, prevState;
    int i, j, k, l;
    int fails = 0;
    int flag = 0;

    // initialize the game
    memset(&state, 23, sizeof(struct gameState));
    initializeGame(numPlayers, cards, seed, &state);

    printf("\n*********** Testing Smithy Card Function ***********\n\n");

    // copy previous game state to check later
    memcpy(&prevState, &state, sizeof(struct gameState));

    // play the Smithy card for both players
    for (i = 0; i < numPlayers; i++) 
    {
        cardEffect(smithy, 0, 0, 0, &state, 0, 0);
        state.whoseTurn = 1;
    }

    // hand count should have incremented by 2 (+3 - 1 discard) for each player
    printf("Test 1: +2 cards in hand after both players play card\n");
    for (j = 0; j < numPlayers; j++)
    {
        printf("Expected player %d hand count: %d, Actual player %d hand count: %d\n", j + 1, prevState.handCount[j] + 2, j + 1, state.handCount[j]);
        if (state.handCount[j] != prevState.handCount[j] + 2)
            fails++;
    }

    if (fails == 0)
        printf("\nTest 1: PASS\n\n");
    else
        printf("Test 1: FAIL\n\n");

    for (int aa = 0; aa < numPlayers; aa++)
    {
        printf("Deck count for player %d is: %d\n", aa, state.deckCount[aa]);
        printf("Hand count for player %d is: %d\n", aa, state.handCount[aa]);
        printf("Deck Pre for player %d is: ", aa);
        for (int bb = 0; bb < prevState.deckCount[aa]; bb++)
        {
            printf("%d ", prevState.deck[aa][bb]);
        }

        printf("Deck Post for player %d is: ", aa);
        for (int ee = 0; ee < state.deckCount[aa]; ee++)
        {
            printf("%d ", state.deck[aa][ee]);
        }

        printf("\nHand Pre for player %d is: ", aa);
        for (int dd = 0; dd < prevState.handCount[dd]; dd++)
        {
            printf("%d ", prevState.hand[aa][dd]);
        }
        
        printf("\nHand Post for player %d is: ", aa);
        for (int cc = 0; cc < state.handCount[cc]; cc++)
        {
            printf("%d ", state.hand[aa][cc]);
        }
        printf("\n");
    }

    // after play, additional cards in players' hands should be from their deck
    printf("Test 2: cards in hand should be from each player's decks\n");
    for (k = 0; k < numPlayers; k++)
    {
        int deckIndex = prevState.deckCount[k] - 1;
        int handIndex = state.handCount[k] - 1;

        for (l = 0; l < 3; l++)
        {
            int cardPrev = prevState.deck[k][deckIndex];
            int cardPost = state.hand[k][handIndex];
            if (cardPrev != cardPost)
            {
                flag++;
                printf("Flagging for player %d\n", k);
                printf("Card prev: %d, Card post: %d\n", cardPrev, cardPost);
            }
            deckIndex--;
            handIndex--;
        }
    }

    if (flag == 0)
        printf("Test 2: PASS\n\n");
    else
    {
        printf("Test 2: FAIL\n\n");
        fails++;
    }

    // after play, no other properties of state should be adjusted
    printf("Test 3: State not otherwise adjusted\n");
    if (statesSame(prevState, state))
        printf("Test 3: PASS\n\n");
    else
    {
        printf("Test 3: FAIL\n\n");
        fails++;
    }

    if (fails == 0)
        printf("Smithy Card Function: All Tests Passed!\n\n");
    else
        printf("Smithy Card Function: Failed %d Tests\n\n", fails);

    return 0;
}