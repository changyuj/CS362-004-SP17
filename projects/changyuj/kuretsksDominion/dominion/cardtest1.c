#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dominion.h"
#include "rngs.h"
/*	This unit test is designed to test the Adventurer card
 *	implementation. 
 *
 *	Card Effect: Reveal cards from your deck until you reveal
 *	2 Treasure cards. Put those Treasure cards into your hand and
 *	discard the other revealed cards.
 *
 *	Desired Pre-condition: 
 *		-- 	struct gameState game which holds game information. 
 *		  	See dominion.h for full description of struct. 
 *	Desired Post-condition:
 *		--	Current player receives two treasure cards into 
 *			current hand if 2 treasure cards are available for draw.
 *		--  Current player receives one treasure card into 
 *		    current hand if 1 treasure card are available for draw. 
 *		--	Current player plays Adventurer and discards all other non-Treasure cards
 *		    which were drawn to find treasure card. 
 *
 */

int main(int argc, char **argv){
	printf("\n\n################################### TESTING ADVENTURER CARD... ############################################################## \n\n");

	//Variables
	struct gameState gameBefore, gameAfter;
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, 
		cutpurse, sea_hag, tribute, smithy};
	int randNum, result, error = 0;	

	//Initialzing game with preset values
	randNum = rand()%123 + 1;
	result = initializeGame(2, k, randNum, &gameBefore);

	//Game initialization on successful completion should return zero
	if(result != 0){
		printf("Fail:\tInitializing game returned non-zero value.\n\n");
		exit(1); //Exiting with error since game initialization is required for further tests
	}
	result = initializeGame(2, k, randNum, &gameAfter);

	/* Note: Initialized hands have 3 estates and 7 copper
	 * Setting a random card in player 1's hand as Adventurer 
	 * Before and After hands will be the same (adventurer not played yet)
	 */
	randNum = rand()%5;
	gameBefore.hand[0][randNum] = adventurer;
	gameAfter.hand[0][randNum] = adventurer;

	//Playing Adventurer card
	result = playAdventurer(&gameAfter);

	//playAdventurer should return zero 
	if(result != 0){
		printf("Fail:\tplaying Adventurer card returned non-zero value.\n\n");
		error = 1;
	}

	/*  Hand Counts
 	 * 	
	 *  Player's hand should have yielded 2 additional cards and discarded Adventurer,
	 *  so net total of 6 cards in hand.
	 */
	printf("Testing Hand Counts...\n\n");
	if(gameAfter.handCount[0] > 6){
		printf("\tFail:\tAdventurer card put too many cards into player's hand.\n\n");
		error = 1;
	} else{
		printf("\tPass.\n\n");
	}

	//Played Cards (looking for Adventurer)
	printf("Testing Played Cards...\n\n");
	if(gameAfter.playedCardCount != (gameBefore.playedCardCount + 1)){
		printf("\tFail:\tThere should be one card played (the Adventurer).\n\n");
		error = 1;
	} 
	else if(gameAfter.playedCards[gameAfter.playedCardCount - 1] != adventurer){
		printf("\tFail:\tAdventurer should be last card in playedCards.\n\n");
		error = 1;
	}
	else{
		printf("\tPass.\n\n");
	}

	// Custom Decks to test Adventurer
	printf("################### Custom Deck Testing... ###################\n\n");
	// Custom Deck 1 -- 3 treasures in deck (and no discard)
	printf("Testing deck with 3 treasure cards...\n\n");
	result = initializeGame(2, k, 5, &gameBefore);
	result = initializeGame(2, k, 5, &gameAfter);

	gameBefore.deck[0][0] = estate;
	gameBefore.deck[0][1] = estate;
	gameBefore.deck[0][2] = copper;
	gameBefore.deck[0][3] = copper;
	gameBefore.deck[0][4] = copper;

	gameBefore.hand[0][0] = adventurer;
	gameBefore.discardCount[0] = 0;	
	gameBefore.deckCount[0] = 5;
	gameBefore.handCount[0] = 1;
	gameAfter = gameBefore;
	
	result = playAdventurer(&gameAfter);
	// Discards
	printf("\tTesting Discards...\n\n");
	if(gameAfter.discardCount[0] != (gameBefore.discardCount[0] + 2)){
		printf("\t\tFail:\tShould have discarded 2 cards.\n\n");
		error = 1;
	} 
	else if(gameAfter.discard[0][0] != estate || gameAfter.discard[0][1] != estate){
		printf("\t\tFail:\tDiscards should be Estate cards.\n\n");
		error = 1;
	}
	else{
		printf("\t\tPass.\n\n");
	}
		
	// Hand Cards
	printf("\tTesting Hand Cards...\n\n");
	if(gameAfter.handCount[0] != (gameBefore.handCount[0] + 1)){
		printf("\t\tFail:\tHand count should be net gain of 1 (+2 Treasure, -1 Adventurer).\n\n");
		error = 1;
	}
	else if(gameAfter.hand[0][0] != copper || gameAfter.hand[0][1] != copper){
		printf("\t\tFail:\tHand should have gained 2 copper cards.\n\n");
		error = 1;
	}
	else{
		printf("\t\tPass.\n\n");
	}

	//Checking Remaining Deck Cards
	printf("\tTesting Remaining Deck Cards...\n\n");
	if(gameAfter.deckCount[0] != (gameBefore.deckCount[0] - 4)){
		printf("\t\tFail:\tRemaining deck should have 4 less cards.\n\n");
		error = 1;
	}
	else if(gameAfter.deck[0][0] != copper){
		printf("\t\tFail\t:Remaining deck card should be copper.\n\n");
		error = 1;
	}
	else{
		printf("\t\tPass.\n\n");
	}

	// Custom Deck 2 -- No treasures in deck (and no discard)
	printf("Testing deck with no treasure cards...\n\n");
	result = initializeGame(2, k, 5, &gameBefore);
	result = initializeGame(2, k, 5, &gameAfter);

	gameBefore.deck[0][0] = estate;
	gameBefore.deck[0][1]= estate;
	gameBefore.hand[0][0] = adventurer;

	gameBefore.discardCount[0] = 0;
	gameBefore.deckCount[0] = 2;
	gameBefore.handCount[0] = 1;
	gameAfter = gameBefore;
	
	result = playAdventurer(&gameAfter);
	// Discards
	printf("\tTesting Discards...\n\n");
	if(gameAfter.discardCount[0] != (gameBefore.discardCount[0] + 2)){
		printf("\t\tFail:\tShould have discarded 2 cards.\n\n");
		error = 1;
	} 
	else if(gameAfter.discard[0][0] != estate || gameAfter.discard[0][1] != estate){
		printf("\t\tFail:\tDiscards should be Estate cards.\n\n");
		error = 1;
	}
	else{
		printf("\t\tPass.\n\n");
	}
	
	// Hand Cards
	printf("\tTesting Hand Cards...\n\n");
	if(gameAfter.handCount[0] != (gameBefore.handCount[0] - 1)){
		printf("\t\tFail:\tHand count should be one less than starting hand (-1 Adventurer card).\n\n");
		error = 1;
	}else{
		printf("\t\tPass.\n\n");
	}
	// Deck Cards
	printf("\tTesting Deck Cards...\n\n");
	if(gameAfter.deckCount[0] != (gameBefore.deckCount[0] - 2)){
		printf("\t\tFail:\tRemaining deck count should be 2 less.\n\n");
		error = 1;
	} else{
		printf("\t\tPass.\n\n");
	}

	// Custom Deck 3 -- One treasure in deck (and no discard)
	printf("Testing deck with ONE treasure card...\n\n");
	result = initializeGame(2, k, 5, &gameBefore);
	result = initializeGame(2, k, 5, &gameAfter);

	gameBefore.deck[0][0] = estate;
	gameBefore.deck[0][1] = estate;
	gameBefore.deck[0][2] = copper;
	gameBefore.hand[0][0] = adventurer;

	gameBefore.discardCount[0] = 0;
	gameBefore.deckCount[0] = 3;
	gameBefore.handCount[0] = 1;
	gameAfter = gameBefore;
	
	result = playAdventurer(&gameAfter);
	// Discards
	printf("\tTesting Discards...\n\n");
	if(gameAfter.discardCount[0] != (gameBefore.discardCount[0] + 2)){
		printf("\t\tFail:\tShould have discarded 2 cards.\n\n");
		error = 1;
	} 
	else if(gameAfter.discard[0][0] != estate || gameAfter.discard[0][1] != estate){
		printf("\t\tFail:\tDiscards should be Estate cards.\n\n");
		error = 1;
	} else{
		printf("\t\tPass.\n\n");
	}
		
	// Hand Cards
	printf("\tTesting Hand Cards...\n\n");
	if(gameAfter.handCount[0] != (gameBefore.handCount[0])){
		printf("\t\tFail:\tHand count should equal to starting hand (+1 copper, -1 Adventurer).\n\n");
		error = 1;
	} 
	else if(gameAfter.hand[0][0] != copper){
		printf("\t\tFail:\tCard in hand should be copper.\n\n");
		error = 1;
	} else{
		printf("\t\tPass.\n\n");
	}

	// Deck Cards
	printf("\tTesting Deck Cards...\n\n");
	if(gameAfter.deckCount[0] != (gameBefore.deckCount[0] -2)){
		printf("\t\tFail:\tRemaining deck count should be 2 less.\n\n");
		error = 1;
	} else{
		printf("\t\tPass.\n\n");
	}		
	if(!error)
		printf("ADVENTURER TESTS PASSED.\n\n");	
	printf("\n\n################################### END TEST ADVENTURER CARD ############################################################## \n\n");
	return 0;
}
