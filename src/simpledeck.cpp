/*
 * simpledeck.cpp
 *
 *  Created on: Jun 29, 2012
 *      Author: chris
 */

#include "../include/simpledeck.h"

using namespace std;

/*
 * It had occurred to me to provide functionality to initialize the deck with
 * the starting cards, but it would require knowledge of things like supply
 * piles and I don't think that's necessary. Off the top of my head, it makes
 * sense for the game state to manipulate the decks using the standard
 * interface.
 */
SimpleDeck::SimpleDeck() {
	discardPile = stack<string>();
	drawPile = stack<string>();
	hand = vector<string>();
	tableau = stack<string>();
}

int SimpleDeck::draw(int count) {
	int drawnCount = 0;
	while (!drawPile.empty() && drawnCount < count) {
		hand.insert(hand.end(), drawPile.top());
		drawPile.pop();
		drawnCount++;
	}

	if (drawnCount < count && countDrawableCards() > 0) {
		// In the future, a shuffling event may be needed.
		shuffle();

		while (!drawPile.empty() && drawnCount < count) {
			hand.insert(hand.end(), drawPile.top());
			drawPile.pop();
			drawnCount++;
		}
	}

	return drawnCount;
}

int SimpleDeck::countDrawableCards() {
	return drawPile.size() + discardPile.size();
}

void SimpleDeck::gain(string card) {
	discardPile.push(card);
}

/*
 * Cards that require reveals:
 * * Spy
 * * Thief
 * * Library sort of
 * * Adventurer
 *
 * Lesser reveals:
 * * Moat
 * * Bureaucrat
 */

/*
 * This is troublesome. I need to provide these cards so that another
 * context can manipulate the revealed cards and possibly the rest of the
 * deck based on what it finds. Options include
 * * Changing the method signature to take a function to run on the revealed cards.
 * * Adding a member `revealedCards` which is populated by this method? Might
 *   need more thought.
 * *
 */
void SimpleDeck::reveal(int count) {

}


/*
 * Publicized this method to provide an interface for the game start
 * initialization.
 */
void SimpleDeck::shuffle() {
	// TODO: actually shuffle the discard pile. And see if there is a non-naive way of moving all of these objects.

}
