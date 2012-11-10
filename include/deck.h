/*
 * deck.h
 *
 *  Created on: Jun 29, 2012
 *      Author: chris
 */

#ifndef DOMONION_SIMPLEDECK_H_
#define DOMONION_SIMPLEDECK_H_

#include <string>
#include <vector>

class Card;

class SimpleDeck {
public:
	SimpleDeck();
	~SimpleDeck();

	/*
	 * Run the standard C and D parts of the turn: (c)leanup the cards on the
	 * table, discard any remaining cards, (d)raw a new hand.
	 */
	void cleanup_and_draw();

	/*
     * Draw, optionally taking a number of cards to draw, into the player's
     * hand. Returns the number of cards drawn.
     */
    int draw(int count);

	/*
	 * Accepts a card into this deck. Default destination is the discard pile
	 * but you can also gain a card into the hand or on top of the draw pile.
	 */
	void gain(Card card);

	/*
	 * Takes `card` from the hand and plays it. Returns the played card.
	 */
	Card play(std::string card);
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
	std::string trash(Card card);

	const std::vector<Card>& hand() const;
	const std::vector<Card>& tableau() const;

private:
    /*
     * Cards in the discard pile.
     */
    std::vector<Card> discard_pile_;

    /*
     * Cards (immediately) available for drawing.
     */
    std::vector<Card> draw_pile_;

    /*
     * Cards in hand.
     */
    std::vector<Card> hand_;

    /*
     * Cards in play.
     */
    std::vector<Card> tableau_;

	/*
	 * Return a count of the cards that can be drawn.
	 */
	int count_drawable_cards() const;
};

/*
 * Should owner's hand be a part Deck? I mean, the cards are not considered
 * part of the deck when they're in the hand. Perhaps it's a special member
 * of the deck, in the same way that the piles are special members that make up
 * the deck.
 */


#endif /* SIMPLEDECK_H_ */
