#include <stdlib.h>
#include <stdio.h>
#include "dominion.h"
#include "rngs.h"

/*	This unit test is designed to test whoseTurn function in
 *	dominion.c.
 *
 *	Function effect: This function should return which player's
 *	turn it is
 *
 *	Desired Pre-condition: 
 *		-- struct gameState: this holds pertinent game information
 *			See dominion.h for full detail
 *	Desired Post-condition:
 *		-- Returns corresponding player number in accordance to
 *			correct turn
 */ 

int main(int argv, char **argc){
	printf("\n\n####################################### TESTING WHOSETURN FUNCTION ############################################################## \n\n");

	//Variables
	struct gameState game;
	int result, randNum, whoseTurnFunc, error = 0;

	//Initializing Game
	randNum = rand()%10;
	int k[10] = {1,2,3,4,5,6,7,8,9,0};
	result = initializeGame(2, k, randNum, &game);
	if(result != 0){
		printf("Fail:\tInitializing game should return zero.\n\n");
		exit(1);
	}

	//Calling WhoseTurn
	whoseTurnFunc = whoseTurn(&game);
	printf("Testing WhoseTurn Return Value...\n\n");
	if(game.whoseTurn != whoseTurnFunc){
		printf("\tFail:\twhoseTurn() function should return player 1 with a value of zero.\n\n");
		error = 1;
	} else{
		printf("\tPass.\n\n");
	}
	if(!error){
		printf("WHOSETURN TESTS PASSED.\n\n");
	}
	printf("\n\n####################################### END WHOSE TURN FUNCTION TESTS ############################################################## \n\n");
	return 0;
}
