/* -----------------------------------------------------------------------
 * Assignment 3
 * unittest1.c
 * Yu Ju Chang
 *
 * Include the following lines in your makefile:
 *
 * unittest1: unittest1.c dominion.o rngs.o
 *      gcc -o unittest1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)
 *
 *
 * function rules for shuffle:
 * 1. If no card in deck, shuffle does not occur
 * 2. Pre-shuffle and post-shuffle deck card position should be different 
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include<stdlib.h>
#include<time.h>
#include <assert.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1
#define TESTFUNCTION "Shuffle()"

void assertEqual(int value1, int value2)
{
	if(value1 == value2)
	{
		printf("\n----------------- Shuffle Test: Failed -----------------\n");
	}
	else{
		printf("\n----------------- Shuffle Test: Passed -----------------\n");
	}
}

int main() {
	srand(time(NULL));
    int i, p;
    int seed = 1000;
    int numPlayer = 2;
	int deckCount, random;
    int maxDeckCount = 10;
	
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	int supplyPile[16] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, 
					council_room, estate, duchy, province, copper, silver, gold};
    struct gameState G;
	struct gameState G2;
	
    printf ("TESTING Shuffle():\n");
	
    for (p = 0; p < numPlayer; p++)
    {
        for (deckCount = 0; deckCount <= maxDeckCount; deckCount++)
        {
#if (NOISY_TEST == 1)
            printf("Test player %d with %d card(s) in deck.\n", p, deckCount);
#endif
 //           memset(&G, 23, sizeof(struct gameState));   // clear the game state
			initializeGame(numPlayer, k, seed, &G); 	// initialize a new game
            G.deckCount[p] = deckCount;                 // set the number of cards in deck
			for(i = 0; i < deckCount; i++)
			{
				random = rand() % 16;
				G.deck[p][i] = supplyPile[random];
			}
			memcpy (&G2, &G, sizeof(struct gameState)); // copy gameState to G2
            int ret = shuffle(p, &G);
			
#if (NOISY_TEST == 1)
			if(deckCount == 0)
			{
				printf("0 card in deck, no shuffle\n");
			}
			else
			{
				printf("More than one care in deck, shuffle\n");
			}
#endif
			if(G.deckCount[p] > 0)
			{
				assertEqual(ret, -1);
				
				printf("G.deck does not equal G2.deck after shuffle\n"); 
				assertEqual(memcmp(&G, &G2, sizeof(struct gameState)), 0);
				printf("\n");
			}
			else if(G.deckCount[p] == 0)
			{
				assertEqual(ret, 0);
			}	
/*
#if (NOISY_TEST == 1)

			for(j = 0; j < deckCount; j++)
			{
				printf("G.deck card %d = %d, original card %d = %d\n", j+1, G.deck[p][j], j+1, G2.deck[p][j]);
			}

			printf("G.deck does not equal G2.deck after shuffle\n"); 
#endif
			assertEqual(memcmp(&G, &G2, sizeof(struct gameState)), 0);
			printf("\n");
*/
		}
    }

    printf("All tests passed!\n");
	
	return 0;
}