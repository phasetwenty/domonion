/*
 * simpledeck.cpp
 *
 *  Created on: Jun 29, 2012
 *      Author: chris
 */
#include <assert.h>
#include <algorithm>
#include <stdlib.h>
#include <time.h>

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
	discardPile = vector<string>();
	drawPile = vector<string>();
	hand = vector<string>();
	tableau = vector<string>();

	srand(time(NULL));
}

SimpleDeck::~SimpleDeck() {
	delete discardPile;
	delete drawPile;
	delete hand;
	delete tableau;
}

/*
 * When Seaside is on the table, you have to remember not to clean up cards with
 * Duration.
 */
void SimpleDeck::cleanupAndDraw() {
	while (!hand.empty()) {
		discardPile.push_back(hand[0]);
		hand.erase(hand.begin());
	}

	while (!tableau.empty()) {
		discardPile.push_back(tableau.back());
		tableau.erase(tableau.end());
	}

	draw(5);
}

int SimpleDeck::draw(int count) {
	int drawnCount = 0;
	while (!drawPile.empty() && drawnCount < count) {
		hand.insert(hand.end(), drawPile.front());
		drawPile.erase(drawPile.begin());
		drawnCount++;
	}

	if (drawnCount < count && countDrawableCards() > 0) {
		// In the future, a shuffling event may be needed.
		shuffle();

		while (!drawPile.empty() && drawnCount < count) {
			hand.insert(hand.end(), drawPile.front());
			drawPile.erase(drawPile.begin());
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
	discardPile.push_back(card);
}

/*
 * Moves a card from the hand to the tableau. The user is responsible for taking
 * appropriate action to "play" the card.
 *
 * The return value is the card played.
 */
string SimpleDeck::play(string card) {
	/*
	 * At first I wanted to return a null value when the card isn't found. Then I
	 * thought, this should be an uncommon case: the user should already know that
	 * the card is in the hand and shouldn't be requesting plays of cards that
	 * aren't there.
	 */
	/*
	 * TODO: In the event a card cannot be played, such as plain victory cards
	 * or curses, do something. It's not clear yet if introducing this
	 * information into the deck will harm the separation of concerns.
	 *
	 * Perhaps a property isPlayable() would work: the card will have to be
	 * aware of the game state anyway, so it would be appropriate to know the
	 * answer.
	 */
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

	string foundCard = *it;
	hand.erase(it);
	tableau.push_back(foundCard);

	return foundCard;
}

/*
 * Cards that require reveals:
 * * Spy
 * * Thief
 * * Library sort of
 * * Adventurer
 *
 * Lesser or different reveals:
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
 */
void SimpleDeck::reveal(int count) {

}

/*
 * In base Dominion, you can assume that the draw pile is empty when shuffling.
 * This won't be the case in future sets (Inn, for example, will break it).
 */
void SimpleDeck::shuffle() {
	/*
	 * Publicized this method to provide an interface for the game start
	 * initialization.
	 */

	assert(drawPile.empty());

	random_shuffle(discardPile.begin(), discardPile.end());

	drawPile = discardPile;
	discardPile = vector<string>();
}

const vector<string>& SimpleDeck::getHand() {
	return hand;
}

const vector<string>& SimpleDeck::getTableau() {
	return tableau;
}

int SimpleDeck::countDrawableCards() {
	return drawPile.size() + discardPile.size();
}
