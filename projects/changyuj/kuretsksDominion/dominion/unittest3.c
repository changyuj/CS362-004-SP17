#include <stdlib.h>
#include <stdio.h>
#include "dominion.h"
#include "rngs.h"
#include "interface.h"

/*	This unit test is designed to test scoreFor() in dominion.c
 *
 *	Function Effect: This function will return a player's score at 
 *	any given time. It returns an int with the player's score.
 *
 *	Desired Pre-condition: 
 *		-- struct gameState: this holds pertinent game information
 *			See dominion.h for full detail
 *		-- Test Case 1:
 *			- 3 Victory Cards in entire deck (1 Estate in hand, 1 Duchy discard, 1 Province deck)
 *		-- Test Case 2:
 *			- No Victory Point cards
 *		-- Test Case 3:
 *			- 1 Estate Card in hand, 1 Curse Card in discard, 1 Curse Card in deck
 *
 *	Desired Post-condition:
 *		-- Test Case 1:
 *			- Total score of 10 from hand, discard, and deck
 *		-- Test Case 2:
 *			- Total score of zero from hand, discard, and deck
 *		-- Test Case 3:
 *			- Total score of -1 
 */ 
void clearVictoryCards(struct gameState *game, int k[]);

int main(int argv, char **argc){
	printf("\n\n####################################### TESTING SCOREFOR() FUNCTION ############################################################## \n\n");

	//Variables
	struct gameState game;
	int result, randNum, scoreExpected, scoreResult, error = 0;
	int k[10] = {smithy, mine, adventurer, feast, sea_hag,
		village, remodel, minion, ambassador, embargo};
	
	//Initializing Game
	randNum = rand()%1198 + 1;
	result = initializeGame(2, k, randNum, &game);
	if(result != 0){
		printf("Fail:\tGame initialization should return zero.\n\n");
		exit(1);
	} 

	//Test Case 1
	printf("Testing Case 1 (1 Estate, 1 Duchy, 1 Province)...\n\n");
	clearVictoryCards(&game, k);
	game.hand[0][4] = estate;
	game.discard[0][0] = duchy;
	game.discardCount[0] = 1;
	game.deck[0][2] = province;
	scoreExpected = 10;
	scoreResult = scoreFor(0, &game);
	if(scoreExpected != scoreResult){
		printf("\tFail:\tResult does not equal expected score of %d\n\n\n", scoreExpected);
		error = 1;
	} else{
		printf("\tPass\n\n");
	}
	//Test Case 2
	printf("Testing Case 2 (No Victory Point cards)...\n\n");
	clearVictoryCards(&game, k);
	scoreExpected = 0;
	scoreResult = scoreFor(0, &game);
	if(scoreExpected != scoreResult){
		printf("\tFail:\tResult does not equal expected score of %d.\n\n\n", scoreExpected);
		error = 1;
	}else{
		printf("\tPass\n\n");
	}
	
	//Test Case 3
	printf("Testing Case 3 (1 Estate hand, 1 Curse discard, 1 Curse deck)...\n\n");
	clearVictoryCards(&game, k);
	game.hand[0][3] = estate;
	game.discard[0][0] = curse;
	game.discardCount[0] = 1;
	game.deck[0][2] = curse;
	scoreExpected = -1;
	scoreResult = scoreFor(0, &game);
	if(scoreExpected != scoreResult){
		printf("\tFail:\tResult does not equal expected score of %d.\n\n\n", scoreExpected);
		error = 1;
	}else{
		printf("\tPass.\n\n");
	}	
	if(!error){
		printf("SCOREFOR TESTS PASSED.\n\n");
	}
	printf("\n\n####################################### END SCOREFOR FUNCTION TESTS ############################################################## \n\n");
	return 0;
}

void clearVictoryCards(struct gameState *game, int k[]){
	int i;
	game->deckCount[0] = 5;
	game->handCount[0] = 5;
	for(i = 0; i < game->deckCount[0]; i++){
		game->deck[0][i] = k[i];
	}
	for(i = 0; i < game->handCount[0]; i++){
		game->hand[0][i] = k[i];
	}	
	game->discardCount[0] = 0;
} 
