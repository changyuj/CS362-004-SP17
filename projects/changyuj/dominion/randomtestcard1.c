/******************************************************
 * Yu Ju Chang
 * randomtestcard1.c
 * Assignment 4
 *
 * smithy random test
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
 
 int checkSmithy(int thisPlayer, struct gameState *testG, int handPos)
 {
	struct gameState G2;
	memcpy(&G2, testG, sizeof(struct gameState));
	int initial_hand, initial_discard, test_num = 0;
	
	initial_hand = testG->handCount[thisPlayer];
	initial_discard = testG->discardCount[thisPlayer];
	playSmithy(&G2, handPos);

	
#if (NOISY_TEST == 1)
    printf("Testing player %d hand...should have 2 extra card in hand with smithy discarded\n", thisPlayer+1);
	printf("\nhand count: %d\tExpected: %d\n",G2.handCount[thisPlayer], initial_hand+2);
#endif
//should have added 3 new card and discarded 1 card so hand size should be 2 card more than original
	test_num += assertEqual(initial_hand+3-1, G2.handCount[thisPlayer]);
			
#if (NOISY_TEST == 1)
    printf("Testing player %d discard count... discard cound should increase by 1\n", thisPlayer+1);
	printf("\ndiscard count: %d\tExpected: %d\n",G2.discardCount[thisPlayer], initial_discard+1);
#endif
	test_num += assertEqual(initial_discard+1, G2.discardCount[thisPlayer]);
	
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
			
			//randomly insert smithy in hand
			int y = floor(Random() * HAND_SIZE);
			G.hand[n][y] = smithy;
			
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
			failTest = checkSmithy(n, &G, y);
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