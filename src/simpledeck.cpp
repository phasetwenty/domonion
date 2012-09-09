/*
 * simpledeck.cpp
 *
 *  Created on: Jun 29, 2012
 *      Author: chris
 */
#include <simpledeck.h>

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

SimpleDeck::~SimpleDeck() {

}

/*
 * When Seaside is on the table, you have to remember not to clean up cards with
 * Duration.
 */
void SimpleDeck::cleanupAndDraw() {
	while (!hand.empty()) {
		discardPile.push(hand[0]);
		hand.erase(hand.begin());
	}

	while (!tableau.empty()) {
		discardPile.push(tableau.top());
		tableau.pop();
	}

	draw(5);
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

/*
 * In the future, I'll need to gain cards into the hand and the top of the
 * draw pile.
 */
void SimpleDeck::gain(string card) {
	discardPile.push(card);
}

/*
 * At first I wanted to return a null value when the card isn't found. Then I
 * thought, this should be an uncommon case: the user should already know that
 * the card is in the hand and shouldn't be requesting plays of cards that
 * aren't there.
 */
string SimpleDeck::play(string card) {
	bool done = false;
	vector<string>::iterator it = hand.begin();
	while (!done && it != hand.end()) {
		if (card == *it) {
			done = true;
		}

		if (!done) {
			it++;
		}
	}

	if (!done && it == hand.end()) {
		// throw an exception
	}


	return *it;
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
	while (discardPile.size() > 0) {
		string temp = discardPile.top();
		discardPile.pop();
		drawPile.push(temp);
	}
}

const vector<string>& SimpleDeck::getHand() {
	return hand;
}

int SimpleDeck::countDrawableCards() {
	return drawPile.size() + discardPile.size();
}
