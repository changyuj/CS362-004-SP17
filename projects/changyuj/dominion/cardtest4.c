/* Assignment 3
 * cardtest4.c
 * Yu Ju Chang
 *
 * Include the following lines in your makefile:
 *
 * cardtest4: cardtest4.c dominion.o rngs.o
 *      gcc -o cardtest4 -g  cardtest4.c dominion.o rngs.o $(CFLAGS)
 */
/* business rules for council_room:
 * 1. Current player should add 4 cards to hand
 * 2. Current player should add 1 buy
 * 3. Other player should add 1 card.
 * 4. No state change should occur to the victory card piles and kingdom card piles.
 */
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "Council Room"

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
	int buy = 0;
	
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
	
	// ----------- TEST 1: player 1 get +4 cards --------------
	printf("TEST 1: player 1 receives +4 cards\n");
	
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	cardEffect(council_room, choice1, choice2, choice3, &testG, handpos, &bonus);
	
	newCards = 4;
	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
	assertEqual(testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded, 1);
	
	// ----------- TEST 2: player 1 get +1 buy --------------
	printf("TEST 2: player 1 gets +1 buy\n");
	
	buy++;
	printf("buy count = %d, expected = %d\n", testG.numBuys, G.numBuys + buy);
	assertEqual(testG.numBuys, G.numBuys + buy, 2);
	
	// ----------- TEST 3: Other player should add 1 card --------------	
	printf("TEST 3: State change should occur for other players\n");
	printf("player 2 hand count = %d, expected = %d\n", testG.handCount[thisPlayer+1], G.handCount[thisPlayer+1] + 1);
	assertEqual(testG.handCount[thisPlayer+1], G.handCount[thisPlayer+1] + 1, 3);
	printf("player 2 deck count = %d, expected = %d\n", testG.deckCount[thisPlayer+1], G.deckCount[thisPlayer+1] - 1);
	assertEqual(testG.deckCount[thisPlayer+1], G.deckCount[thisPlayer+1] - 1, 3);
	
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