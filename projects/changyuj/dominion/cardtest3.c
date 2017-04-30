/* Assignment 3
 * cardtest3.c
 * Yu Ju Chang
 *
 * Include the following lines in your makefile:
 *
 * cardtest3: cardtest3.c dominion.o rngs.o
 *      gcc -o cardtest3 -g  cardtest3.c dominion.o rngs.o $(CFLAGS)
 */
/* business rules for village:
 * 1. Current player should add 1 cards to hand
 * 2. Current player have 2 actions
 * 3. No state change should occur for other players.
 * 4. No state change should occur to the victory card piles and kingdom card piles.
 */
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "Village"

void assertEqual(int before, int after, int testNum)
{
	if(before == after)
	{
		printf("\n----------------- Test #%d: Passed -----------------\n", testNum);
	}
	else{
		printf("\n----------------- Test #%d: Failed -----------------\n", testNum);
	}
}

int main()
{
	int newCards = 0;
    int discarded = 1;
	int actions = 0;
	
    int j;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState G, testG;
	
	//Kingdom cards
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};

	//supply cards of kindom and victory cards pile
	int supplyPile[16] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, 
						council_room, estate, duchy, province, copper, silver, gold};
						
	char* supplyString[16] = {"adventurer", "embargo", "village", "minion", "mine", "cutpurse", "sea_hag", "tribute", "smithy", 
						"council_room", "estate", "duchy", "province", "copper", "silver", "gold"};
						
	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
	
	// ----------- TEST 1: player 1 get +1 cards --------------
	printf("TEST 1: player 1 receives +1 cards\n");
	
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	cardEffect(village, choice1, choice2, choice3, &testG, handpos, &bonus);
	
	newCards = 1;
	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
	assertEqual(testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded, 1);
	
	// ----------- TEST 2: Current player have +2 actions --------------
	printf("TEST 2: player 1 have +2 actions\n");
	
	actions += 2;
	
	printf("action count = %d, expected = %d\n", testG.numActions, G.numActions + actions);
	assertEqual(testG.numActions, G.numActions + actions, 2);
	
	// ----------- TEST 3: No state change should occur for other players --------------	
	printf("TEST 3: No state change should occur for other players\n");
	printf("player 2 hand count = %d, expected = %d\n", testG.handCount[thisPlayer+1], G.handCount[thisPlayer+1]);
	assertEqual(testG.handCount[thisPlayer+1], G.handCount[thisPlayer+1], 3);
	printf("player 2 deck count = %d, expected = %d\n", testG.deckCount[thisPlayer+1], G.deckCount[thisPlayer+1]);
	assertEqual(testG.deckCount[thisPlayer+1], G.deckCount[thisPlayer+1], 3);
	
	// ----------- TEST 4: No state change should occur to the victory card piles and kingdom card piles --------------	
	printf("TEST 4: No state change should occur to victory card and kingdome card piles\n");
	for(j = 0; j < 16; j++)
	{
		printf("Supply count for %s = %d, expected %d\n", supplyString[j], testG.supplyCount[supplyPile[j]], G.supplyCount[supplyPile[j]]);
		assertEqual(testG.supplyCount[supplyPile[j]], G.supplyCount[supplyPile[j]], 4);
		printf("----------------------------------------\n");
	}
	
	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);
	return 0;
}