
/* randomtestcard1.c (Smithy random test)
 *
 * Author: Susan Kuretski
 * CS362-400, Spring 2017
 * Assignment 4: Random Testers
 * May 8, 2017
 *
 * Description: This is a random tester for the Smithy card. Randomized entities:
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
 * 	The randomized state is set and then Smithy is played.
 * 	The Oracle will check if the post-conditions are correct.
 * ***********************************************************************************
 * A Smithy card should:
 * 	1. Add three cards to player's hand.
 * 		a. If there are no draw cards from deck, then it is assumed
 * 		the discard pile is shuffled to be the deck again.
 * 		b. The three cards can be any type (Victory, Action, Treasure, etc).
 * 		c. If there are less than 3 cards to be drawn, then the player draws
 * 		max capable.
 * 	2. Playing Smithy consumes one action.
 * 		a. It should be noted an action is not consumed in the function
 * 		cardEffect() function. It is done at playCard(), which is not tested here.
 * 		b. Therefore, the number of actions will NOT be decremented in this test case.
 * 	3. Playing Smithy puts Smithy in the playedCards pile and increments playedCardsCount
 * 		by one.
 * 		a. It *should* not put in discard until endTurn() (endTurn is not under test here).
 * 	4. Playing Smithy should decrement handCount by one and remove it from hand pile.
 * 		a. Playing Smithy should increment handCount by number of cards drawn.
 * 	5. Playing Smithy should decrement deckCount by three (or what is drawn) and the
 * 		card(s) from the deck should be placed into hand.
 * 	5. State that should NOT change:
 * 		numPlayers, supplyCount, embargoTokens,outpostPlayed, outpostTurn,
 * 		whoseTurn, phase, numActions, coins, numBuys, discard, discardCount.
 */

#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "mytesthelper.h"
#include "dominion.h"
#include "rngs.h"

/*  --  Smithy Oracle --
 *
 * Description: takes in struct gameState postState which will use
 * the function playSmithy. The postState will be compared to what
 * the state should be (preState will contain this).
 *
 * Parameters:
 * 	 - struct gameState to be tested
 * 	 - int handPos indicating where Smithy is in hand
 *
 * Returns:
 * 	int
 * 		-1 indicates mismatch
 * 		0 indicates no error
 *
 */
int check_playSmithy(struct gameState *postState, int handPos){
    struct gameState preState;
    int curPlayer = postState->whoseTurn;
    memcpy(&preState, postState, sizeof(struct gameState));

    //Calling playSmithy Function
    int r = playSmithy(postState, handPos);

    //If the function flat out fails, return -1.
    if(r != 0){
    	r = -1;
    }
    //Setting preState to what the postState should be
    else{
    	int i;
    	//Played Card Count
    	preState.playedCardCount++;
    	preState.playedCards[0] = smithy;

    	//Draw Cards
    	for(i = 0; i < 3; i++){
    		drawOneCard(curPlayer, &preState);
    	}
    	//Taking Smithy out of hand
    	preState.hand[curPlayer][handPos] = -1;
    	if(!(handPos == (preState.handCount[curPlayer] - 1)) || !(preState.handCount[curPlayer] == 1)){
    		preState.hand[curPlayer][handPos] = preState.hand[curPlayer][(preState.handCount[curPlayer] - 1 )];
    		preState.hand[curPlayer][preState.handCount[curPlayer] -1 ] = -1;
    	}
    	//Decrementing Hand Count by one
    	preState.handCount[curPlayer]--;

    	//Comparing oracle to postState (after Smithy)
        if(memcmp(&preState, postState, sizeof(struct gameState)) != 0)
        	r = -1;
        else
        	r = 0;
    }
    return r;
}


int main()
{
    printf("**********************************************************************************************************\n");
    printf("Initiate Random Testing [playSmithy] function\n");
    SelectStream(SEED_STREAM);
    PutSeed(RANDOM_SEED);
    struct gameState rand_gameState, emptyStruct;
    int smithyPosition;
    printf("\nRandom Testing..");
    int trialNum;
    for (trialNum = 1; trialNum <= NUM_TRIALS; ++trialNum){
    	rand_gameState = emptyStruct;
        initialize_rand_gameState(&rand_gameState, smithy);

        // Randomize whose turn
        int rand_curPlayer = randomRange(0, rand_gameState.numPlayers - 1); // -1 because 0 indexed;
        rand_gameState.whoseTurn = rand_curPlayer;

        // Randomize that player's hand
        int rand_handsize = randomRange(MIN_NUM_CARDS_IN_HAND, MAX_NUM_CARDS_IN_HAND);
        rand_gameState.handCount[rand_curPlayer] = rand_handsize;
        fill_with_random_cards(&rand_gameState, rand_gameState.hand[rand_curPlayer],rand_handsize);

        // Putting in Smithy in random place in hand if not there already
        smithyPosition = putCardInRandomHandPlace(&rand_gameState, rand_gameState.hand[rand_curPlayer], rand_handsize, smithy);

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
        printf("   %d", check_playSmithy(&rand_gameState, smithyPosition));

    }


    printf("\n******************* Initiate Fixed Testing... ****************************\n");
    int decksize, discardsize, fixedTrialNum = 0;
    for (decksize = 0; decksize < 5; ++decksize){
        for (discardsize = 0; discardsize < 5; ++discardsize){
        	rand_gameState = emptyStruct;
            initialize_rand_gameState(&rand_gameState, smithy);

            // Randomize whose turn
            int rand_curPlayer = randomRange(0, rand_gameState.numPlayers - 1); // -1 because 0 indexed;
            rand_gameState.whoseTurn = rand_curPlayer;

            // Randomize player's hand
            int rand_handsize = randomRange(MIN_NUM_CARDS_IN_HAND, MAX_NUM_CARDS_IN_HAND);
            rand_gameState.handCount[rand_curPlayer] = rand_handsize;
            fill_with_random_cards(&rand_gameState, rand_gameState.hand[rand_curPlayer],rand_handsize);

            // Putting in Smithy in random place in hand if not there already
            smithyPosition = putCardInRandomHandPlace(&rand_gameState, rand_gameState.hand[rand_curPlayer], rand_handsize, smithy);

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
            printf("   %d",check_playSmithy(&rand_gameState, smithyPosition));
        }
    }
    printf("\n\nEnd of Random Testing [playSmithy] function\n");
    printf("**********************************************************************************************************\n");
	return 0;
}
