/*
 * simpledeck.h
 *
 *  Created on: Jun 29, 2012
 *      Author: chris
 */

#ifndef SIMPLEDECK_H_
#define SIMPLEDECK_H_

#include <string>
#include <stack>
#include <vector>

class SimpleDeck {
public:
	SimpleDeck();
	~SimpleDeck();

	/*
	 * Run the standard C and D parts of the turn: (c)leanup the cards on the
	 * table, discard any remaining cards, (d)raw a new hand.
	 */
	void cleanupAndDraw();

	/*
     * Draw, optionally taking a number of cards to draw, into the player's
     * hand. Returns the number of cards drawn.
     */
    int draw(int count);

	/*
	 * Accepts a card into this deck. Default destination is the discard pile
	 * but you can also gain a card into the hand or on top of the draw pile.
	 */
	void gain(std::string card);

	/*
	 * Takes `card` from the hand and plays it. Returns the played card.
	 */
	std::string play(std::string card);
    /*
     * Reveal a card from the top of the deck, optionally taking a number of
     * cards to reveal (defaulting to 1).
     */
	void reveal(int count);

    /*
     * Shuffle the discard pile and add it to the bottom of the draw pile.
     */
	void shuffle();

	/*
	 * Take a card from the deck and remove it. Returns the card that was
	 * trashed.
	 */
	std::string trash(std::string card);

	const std::vector<std::string>& getHand();
	const std::vector<std::string>& getTableau();

private:
    /*
     * Cards in the discard pile.
     */
    std::vector<std::string> discardPile;

    /*
     * Cards (immediately) available for drawing.
     */
    std::vector<std::string> drawPile;

    /*
     * Cards in hand.
     */
    std::vector<std::string> hand;

    /*
     * Cards in play.
     */
    std::vector<std::string> tableau;

	/*
	 * Return a count of the cards that can be drawn.
	 */
	int countDrawableCards();
};

/*
 * Should owner's hand be a part Deck? I mean, the cards are not considered
 * part of the deck when they're in the hand. Perhaps it's a special member
 * of the deck, in the same way that the piles are special members that make up
 * the deck.
 */


#endif /* SIMPLEDECK_H_ */
