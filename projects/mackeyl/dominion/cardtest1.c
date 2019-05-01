/**********************************************************************************
* Unit test for the Adventurer card implementation in dominion.c
* Sources: assignment 3 assistance (2) code, cardtest4.c provided code
* To run, makefile should include:
* testPlayAdventurerBoundary: cardtest1.c dominion.o rngs.o
*     gcc -o testPlayAdventurerBoundary -g cardtest1.c dominion.o rngs.o $(CFLAGS)
***********************************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "rngs.h"

#define MYDEBUG 1

// boundary unit test for Adventurer card
int main()
{
    // declare variables
    int seed = 1000;
    int numPlayers = 2;
    int cards[10] = {adventurer, outpost, salvager, village, minion, mine, cutpurse,
           sea_hag, estate, smithy};
    struct gameState state, prevState;
    int deckSize = 10;
    //int handSize = 5;
    int k, l, n, o, p, q, r, s, t, u, v, y;
    int numHandPre[2] = {0, 0};
    int numTreasurePre[2] = {0, 0};
    int numTreasurePost[2] = {0, 0};
    //int numDiscard[2] = {0, 0};
    int flag = 0;
    int fails = 0;

    // initialize the game
    memset(&state, 23, sizeof(struct gameState));
    initializeGame(numPlayers, cards, seed, &state);

    printf("\n*********** Testing Adventurer Card Function (Boundary) ***********\n\n");

    // copy previous game state to check later
    memcpy(&prevState, &state, sizeof(struct gameState));

    // manually reset the deck to have 0 treasures (lower boundary)
    // for (i = 0; i < numPlayers; i++)
    // {
    //     state.deckCount[i] = 0;
    //     for (j = 0; j < deckSize - 8; j++)
    //     {
    //         state.deck[i][j] = minion;
    //         state.deckCount[i]++;    
    //     }
    //     for (j = deckSize - 8; j < deckSize; j++)
    //     {
    //         state.deck[i][j] = estate;
    //         state.deckCount[i]++;
    //     }
    // }

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

    // reset hand and then draw from new deck into hand for player 1
    // state.handCount[1] = 0;
    // state.deckCount[1] = 5;
    // for (m = 0; m < handSize; m++)
    // {
    //     drawCard(1, &state);
    // }

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

    // get number of total cards in hand before play
    numHandPre[0] = state.handCount[0];
    numHandPre[1] = state.handCount[1];

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

    //play the Adventurer card for both players
    for (r = 0; r < numPlayers; r++) 
    {
        cardEffect(adventurer, 0, 0, 0, &state, 0, 0);
        state.whoseTurn = 1;
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

    // after play, hand should have increased by 2 cards overall
    printf("Test 1: +2 cards in hand for each player\n");
    printf("Expected player 1 hand count: %d, Actual player 1 hand count: %d\n", numHandPre[0] + 2, state.handCount[0]);
    printf("Expected player 2 hand count: %d, Actual player 2 hand count: %d\n\n", numHandPre[1] + 2, state.handCount[1]);
    if ((state.handCount[0] == numHandPre[0] + 2) && (state.handCount[1] == numHandPre[1] + 2))
        printf("Test 1: PASS\n\n");
    else
    {
        printf("Test 1: FAIL\n\n");
        fails++;
    }

    // after play, hand should have +2 treasure cards
    printf("Test 2: +2 treasure cards in hand for each player\n");
    printf("Expected player 1 treasure count: %d, Actual player 1 treasure count: %d\n", numTreasurePre[0] + 2, numTreasurePost[0]);
    printf("Expected player 2 treasure count: %d, Actual player 2 treasure count: %d\n\n", numTreasurePre[1] + 2, numTreasurePost[1]);
    if ((numTreasurePost[0] == numTreasurePre[0] + 2) && (numTreasurePost[1] == numTreasurePre[1] + 2))
        printf("Test 2: PASS\n\n");
    else
    {
        printf("Test 2: FAIL\n\n");
        fails++;
    }

    // get number of cards that will need to be discarded for each player before play
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

    // after play, anything before treasure cards should be in discard pile
    printf("Test 3: All cards in deck before treasure cards now in discard pile\n");

    // loop through to check what should be discarded for each player
    for (y = 0; y < numPlayers; y++)
    {
        int deckPos = prevState.deckCount[y] - 1;
        int drawnTreasure = 0;
        int index = 0;
        int expectedDiscards[5];

        while (drawnTreasure < 2 && deckPos > 0)
        {
            int card = prevState.deck[y][deckPos];
            if (card == copper || card == silver || card == gold)
            {
                drawnTreasure++;
            }
            else
            {
                expectedDiscards[index] = card;
                index++;
            }

            deckPos--;
        }
        for (int z = 0; z < index; z++)
        {
            if (expectedDiscards[z] != state.discard[y][z])
            {
                flag++;
            }
        }
    }

    if (flag == 0)
        printf("Test 3: PASS\n\n");
    else
    {
        printf("Test 3: FAIL\n\n");
        fails++;
    }

    if (fails == 0)
        printf("Adventurer Card Function (Boundary): All Tests Passed!\n\n");
    else
        printf("Adventurer Card Function (Boundary): Failed %d Tests\n\n", fails);

    return 0;
}