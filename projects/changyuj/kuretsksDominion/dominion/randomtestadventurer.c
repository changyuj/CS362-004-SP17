
/* randomtestadventurer.c
 *
 * Author: Susan Kuretski
 * CS362-400, Spring 2017
 * Assignment 4: Random Testers
 * May 8, 2017
 *
 * Description: This is a random tester for the Adventurer card. Randomized entities:
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
 * 	The randomized state is set and then Adventurer is played.
 * 	The Oracle will check if the post-conditions are correct.
 * ***********************************************************************************
 * An Adventurer card should:
 *	1. Add 2 Treasure cards (gold, silver, or copper) to current player's hand.
 *		a. If 2 Treasure cards are not available for draw (deck + discard),
 *			then the maximum is drawn (1 or 0 treasure card(s)).
 *		b. Hand Count is increased by 2 (or what Treasure card is drawn).
 *		c. Hand is updated with Treasure cards.
 *	2. playAdventurer function does not consume an action. This is done in function
 *	   playCard() which is not under test here.
 *	3. Non-treasure cards drawn to get Treasure cards are put in the discard pile.
 *	4. playAdventurer should put Adventurer card into playedCards pile and
 *	   increase playedCardsCount by 1.
 *	5. Discard count is only affected by the cards drawn that are discarded.
 *		a. Adventurer card is not discarded yet. This is done in endTurn() which
 *		   is not under test here.
 *	6. Deck count should be decreased by the number of cards drawn and the deck pile
 *	   should place those cards into hand or discard, depending on type of card.
 *	7. State that should NOT change:
 *		numPlayers, supplyCount, embargoTokens, outpostPlayed, outpostTurn,
 *		whoseTurn, phase, numActions, coins, numBuys
 */

#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "mytesthelper.h"
#include "dominion.h"
#include "rngs.h"
#include "interface.h"

int check_playAdventurer(struct gameState *postState, int handPos){
    struct gameState preState;
    int curPlayer = postState->whoseTurn;
    memcpy(&preState, postState, sizeof(struct gameState));

    //Calling playAdventurer Function
    int r = playAdventurer(postState);

    //If the function flat out fails, return -1.
    if(r != 0){
    	r = -1;
    }
    //Setting preState to what the postState should be
    else{
    	int cardDrawn, i = 0, treasureCount = 0, numTotalCards;
    	numTotalCards = preState.deckCount[curPlayer] + preState.discardCount[curPlayer];
    	//Played Card Count
    	preState.playedCardCount++;
    	preState.playedCards[0] = adventurer;

    	//Drawing Cards until 2 Treasures
    	while(treasureCount < 2 && i < numTotalCards){
    		drawOneCard(curPlayer, &preState);
    		cardDrawn = preState.hand[curPlayer][preState.handCount[curPlayer] - 1];
    		if(cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
    			treasureCount++;
    		i++;
    	}
    	//Taking Adventurer out of hand
    	preState.hand[curPlayer][handPos] = -1;
    	if(!(handPos == (preState.handCount[curPlayer] - 1)) || !(preState.handCount[curPlayer] == 1)){
    		preState.hand[curPlayer][handPos] = preState.hand[curPlayer][(preState.handCount[curPlayer] - 1 )];
    		preState.hand[curPlayer][preState.handCount[curPlayer] -1 ] = -1;
    	}
    	//Decrementing Hand Count by one
    	preState.handCount[curPlayer]--;

    	//Comparing oracle to postState (after Adventurer)
        if(memcmp(&preState, postState, sizeof(struct gameState)) != 0)
        	r = -1;
        else
        	r = 0;
    }
	return r;
}


int main(){
    printf("**********************************************************************************************************\n");
    printf("Initiate Random Testing [playAdventurer] function\n");
    SelectStream(SEED_STREAM);
    PutSeed(RANDOM_SEED);
    struct gameState rand_gameState, emptyStruct;
    int advPosition;
    printf("\nRandom Testing..");
    int trialNum;
    for (trialNum = 1; trialNum <= NUM_TRIALS; ++trialNum){
    	rand_gameState = emptyStruct;
        initialize_rand_gameState(&rand_gameState, adventurer);

        // Randomize whose turn
        int rand_curPlayer = randomRange(0, rand_gameState.numPlayers - 1); // -1 because 0 indexed;
        rand_gameState.whoseTurn = rand_curPlayer;

        // Randomize that player's hand
        int rand_handsize = randomRange(MIN_NUM_CARDS_IN_HAND, MAX_NUM_CARDS_IN_HAND);
        rand_gameState.handCount[rand_curPlayer] = rand_handsize;
        fill_with_random_cards(&rand_gameState, rand_gameState.hand[rand_curPlayer],rand_handsize);

        // Putting in Adventurer in random place in hand if not there already
        advPosition = putCardInRandomHandPlace(&rand_gameState, rand_gameState.hand[rand_curPlayer], rand_handsize, adventurer);

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
        printf("   %d", check_playAdventurer(&rand_gameState, advPosition));

    }


    printf("\n******************* Initiate Fixed Testing... ****************************\n");
    int decksize, discardsize, fixedTrialNum = 0;
    for (decksize = 0; decksize < 5; ++decksize){
        for (discardsize = 0; discardsize < 5; ++discardsize){
        	rand_gameState = emptyStruct;
            initialize_rand_gameState(&rand_gameState, adventurer);

            // Randomize whose turn
            int rand_curPlayer = randomRange(0, rand_gameState.numPlayers - 1); // -1 because 0 indexed;
            rand_gameState.whoseTurn = rand_curPlayer;

            // Randomize player's hand
            int rand_handsize = randomRange(MIN_NUM_CARDS_IN_HAND, MAX_NUM_CARDS_IN_HAND);
            rand_gameState.handCount[rand_curPlayer] = rand_handsize;
            fill_with_random_cards(&rand_gameState, rand_gameState.hand[rand_curPlayer],rand_handsize);

            // Putting in Adventurer in random place in hand if not there already
            advPosition = putCardInRandomHandPlace(&rand_gameState, rand_gameState.hand[rand_curPlayer], rand_handsize, adventurer);

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
            printf("   %d",check_playAdventurer(&rand_gameState, advPosition));
        }
    }
    printf("\n\nEnd of Random Testing [playAdventurer] function\n");
    printf("**********************************************************************************************************\n");
	return 0;


}

