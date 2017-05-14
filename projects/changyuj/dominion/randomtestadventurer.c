/******************************************************
 * Yu Ju Chang
 * randomtestadventurer.c
 * Assignment 4
 *
 * Adventurer random test
 *****************************************************/
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rand_test_helper.h"
#include "rngs.h"
 
// set NOISY_TEST to 0 to remove printfs from output
// set NOISY_TEST to 1 to display printfs in output
#define NOISY_TEST 1
#define TEST_SIZE 20
#define DECK_SIZE 100
#define HAND_SIZE 27
 
 int checkAdventure(int thisPlayer, struct gameState *testG)
 {
	struct gameState G2;
	memcpy(&G2, testG, sizeof(struct gameState));
	
	int q, r, initial_copper, initial_silver, initial_gold, initial_hand;
	int post_copper, post_silver, post_gold, preTreasureCard = 0, postTreasureCard = 0;
		int test_num = 0;
				
			
	initial_hand = testG->handCount[thisPlayer];

	//initial treasures
	initial_copper = fullDeckCount(thisPlayer, copper, testG);
	initial_silver = fullDeckCount(thisPlayer, silver, testG);
	initial_gold = fullDeckCount(thisPlayer, gold, testG);

	for (q = 0; q < testG->handCount[thisPlayer]; q++)
	{
		if (testG->hand[thisPlayer][q] == copper) { preTreasureCard = preTreasureCard + 1; };
		if (testG->hand[thisPlayer][q] == silver) { preTreasureCard = preTreasureCard + 1; };
		if (testG->hand[thisPlayer][q] == gold) { preTreasureCard = preTreasureCard + 1; };
	}
			
	playAdventurer(&G2);
	

	//post tresures
	post_copper = fullDeckCount(thisPlayer, copper, &G2);
	post_silver = fullDeckCount(thisPlayer, silver, &G2);
	post_gold = fullDeckCount(thisPlayer, gold, &G2);
			
	for (r = 0; r < G2.deckCount[thisPlayer]; r++)
	{
		if (G2.hand[thisPlayer][r] == copper) { postTreasureCard = postTreasureCard + 1; };
		if (G2.hand[thisPlayer][r] == silver) { postTreasureCard = postTreasureCard + 1; };
		if (G2.hand[thisPlayer][r] == gold) { postTreasureCard = postTreasureCard + 1; };
	}
	
	
#if (NOISY_TEST == 1)
    printf("Testing player %d hand...should have 2 extra card in hand\n", thisPlayer+1);
#endif
	test_num += assertEqual(initial_hand+2, G2.handCount[thisPlayer]);
			
#if (NOISY_TEST == 1)
    printf("Testing player %d total copper card does not change\n", thisPlayer+1);
#endif			
	test_num += assertEqual(initial_copper, post_copper);
			
#if (NOISY_TEST == 1)
    printf("Testing player %d total silver card does not change\n", thisPlayer+1);
#endif			
	test_num += assertEqual(initial_silver, post_silver);
			
#if (NOISY_TEST == 1)
    printf("Testing player %d total gold card does not change\n", thisPlayer+1);
#endif			
	test_num += assertEqual(initial_gold, post_gold);			
			
#if (NOISY_TEST == 1)
    printf("Testing player %d hand increased two treasure cards\n", thisPlayer+1);
	printf("hand treasure card count = %d, expected = %d\n", postTreasureCard, preTreasureCard + 2);
#endif	
	test_num += assertTreasure(preTreasureCard, postTreasureCard);

	return test_num;
 }
 int main()
 {
	int i, n, p, q, r, x, z, random;
	int failTest = 0, totalFailed = 0, counter = 0;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
    int seed = 1000;
	
	// Initialize random stream
    SelectStream(2);
    PutSeed(3);
	
	srand(time(NULL));
	struct gameState G;
	
	printf ("Random Testing Adventurer.\n");

	printf ("RANDOM TESTS.\n");


	for(i = 0; i < TEST_SIZE; i++)
	{	

		//randomized chao in hand
		for (r = 0; r < sizeof(struct gameState); r++) 
		{
			((char*)&G)[r] = floor(Random() * 256);
		}
		
		//random num of player
		p = rand() % 4 + 1;
		
		//clear gamestate
		memset((char*)&G, 0, sizeof(struct gameState));
		
		//initialize game state
		initializeGame(p, k, seed, &G);
		//set number of players
		G.numPlayers = p;
		
		
		//go through all player
		for(n = 0; n < p; n++)
		{
			//select player
			G.whoseTurn = n;
			
			//set deck count with random size
			G.deckCount[n] = floor(Random() * DECK_SIZE);;
			memset(G.deck[n], 0, sizeof(int) * G.deckCount[n]);
			
			//fill deck with random cards
			for(z = 0; z < G.deckCount[n]; z++)
			{
				random = floor(Random() * 28);
				G.deck[n][z] = random;
			}
			
			//set hand count with random size
			G.handCount[n] = floor(Random() * HAND_SIZE);;
			memset(G.hand[n], 0, sizeof(int) * G.handCount[n]);

			//fill hand with random cards
			for(x = 0; x < G.handCount[n]; x++)
			{
				random = floor(Random() *28);
				G.hand[n][x] = random;
			}
			
			//randomly insert adventurer in hand
			int y = floor(Random() * HAND_SIZE);
			G.hand[n][y] = adventurer;
			
			//set discard count with random size
			G.discardCount[n] = floor(Random() * (DECK_SIZE - 50));
			
			//fill discard with random card
			for(q = 0; q < G.discardCount[n]; q++)
			{
				random = floor(Random() * 28);
				G.discard[n][q] = random;
			}
#if (NOISY_TEST == 1)
            printf("\nTest Number %d\tplayer: %d\tdeckCount: %d\thandCount: %d\tdiscardCount: %d\n\n",i+1, n+1, G.deckCount[n],G.handCount[n],G.discardCount[n]);
#endif		
			failTest = checkAdventure(n, &G);
			counter+=5;
			totalFailed += failTest;
		}
#if (NOISY_TEST == 1)		
		printf("------------------ Test number %d complete with %d failed tests --------------------\n", i+1, failTest);
#endif			
	}
	printf("------------------ %d runs with total %d tests completed with %d failed tests --------------------\n", TEST_SIZE, counter, totalFailed);
	
	return 0;
 }