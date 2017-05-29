#include <stdlib.h>
#include <stdio.h>
#include "dominion.h"
#include "rngs.h"
#include "interface.h"

/*	Testing Function: int isGameOver(struct gameState *state)
 *	
 *	Source: dominion.c
 *
 *	Function Effect: returns int of value 1 if game is over, returns 0 if game will
 *		continue
 *
 *	Desired Pre-Conditions:
 *		-- struct gameState: this holds pertinent game information
 *				See dominion.h for further detail
 *
 *	Desired Post-conditions:
 *		-- Returns 1 if game over condition is met
 *		-- Returns 0 if game should continue
 *
 * 	Test Case 1:
 * 		-- Pre-Condition:
 * 			-- Supply has no more Provinces 
 * 		-- Post-Condition:
 * 			-- Returns 1
 *
 * 	Test Case 2:
 * 		-- Pre-condition:
 * 			-- Supply has 3 empty piles
 * 		-- Post-Condition:
 * 			-- Returns 1
 *
 * 	Test Case 3:
 * 		-- Pre-condition:
 * 			-- Supply has no empty piles
 * 		-- Post-Condition:
 * 			-- Returns 0
 */ 

int main(int argv, char **argc){
	printf("\n\n####################################### TESTING isGameOver() FUNCTION ############################################################## \n\n");
	
	//Variables
	struct gameState game;
	int result, randNum, expectedOver, resultedOver, error = 0;
	int k[10] = {adventurer, council_room, feast, gardens, mine,
		remodel, smithy, village, sea_hag, great_hall};
	
	//Initializing Game
	randNum = rand()%129+1;
	result = initializeGame(2, k, randNum, &game);
	if(result != 0){
		printf("Fail:\tGame initialization should return zero.\n\n");
		exit(1);
	}
	
	//Test Case 1 (No Provinces)
	printf("Test Case 1 (No Provinces)...\n\n");
	game.supplyCount[province] = 0;
	expectedOver = 1;
	resultedOver = isGameOver(&game);
	if(expectedOver != resultedOver){
		printf("\tFail:\tExpected game to be over with value of %d. Resulted with %d.\n\n", expectedOver, resultedOver);
		error = 1;
	} else{
		printf("\tPass.\n\n");
	}

	//Test Case 2 (3 Empty Supply Piles)
	printf("Test Case 2 (3 Empty Supply Piles)...\n\n");
	
	//Resetting Province count to not zero and 3 kingdom cards to zero
	game.supplyCount[province] = 5;
	game.supplyCount[smithy] = 0;
	game.supplyCount[village] = 0;
	game.supplyCount[mine] = 0;
	expectedOver = 1;
	resultedOver = isGameOver(&game);
	if(expectedOver != resultedOver){
		printf("\tFail:\tExpected game to be over with value of %d. Resulted with %d.\n\n", expectedOver, resultedOver);
		error = 1;
	} else{
		printf("\tPass.\n\n");
	}
	
	//Test Case 3 (Supply has no empty piles and Provinces are not empty)
	printf("Test Case 3 (No empty supply and Provinces are not empty)...\n\n");
	game.supplyCount[province] = 5;
	game.supplyCount[smithy] = 1;
	game.supplyCount[village] = 1;
	game.supplyCount[mine] = 1;
	expectedOver = 0;
	resultedOver = isGameOver(&game);
	if(expectedOver != resultedOver){
	printf("\tFail:\tExpected game to continue with value of %d. Resulted with %d.\n\n", expectedOver, resultedOver);
	error = 1;
	} else{
		printf("\tPass.\n\n");
	}

	//Final Prints
	if(!error){
		printf("ISGAMEOVER() TESTS PASSED.\n\n");
	}
	printf("\n\n####################################### END isGameOver() FUNCTION TESTS ############################################################## \n\n");
	return 0;
}

