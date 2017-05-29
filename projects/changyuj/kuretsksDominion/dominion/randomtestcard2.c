
/* randomtestcard2.c  (Village Card Test)
 *
 * Author: Susan Kuretski
 * CS362-400, Spring 2017
 * Assignment 4: Random Testers
 * May 8, 2017
 *
 * Description: This is a random tester for the Village card. Randomized entities:
 * 	1. Initial Game State
 * 		a. Num of players (2-4) randomized.
 * 		b. Kingdom Cards (adventurer - treasure_map) randomized.
 * 			i. If Kingdom Card under test is not included, then it is put in
 * 				random location in Kingdom Card array.
 * 		c. Pseudo-randomized seed (see rngs.h)
 * 	2. WhoseTurn
 * 		a. Randomly selected based upon number of players in gameState
 * 	3. Player's hand
 * 		a. Randomly selected from Kingdom Cards
 * 		b. Card under test is put in random location in hand.
 * 		c. Size is randomized (min/max in mytesthelper.h)
 * 	4. Deck
 * 		a. Deck size is randomized (min and max defined in mytesthelper.h)
 * 		b. Deck itself is randomized
 * 	5. Discard
 * 		a. Discard size randomized (min/max in mytesthelper.h)
 * 		b. Discard cards randomized
 * 	6. NumActions and NumBuys
 * 		a. Number is randomized (min/max in mytesthelper.h)
 * 	7. PHASE IS ALWAYS SET TO ACTION
 *
 * 	The randomized state is set and then Village is played.
 * 	The Oracle will check if the post-conditions are correct.
 * ***********************************************************************************
 * A Village card should:
 *	1. playVillage function does not consume an action. This is done in function
 *	   playCard() which is not under test here.
 *	2. playVillage should put Village card into playedCards pile and
 *	   increase playedCardsCount by 1.
 *	3. Number of actions should increase by 2.
 *	4. Player should draw one card from deck and put into hand.
 *		a. Hand Count is increased by 1.
 *		b. Deck Count is decreased by 1.
 *		c. Drawn card should be put into hand array and removed from deck
 *			array
 *	5. State that should NOT change:
		Discard Count, Discard cards, whoseTurn, numPlayers, supplyCount, embargoToken,
		outpostPlayed, outpostTurn, phase, coins, numBuys.
 */

#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "mytesthelper.h"
#include "dominion.h"
#include "rngs.h"

/* Description: playVillage oracle. This function will compare postState (the
 * function which goes through playVillage function and what the state should be
 * (preState struct).
 *
 * Parameters:
 * 	- struct gameState *postState: the current game state to be tested
 * 	- int handPos: the position in which Village is in
 *
 * Returns:
 * 	-1 if pre/post mismatch
 * 	0  if pre/post same state
 *
 */
int check_playVillage(struct gameState *postState, int handPos){
    struct gameState preState;
    int curPlayer = postState->whoseTurn;
    memcpy(&preState, postState, sizeof(struct gameState));

    //Calling playVillage Function
    int r = playVillage(postState, handPos);

    //If the function flat out fails, return -1.
    if(r != 0){
    	r = -1;
    }
    //Setting preState to what the postState should be
    else{

    	//Played Card Count
    	preState.playedCardCount++;
    	preState.playedCards[0] = village;

    	//Incrementing Actions by 2
    	preState.numActions+=2;

    	//Drawing one card
    	drawOneCard(curPlayer, &preState);


    	//Taking Village out of hand
    	preState.hand[curPlayer][handPos] = -1;
    	if(!(handPos == (preState.handCount[curPlayer] - 1)) || !(preState.handCount[curPlayer] == 1)){
    		preState.hand[curPlayer][handPos] = preState.hand[curPlayer][(preState.handCount[curPlayer] - 1 )];
    		preState.hand[curPlayer][preState.handCount[curPlayer] -1 ] = -1;
    	}
    	//Decrementing Hand Count by one
    	preState.handCount[curPlayer]--;

    	//Comparing oracle to postState (after Village)
        if(memcmp(&preState, postState, sizeof(struct gameState)) != 0)
        	r = -1;
        else
        	r = 0;
    }
	return r;
}

int main(){
    printf("**********************************************************************************************************\n");
    printf("Initiate Random Testing [playVillage] function\n");
    SelectStream(SEED_STREAM);
    PutSeed(RANDOM_SEED);
    struct gameState rand_gameState, emptyStruct;
    int villagePosition;
    printf("\nRandom Testing..");
    int trialNum;
    for (trialNum = 1; trialNum <= NUM_TRIALS; ++trialNum){
    	rand_gameState = emptyStruct;
        initialize_rand_gameState(&rand_gameState, village);

        // Randomize whose turn
        int rand_curPlayer = randomRange(0, rand_gameState.numPlayers - 1); // -1 because 0 indexed;
        rand_gameState.whoseTurn = rand_curPlayer;

        // Randomize that player's hand
        int rand_handsize = randomRange(MIN_NUM_CARDS_IN_HAND, MAX_NUM_CARDS_IN_HAND);
        rand_gameState.handCount[rand_curPlayer] = rand_handsize;
        fill_with_random_cards(&rand_gameState, rand_gameState.hand[rand_curPlayer],rand_handsize);

        // Putting in Village in random place in hand if not there already
        villagePosition = putCardInRandomHandPlace(&rand_gameState, rand_gameState.hand[rand_curPlayer], rand_handsize, village);

        // Randomize player's deck
        int rand_decksize = randomRange(MIN_NUM_CARDS_IN_DECK, MAX_NUM_CARDS_IN_DECK);
        rand_gameState.deckCount[rand_curPlayer] = rand_decksize;
        fill_with_random_cards(&rand_gameState, rand_gameState.deck[rand_curPlayer], rand_decksize);

        // Randomize player's discard
        int rand_discardsize = randomRange(MIN_NUM_CARDS_IN_DISCARD, MAX_NUM_CARDS_IN_DISCARD);
        rand_gameState.discardCount[rand_curPlayer] = rand_discardsize;
        fill_with_random_cards(&rand_gameState, rand_gameState.discard[rand_curPlayer], rand_discardsize);

        // Randomize the current turn
        rand_gameState.numBuys = randomRange(MIN_NUM_BUYS, MAX_NUM_BUYS);
        rand_gameState.numActions = randomRange(MIN_NUM_ACTIONS, MAX_NUM_ACTIONS);

        // NOT-RANDOM gameState members
        rand_gameState.phase = 0; // Need action phase

        // Evaluate Random Trial
        printf("\nRandom Trial #%d of %d:", trialNum, NUM_TRIALS);
        printf("   %d", check_playVillage(&rand_gameState, villagePosition));

    }


    printf("\n******************* Initiate Fixed Testing... ****************************\n");
    int decksize, discardsize, fixedTrialNum = 0;
    for (decksize = 0; decksize < 5; ++decksize){
        for (discardsize = 0; discardsize < 5; ++discardsize){
        	rand_gameState = emptyStruct;
            initialize_rand_gameState(&rand_gameState, village);

            // Randomize whose turn
            int rand_curPlayer = randomRange(0, rand_gameState.numPlayers - 1); // -1 because 0 indexed;
            rand_gameState.whoseTurn = rand_curPlayer;

            // Randomize player's hand
            int rand_handsize = randomRange(MIN_NUM_CARDS_IN_HAND, MAX_NUM_CARDS_IN_HAND);
            rand_gameState.handCount[rand_curPlayer] = rand_handsize;
            fill_with_random_cards(&rand_gameState, rand_gameState.hand[rand_curPlayer],rand_handsize);

            // Putting in Village in random place in hand if not there already
            villagePosition = putCardInRandomHandPlace(&rand_gameState, rand_gameState.hand[rand_curPlayer], rand_handsize, village);

            // ITERATED deck size with random cards
            rand_gameState.deckCount[rand_curPlayer] = decksize;
            fill_with_random_cards(&rand_gameState, rand_gameState.deck[rand_curPlayer], decksize);

            // ITERATED discard size with random cards
            rand_gameState.discardCount[rand_curPlayer] = discardsize;
            fill_with_random_cards(&rand_gameState, rand_gameState.discard[rand_curPlayer], discardsize);

            // Randomize the current turn
            rand_gameState.numBuys = randomRange(MIN_NUM_BUYS, MAX_NUM_BUYS);
            rand_gameState.numActions = randomRange(MIN_NUM_ACTIONS, MAX_NUM_ACTIONS);

            // NOT-RANDOM gameState members
            rand_gameState.phase = 0; // need action phase

            // Evaluate Fixed Trial
            printf("\nFixed Trial #%d:", ++fixedTrialNum);
            printf("   %d",check_playVillage(&rand_gameState, villagePosition));
        }
    }
    printf("\n\nEnd of Random Testing [playVillage] function\n");
    printf("**********************************************************************************************************\n");
	return 0;
}

