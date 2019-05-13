/**********************************************************************************
* Random test for the Adventurer card
* To run, makefile should include:
* randomTestAdventurer: randomtestadventurer.c dominion.o rngs.o
*     gcc -o randomTestAdventurer -g randomtestadventurer.c dominion.o rngs.o $(CFLAGS)
***********************************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "rngs.h"

// random test for the Adventurer card
int main()
{
    // declare variables
    int seed = 1000;
    int numPlayers = 2;
    int cards[10] = {adventurer, outpost, salvager, village, minion, mine, cutpurse,
           sea_hag, estate, smithy};
    struct gameState state;
    int i, j, k, l, m, n, o, p, q, r, s, t;
    int numHandPre[2] = {0, 0};
    int numTreasurePre[2] = {0, 0};
    int numHandPost[2] = {0, 0};
    int numTreasurePost[2] = {0, 0};
    int flag = 0;
    int fails = 0;

    srand(time(NULL));

    // initialize the game
    memset(&state, 23, sizeof(struct gameState));
    initializeGame(numPlayers, cards, seed, &state);

    printf("\n*********** Testing Adventurer Card Function ***********\n\n");

    // dependencies: numPlayers, number of treasure cards in deck

    // randomize the number of treasure cards in deck for each player, between 0 and 10
    for (i = 0; i < numPlayers; i++)
    {
        int numTreasures = rand() % 11;
        state.deckCount[i] = 0;
        for (j = 0; j < numTreasures; j++)
        {
            state.deck[i][j] = gold;
            state.deckCount[i]++;    
        }
        for (j = numTreasures; j < 10; j++)
        {
            state.deck[i][j] = estate;
            state.deckCount[i]++;
        }
    }

    // reset hand and then draw from new deck into hand for player 0
    state.handCount[0] = 0;
    for (k = 0; k < 5; k++)
    {
        drawCard(0, &state);
    }

    // print the hand and deck for each player
    for (int aa = 0; aa < numPlayers; aa++)
    {
        printf("Deck for player %d is:\n", aa);
        for (int bb = 0; bb < state.deckCount[aa]; bb++)
        {
            printf("%d ", state.deck[aa][bb]);
        }
        printf("\n\nHand for player %d is:\n", aa);
        for (int cc = 0; cc < state.handCount[aa]; cc++)
        {
            printf("%d ", state.hand[aa][cc]);
        }
        printf("\n\nDeck count for player %d is: %d\n", aa, state.deckCount[aa]);
        printf("Hand count for player %d is: %d\n", aa, state.handCount[aa]);
        printf("\n\n");
    }

    // get number of total cards in hand before play
    for (l = 0; l < numPlayers; l++)
    {
        numHandPre[l] = state.handCount[l];
    }

    // get number of treasure cards in hand before play
    for (m = 0; m < numPlayers; m++) 
    {
        for (n = 0; n < state.handCount[m]; n++)
        {
            if (state.hand[m][n] == copper || state.hand[m][n] == silver || state.hand[m][n] == gold)
            {
                numTreasurePre[m]++;
            }
        } 
    }

    // print the number of total cards and treasure cards in each player's hand
    for (int dd = 0; dd < numPlayers; dd++)
    {
        printf("numHandPre for player %d is: %d\n", dd, numHandPre[dd]);
        printf("numTreasurePre for player %d is: %d\n\n", dd, numTreasurePre[dd]);
    }

    // play the Adventurer card for all players
    for (o = 0; o < numPlayers; o++) 
    {
        playAdventurer(&state, o);
    }

    // get number of total cards in hand before play
    for (p = 0; p < numPlayers; p++)
    {
        numHandPost[p] = state.handCount[p];
    }

    // get number of treasure cards in hand after play
    for (q = 0; q < numPlayers; q++) 
    {
        for (r = 0; r < state.handCount[q]; r++)
        {
            if (state.hand[q][r] == copper || state.hand[q][r] == silver || state.hand[q][r] == gold)
            {
                numTreasurePost[q]++;
            }
        } 
    }

    // print the number of total cards and treasure cards in each player's hand
    for (int ee = 0; ee < numPlayers; ee++)
    {
        printf("numHandPost for player %d is: %d\n", ee, numHandPost[ee]);
        printf("numTreasurePost for player %d is: %d\n\n", ee, numTreasurePost[ee]);
    }

    // after play, hand should have increased by 2 cards overall for both players
    printf("Test 1: +2 cards in hand for each player\n");
    for (s = 0; s < numPlayers; s++)
    {
        printf("Expected player %d hand count: %d, Actual player %d hand count: %d\n", s, numHandPre[s] + 2, s, numHandPost[s]);
        if (numHandPost[s] != numHandPre[s] + 2)
            flag++;
    }

    if (flag > 0)
    {
        printf("Test 1: FAIL\n\n");
        fails++;
    }
    else
        printf("Test 1: PASS\n\n");    

    // after play, hand should have +2 treasure cards
    printf("Test 2: +2 treasure cards in hand for each player\n");
    for (t = 0; t < numPlayers; t++)
    {
        printf("Expected player %d treasure count: %d, Actual player %d treasure count: %d\n", t, numTreasurePre[t] + 2, t, numTreasurePost[t]);
        if (numTreasurePost[t] != numTreasurePre[t] + 2)
            flag++;
    }

    if (flag > 0)
    {
        printf("Test 2: FAIL\n\n");
        fails++;
    }
    else
        printf("Test 2: PASS\n\n");

    // // after play, anything before treasure cards should be in discard pile
    // printf("Test 3: All cards in deck before treasure cards now in discard pile\n");

    // // loop through to check what should be discarded for each player
    // for (y = 0; y < numPlayers; y++)
    // {
    //     int deckPos = prevState.deckCount[y] - 1;
    //     int drawnTreasure = 0;
    //     int index = 0;
    //     int expectedDiscards[5];

    //     while (drawnTreasure < 2 && deckPos > 0)
    //     {
    //         int card = prevState.deck[y][deckPos];
    //         if (card == copper || card == silver || card == gold)
    //         {
    //             drawnTreasure++;
    //         }
    //         else
    //         {
    //             expectedDiscards[index] = card;
    //             index++;
    //         }

    //         deckPos--;
    //     }
    //     for (int z = 0; z < index; z++)
    //     {
    //         if (expectedDiscards[z] != state.discard[y][z])
    //         {
    //             flag++;
    //         }
    //     }
    // }

    // if (flag == 0)
    //     printf("Test 3: PASS\n\n");
    // else
    // {
    //     printf("Test 3: FAIL\n\n");
    //     fails++;
    // }

    // if (fails == 0)
    //     printf("Adventurer Card Function: All Tests Passed!\n\n");
    // else
    //     printf("Adventurer Card Function: Failed %d Tests\n\n", fails);

    // return 0;
}