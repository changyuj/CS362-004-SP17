/*
 * mytesthelper.h
 *
 *  Created on: May 8, 2017
 *      Author: Susie
 */

#ifndef MYTESTHELPER_H_
#define MYTESTHELPER_H_


#define MAX_PLAYERS 4
#define MAX_DECK 500

// ******** TEST CONSTANTS ***************
#define NUM_TRIALS 500

//		Players
#define MIN_NUM_TESTPLAYERS 2

//This is MAX_PLAYERS
#define MAX_NUM_TESTPLAYERS 4

//		Cards (see dominion.h for enum)
#define MIN_CARD 0	//curse
#define MAX_CARD 26	//treasure_map

//		Kingdom Cards
#define MIN_KINGDOM_CARD 7	//adventurer
#define MAX_KINGDOM_CARD 26	//treasure_map

//		Turn
#define MIN_NUM_ACTIONS 1 // be sure to have at least 1 when testing an action card
#define MAX_NUM_ACTIONS 5
#define MIN_NUM_BUYS 1
#define MAX_NUM_BUYS 5

//		Player Cards
#define MIN_NUM_CARDS_IN_HAND 1
#define MAX_NUM_CARDS_IN_HAND 7
#define MIN_NUM_CARDS_IN_DECK 0
#define MAX_NUM_CARDS_IN_DECK 20
#define MIN_NUM_CARDS_IN_DISCARD 0
#define MAX_NUM_CARDS_IN_DISCARD 20

//		PRNG Seed and Stream
#define RANDOM_SEED 39
#define SEED_STREAM 9

struct gameState;
int randomRange(int min, int max);
void make_rand_kingdomCards(int kC[10]);
void fill_with_random_cards(struct gameState *state, int cardpile[MAX_DECK], int size);
void initialize_rand_gameState(struct gameState *state, int selectedCard);
int putCardInRandomHandPlace(struct gameState *state, int hand[MAX_PLAYERS], int size, int card);
int drawOneCard(int player, struct gameState *state);

#endif /* MYTESTHELPER_H_ */
