/* -----------------------------------------------------------------------
 * Assignment 3
 * unittest4.c
 * Yu Ju Chang
 *
 * Include the following lines in your makefile:
 *
 * unittest4: unittest4.c dominion.o rngs.o
 *      gcc -o unittest4 -g  unittest4.c dominion.o rngs.o $(CFLAGS)
 *
 *
 * function rules for getCost():
 * 1. Should return cost of the card correctly
 * 2. Return -1 if the card does not exist
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
#define TESTFUNCTION "getCost()"

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
    int i;
	int maxCards = 27;
	int fail = 0;

	int cards[27] = {curse, estate, duchy, province, copper, silver, gold, adventurer, council_room, feast, gardens, 
							mine, remodel, smithy, village, baron, great_hall, minion, steward, tribute, ambassador, cutpurse, 
							embargo, outpost, salvager, sea_hag, treasure_map};
	int cardCost[27] = {0, 2, 5, 8, 0, 3, 6, 6, 5, 4, 4, 5, 4, 4, 3, 4, 3, 5, 3, 5, 3, 4, 2, 5, 4, 4, 4};	
	
#if (NOISY_TEST == 1)
        printf("Test Card Cost with getCost():\n");
#endif
	
	for (i = 0; i < maxCards; i++)
    {	
		printf("Card %d cost %d, expected = %d\n", i+1, getCost(cards[i]), cardCost[i]);
		fail += assertEqual(getCost(cards[i]), cardCost[i]);
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