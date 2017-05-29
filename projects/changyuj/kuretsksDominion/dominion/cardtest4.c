#include <stdlib.h>
#include <stdio.h>
#include "dominion.h"
#include "rngs.h"
#include "interface.h"
/*	This unit test is designed to test Great Hall card effect.
 *
 *	Card Effect: +1 Card, +1 Action, 1 Victory Point
 *
 *	Desired Pre-condition: 
 *		-- struct gameState: this holds game information
 *			See dominion.h for more information
 *		-- Player has Great Hall in hand
 *		-- Player has 3 Victory points.
 *	Desired Post-condition:
 *		-- Player gains 1 card.
 *		-- Player gains 1 action.
 *		-- Player gains 1 Victory point for total of 4 VP. 
 *
 *  **NOTE: this unit test assumes function scoreFor() calculates
 *  score correctly with great_hall. 
 */

int main(int argc, char **argv){
	printf("\n\n####################################### TESTING GREAT HALL ############################################################## \n\n");

	//Variables
	struct gameState gameBefore, gameAfter;
	int randNum, result, scoreBefore, scoreAfter, error = 0;
	int k[10] = {adventurer, gardens, embargo, village, minion, mine,
		cutpurse, sea_hag, tribute, great_hall};

	//Initializing Game
	randNum = rand()%123;
	result = initializeGame(2, k, randNum, &gameBefore);
	if(result != 0){
		printf("Fail:\tInitialize game should return zero.\n\n");
		exit(1);
	}
	
	//Getting scoreBefore gaining great_hall
	scoreBefore = scoreFor(0, &gameBefore);

	//Setting sixth card in hand as great_hall 
	gameBefore.hand[0][5] = great_hall;
	gameBefore.handCount[0] = 6;

	//Shallow copy of gameBefore to gameAfter
	gameAfter = gameBefore;

	//Playing Great Hall
	result = cardEffect(great_hall, -1,-1,-1, &gameAfter, 5, 0);
	if(result != 0){
		printf("Fail:\tCard Effect should return zero.\n\n");
		error = 1;
	}
	//Actions
	printf("Testing Number of Actions...\n\n");
	if(gameAfter.numActions != (gameBefore.numActions + 1)){
		printf("\tFail:\tNumber of actions should have increased by 1.\n\n");
		error = 1;
	} else{
		printf("\tPass.\n\n");
	}
	//Hand Count
	printf("Testing Hand Count...\n\n");
	if(gameAfter.handCount[0] != gameBefore.handCount[0]){
		printf("\tFail:\tHand count should net zero cards (+1 card, -1 Great Hall).\n\n");
		error = 1;
	}
	else if(gameAfter.hand[0][gameAfter.handCount[0] - 1] == great_hall){
		printf("\tFail:\tGreat Hall should not be in hand after playing.\n\n");
		error = 1;
	} else{
		printf("\tPass.\n\n");
	}

	//Played Cards
	printf("Testing Played Cards...\n\n");
	if(gameAfter.playedCardCount != (gameBefore.playedCardCount + 1)){
		printf("\tFail:\tPlayed card count should have increased by 1 (Great Hall was played).\n\n");
		error = 1;
	}
	else if(gameAfter.playedCards[gameAfter.playedCardCount - 1] != great_hall){
		printf("\tFail:\tLast played card should be Great Hall.\n\n");
		error = 1;
	} else{
		printf("\tPass.\n\n");
	}

	//Victory Points
	printf("Testing Victory Points...\n\n");

	//Getting Score after having Great Hall
	scoreAfter = scoreFor(0, &gameAfter);
	if((scoreBefore + 1) != scoreAfter){
		printf("\tFail:\tGreat Hall did not add 1 Victory Point.\n\n");
		error = 1;
	} else{
		printf("\tPass.\n\n");
	}
	if(!error){
		printf("GREAT HALL TESTS PASSED.\n\n");
	}
	printf("\n\n####################################### END GREAT HALL TESTS ############################################################## \n\n");
	return 0;
} 
