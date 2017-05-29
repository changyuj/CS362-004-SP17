/******************************************************
 * Yu Ju Chang
 * randomtestcard2.c
 * Assignment 4
 *
 * Salvager random test
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
 
 int checkSalvager(int thisPlayer, int choice1, struct gameState *testG, int handPos)
 {
	struct gameState G2;
	memcpy(&G2, testG, sizeof(struct gameState));
	int initial_coins = 0, test_num = 0;
	
	updateCoins(thisPlayer, testG, 0);
	initial_coins = testG->coins;
	
	playSalvager(&G2, choice1, handPos);
	
	updateCoins(thisPlayer, &G2, 0);
	
#if (NOISY_TEST == 1)
    printf("Testing player %d buys...should have 1 extra buy\n", thisPlayer+1);
	printf("\nTotal buy: %d\tExpected: %d\n",G2.numBuys, testG->numBuys+1);
#endif
	test_num += assertEqual(testG->numBuys+1, G2.numBuys);

#if (NOISY_TEST == 1)
	printf("Trashed card cost: %d \n", getCost(choice1));
#endif
	
#if (NOISY_TEST == 1)
    printf("Testing player %d coins... coins should increase by %d \n", thisPlayer+1, getCost(choice1));
	printf("\nCoins: %d\tExpected: %d\n",G2.coins, initial_coins+getCost(choice1));
#endif
	test_num += assertEqual(G2.coins, initial_coins+getCost(choice1));
	
	return test_num;
 }
 int main()
 {
	int i, n, p, q, r, x, z, random, choice;
	int failTest = 0, totalFailed = 0, counter = 0;
	int k[10] = {adventurer, council_room, salvager, gardens, mine, remodel, smithy, village, baron, great_hall};
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
			
			//randomly insert Salvager in hand
			int y = floor(Random() * HAND_SIZE);
			G.hand[n][y] = salvager;
			
			//set discard count with random size
			G.discardCount[n] = floor(Random() * (DECK_SIZE - 50));
			
			//fill discard with random card
			for(q = 0; q < G.discardCount[n]; q++)
			{
				random = floor(Random() * 28);
				G.discard[n][q] = random;
			}
			
			//set number of buys with random num
			G.numBuys = floor(Random() * 5);
			
			//select a random card from hand
			random = floor(Random() * G.handCount[n]);
			choice = G.hand[n][random];

#if (NOISY_TEST == 1)
            printf("\nTest Number %d\tplayer: %d\tdeckCount: %d\thandCount: %d\tdiscardCount: %d\n\n",i+1, n+1, G.deckCount[n],G.handCount[n],G.discardCount[n]);
			printf("\nTrashed card cost %d coins\n",getCost(handCard(choice, &G)));
#endif		
			failTest = checkSalvager(n, choice, &G, y);
			counter+=2;
			totalFailed += failTest;
		}
#if (NOISY_TEST == 1)		
		printf("------------------ Test number %d complete with %d failed tests --------------------\n", i+1, failTest);
#endif			
	}
	printf("------------------ %d runs with total %d tests completed with %d failed tests --------------------\n", TEST_SIZE, counter, totalFailed);
	
	return 0;
 }