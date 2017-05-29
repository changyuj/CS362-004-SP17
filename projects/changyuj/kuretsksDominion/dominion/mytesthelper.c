/*
 * mytesthelper.c
 *
 *  Created on: May 8, 2017
 *      Author: Susie
 */
#include "dominion.h"
#include "rngs.h"
#include <math.h>
#include <assert.h>
#include <stdlib.h>
#include "mytesthelper.h"

int randomRange(int min, int max)
{
    return floor(Random()*(double)(max-min+1)) + min;
}

void make_rand_kingdomCards(int kingdomCards[10])
{
    assert(MAX_KINGDOM_CARD-MIN_KINGDOM_CARD + 1 >= 10); // otherwise loop below will be infinite
    int i, j;
    for (i = 0; i < 10; ++i)
    {
        int duplicate;
        int rand_kCard;
        // generate random kingdom card and make sure it's not a duplicate
        do{
            rand_kCard = randomRange(MIN_KINGDOM_CARD,MAX_KINGDOM_CARD);
            duplicate = 0;
            for (j = 0; j < i && !duplicate; j++) // will break loop early as soon as duplicate found
                duplicate = (rand_kCard == kingdomCards[j]);
        } while (duplicate);

        kingdomCards[i] = rand_kCard;
    }
}

void fill_with_random_cards(struct gameState *state, int cardpile[MAX_DECK], int size)
{
	int i;
    for (i = 0; i < size; i++)
    {
        int rand_card;
        do{
            rand_card = randomRange(MIN_CARD, MAX_CARD);
        }
        while (state->supplyCount[rand_card] < 0); // from an initialized state, (kingdom) cards not in game will have a supply = -1

        cardpile[i] = rand_card;
    }
}

int putCardInRandomHandPlace(struct gameState *state, int hand[MAX_DECK], int size, int card){
	int i, place, hasCard = 0;
	for(i = 0; i < size; i++){
		if(hand[i] == card){
			hasCard = 1;
			place = i;
			break;
		}
	}
	if(!hasCard){
		place = randomRange(0, size - 1);  // -1 to accommodate array elements
		hand[place] = card;
	}
	return place;
}


void initialize_rand_gameState(struct gameState *state, int selectedCard)
{
	int i;
    int rand_numPlayers = randomRange(MIN_NUM_TESTPLAYERS, MAX_NUM_TESTPLAYERS);
    int rand_kingdomCards[10];
    make_rand_kingdomCards(rand_kingdomCards);

    // Kingdom Cards should have selected card
    int hasCard = 0;
    for (i = 0; i < 10 && !hasCard; ++i)
        hasCard = (rand_kingdomCards[i] == selectedCard);
    if (!hasCard) // overwrite one of the kingdom cards for selected card
        rand_kingdomCards[randomRange(0, 9)] = selectedCard;

    int randomSeed = randomRange(1,NUM_TRIALS*10);

    int init = initializeGame(rand_numPlayers, rand_kingdomCards, randomSeed, state);
    assert(init == 0);
}

int drawOneCard(int player, struct gameState *state)
{
	int count;
	int deckCounter;
	if (state->deckCount[player] <= 0){//Deck is empty
		//Step 1 Shuffle the discard pile back into a deck
		int i;
		//Move discard to deck
		for (i = 0; i < state->discardCount[player];i++){
		  state->deck[player][i] = state->discard[player][i];
		  state->discard[player][i] = -1;
		}

		state->deckCount[player] = state->discardCount[player];
		state->discardCount[player] = 0;//Reset discard

		//Shuffle the deck
		shuffle(player, state);//Shuffle the deck up and make it so that we can draw
		state->discardCount[player] = 0;

		//Step 2 Draw Card
		count = state->handCount[player];//Get current player's hand count
		deckCounter = state->deckCount[player];//Create a holder for the deck count

		if (deckCounter == 0)
		  return -1;

		state->hand[player][count] = state->deck[player][deckCounter - 1];//Add card to hand
		state->deckCount[player]--;
		state->handCount[player]++;//Increment hand count
	}

	else {
		int count = state->handCount[player];//Get current hand count for player
		int deckCounter;

		deckCounter = state->deckCount[player];//Create holder for the deck count
		state->hand[player][count] = state->deck[player][deckCounter - 1];//Add card to the hand
		state->deckCount[player]--;
		state->handCount[player]++;//Increment hand count
	}
  return 0;
}
