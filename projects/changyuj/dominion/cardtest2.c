/* Assignment 3
 * cardtest2.c
 * Yu Ju Chang
 *
 * Include the following lines in your makefile:
 *
 * cardtest2: cardtest2.c dominion.o rngs.o
 *      gcc -o cardtest2 -g  cardtest2.c dominion.o rngs.o $(CFLAGS)
 */
/* business rules for adventurer:
 * 1. Current player should add 2 cards to hand
 *		a) player hand should have increased 2 treasure card
 * 2. Current player deck pile should have 2 less cards
 *      a) player deck should have 2 less treasure card
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

#define TESTCARD "Adventurer"

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
    int shuffledCards = 0;

    int i, j;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState G, testG;
	
	int preTreasureCard = 0, postTreasureCard = 0, preDeckTreasure = 0, postDeckTreasure = 0;
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
	
	// ----------- TEST 1: player 1 get +2 treasure cards --------------
	printf("TEST 1: Current player should add 2 cards\n");
	
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	//treasure cards in hand before adventure card
	for (i = 0; i < testG.handCount[thisPlayer]; i++)
    {
      if (testG.hand[thisPlayer][i] == copper) { preTreasureCard = preTreasureCard + 1; };
      if (testG.hand[thisPlayer][i] == silver) { preTreasureCard = preTreasureCard + 1; };
      if (testG.hand[thisPlayer][i] == gold) { preTreasureCard = preTreasureCard + 1; };
    }
	
	//treasure cards in deck before adventure card
	for (i = 0; i < testG.deckCount[thisPlayer]; i++)
    {
      if (testG.deck[thisPlayer][i] == copper) { preDeckTreasure = preDeckTreasure + 1; };
      if (testG.deck[thisPlayer][i] == silver) { preDeckTreasure = preDeckTreasure + 1; };
      if (testG.deck[thisPlayer][i] == gold) { preDeckTreasure = preDeckTreasure + 1; };
    }
	cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);
	
	
	newCards = 2;
	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
	assertEqual(testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded, 1);
	
	printf("TEST 1a: Current player hand should have increased 2 treasure cards\n");
	
	//treasure cards in hand after adventure card
	for (i = 0; i < testG.handCount[thisPlayer]; i++)
    {
      if (testG.hand[thisPlayer][i] == copper) { postTreasureCard = postTreasureCard + 1; };
      if (testG.hand[thisPlayer][i] == silver) { postTreasureCard = postTreasureCard + 1; };
      if (testG.hand[thisPlayer][i] == gold) { postTreasureCard = postTreasureCard + 1; };
    }
	
	//treasure cards in deck after adventure card
	for (i = 0; i < testG.deckCount[thisPlayer]; i++)
    {
      if (testG.deck[thisPlayer][i] == copper) { postDeckTreasure = postDeckTreasure + 1; };
      if (testG.deck[thisPlayer][i] == silver) { postDeckTreasure = postDeckTreasure + 1; };
      if (testG.deck[thisPlayer][i] == gold) { postDeckTreasure = postDeckTreasure + 1; };
    }
	
	printf("treasure card count = %d, expected = %d\n", postTreasureCard, preTreasureCard + newCards);
	assertEqual(postTreasureCard, preTreasureCard +newCards, 1);
		
	// ----------- TEST 2: player deck pile -2 treasure cards --------------
	printf("TEST 2: Current player deck pile should have 2 less cards\n");
	
	printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);
	assertEqual(testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards, 2);
	
	printf("TEST 2a: Current player deck should have 2 less treasure cards\n");
	printf("treasure card count = %d, expected = %d\n", postDeckTreasure, preDeckTreasure + newCards);
	assertEqual(postDeckTreasure, preDeckTreasure +newCards, 2);
	
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