/* -----------------------------------------------------------------------
 * Assignment 3
 * unittest3.c
 * Yu Ju Chang
 *
 * Include the following lines in your makefile:
 *
 * unittest3: unittest3.c dominion.o rngs.o
 *      gcc -o unittest3 -g  unittest3.c dominion.o rngs.o $(CFLAGS)
 *
 *
 * function rules for whoseTurn():
 * 1. Should return who's turn correctly
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1
#define TESTFUNCTION "whoseTurn()"

int assertEqual(int value1, int value2)
{
	if(value1 == value2)
	{
		printf("\n----------------- Test: Passed -----------------\n");
	}
	else{
		printf("\n----------------- Test: Failed -----------------\n");
		return 1;
	}
	return 0;
}

int main() {
    int p;
    int numPlayer = 10;
	int fail = 0;

	
	struct gameState G;
	
    printf ("TESTING whoseTurn():\n");	
	
    for (p = 0; p < numPlayer; p++)
    {
#if (NOISY_TEST == 1)
        printf("Player %d's turn.\n", p+1);
#endif
		G.whoseTurn = p;
		printf("player %d  turn, expected = %d\n", whoseTurn(&G)+1, p+1);
		fail += assertEqual(whoseTurn(&G), p);
	}
	
	if(fail != 0)
	{
		printf("one of the player turn does not match.\n");
	}
	else 
	{
		printf("\n >>>>> SUCCESS: Testing complete  <<<<<\n\n");
	}
		
	return 0;
}