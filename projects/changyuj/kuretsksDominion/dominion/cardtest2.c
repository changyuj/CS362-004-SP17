#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dominion.h"
#include "rngs.h"
#include "interface.h"

/*	This unit test is designed to test the Smithy card effect.
 *
 *	Card Effect: +3 Cards
 *
 *	Desired Pre-condition: 
 *		-- struct gameState game which holds basic game information
 *		See dominion.h for full description of struct.
 *
 *		-- Smithy card is in player's hand to play
 *
 *	Desired Post-condition:
 *		-- Player gains additional 3 new cards in hand
 *		-- Player discards Smithy card
 *		-- Net number of cards: 2 
 */

int main(int argc, char **argv){
	printf("\n\n####################################### TESTING SMITHY CARD... ############################################################## \n\n");

	//Variables
	struct gameState gameBefore, gameAfter;
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy};
	int randNum, result, error = 0;
	randNum = rand()%123;

	//Initializing Game
	result = initializeGame(2, k, randNum, &gameBefore);
	if(result != 0){
		printf("Fail:\tInitializing game returned non-zero value.\n\n");
		exit(1);
	}
	result = initializeGame(2, k, randNum, &gameAfter);
	
	// Setting random card in hand to smithy
	// Init Games will have 7 copper and 3 estates
	// Before and After will have the same hands (have not played Smithy)
	randNum = rand()%5;
	gameBefore.hand[0][randNum] = k[9];
	gameAfter.hand[0][randNum] = k[9];
	
	//Playing Smithy
	result = playSmithy(&gameAfter, randNum);
	if(result != 0){
		printf("Fail:\tPlaying Smithy should return value of zero.\n\n");
		error = 1;
	}		
	//There should be one playedCard
	printf("Testing Played Cards...\n\n");
	if(gameAfter.playedCardCount != 1){ 
		printf("\tFail:\tThere should one played card.\n\n");
		error = 1; 
	//The is played card should be a Smithy
	}else if(gameAfter.playedCards[0] != smithy){
		printf("\tFail:\tPlayed card should be a Smithy.\n\n");
		error = 1;
	}else{
		printf("\tPass.\n\n");
	}

	//The hand should gain a net of 2 cards (+3 cards, - 1 Smithy)
	printf("Testing Hand Counts...\n\n");
	if(gameAfter.handCount[0] != (gameBefore.handCount[0] + 2)){
		printf("\tFail:\tHand count should net 2 cards (+3 cards, -1 Smithy).\n\n");
		error = 1;
	} else{
		printf("\tPass.\n\n");
	}
	//The number of actions should be decremented
	printf("Testing Number of Actions...\n\n");
	if(gameAfter.numActions != (gameBefore.numActions - 1)){
		printf("\tFail:\tNumber of actions should have decreased by 1.\n\n");
		error = 1;
	} else{
		printf("\tPass.\n\n");
	}
	if(!error){
		printf("SMITHY TESTS PASSED.\n\n");
	}

	printf("\n\n####################################### END SMITHY TESTS ############################################################## \n\n");
	return 0;
}
