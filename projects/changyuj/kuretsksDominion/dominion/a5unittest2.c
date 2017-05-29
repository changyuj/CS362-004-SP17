/* -----------------------------------------------------------------------
 * Assignment 3
 * unittest2.c
 * Yu Ju Chang
 *
 * Include the following lines in your makefile:
 *
 * unittest2: unittest2.c dominion.o rngs.o
 *      gcc -o unittest2 -g  unittest2.c dominion.o rngs.o $(CFLAGS)
 *
 *
 * function rules for kingdomCards:
 * 1. kingdomCards should match assigned cards
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include<stdlib.h>
#include <assert.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1
#define TESTFUNCTION "kingdomCards()"

int assertEqual(int value1, int value2)
{
	if(value1 == value2)
	{
		printf("\n----------------- Card matching Test: Passed -----------------\n");
	}
	else{
		printf("\n----------------- Card matching Test: Failed -----------------\n");
		return 1;
	}
	return 0;
}

int main() {

    int i, j;
    int kingdomCardCount = 10;
	int fail = 0;
	
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	
    printf ("TESTING kingdomCards():\n");
	
	int *kingdomCardTest = kingdomCards(k[0], k[1], k[2], k[3], k[4], k[5], k[6], k[7], k[8], k[9]);
	
    for (i = 0; i < kingdomCardCount; i++)
    {

#if (NOISY_TEST == 1)
        printf("Compare card %d with kingdom card.\n", i+1);
#endif
		printf("card %d = %d, expected = %d\n", i+1, kingdomCardTest[i], k[i]);
		fail += assertEqual(kingdomCardTest[i], k[i]);
    }
	if(fail != 0)
	{
		printf("One of the card does not match.\n");
	}
#if (NOISY_TEST == 1)
        printf("Changed card # 7 in kingdom card.\n");
#endif
	kingdomCardTest = kingdomCards(k[0], k[1], k[2], k[3], k[4], k[5], k[8], k[7], k[8], k[9]);
	for(j = 0; j < kingdomCardCount; j++)
	{
		printf("card %d = %d, expected = %d\n", j+1, kingdomCardTest[j], k[j]);
		fail += assertEqual(kingdomCardTest[j], k[j]);
	}
	
	if(fail != 0)
	{
		printf("One of the card does not match.\n");
	}
	else 
	{
		printf("\n >>>>> SUCCESS: Testing complete  <<<<<\n\n");
	}
	return 0;
}