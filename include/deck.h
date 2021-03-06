/*
 * deck.h
 *
 *  Created on: Jun 29, 2012
 *      Author: chris
 */

#ifndef DOMONION_DECK_H_
#define DOMONION_DECK_H_

#include <string>
#include <vector>

namespace domonion {

class Card;
class GameState;
class IViewable;

class Deck {
public:
	Deck();
	~Deck();

	/*
	 * Run the standard C and D parts of the turn: (c)leanup the cards on the
	 * table, discard any remaining cards, (d)raw a new hand.
	 */
	void CleanupAndDraw();

	/*
     * Draw, optionally taking a number of cards to draw, into the player's
     * hand. Returns the number of cards drawn.
     */
    int Draw(int count);

	/*
	 * Accepts a card into this deck. Default destination is the discard pile
	 * but you can also gain a card into the hand or on top of the draw pile.
	 */
	void Gain(const Card *card);

	/*
	 * Takes `card` from the hand and plays it. Returns the played card.
	 */
	const Card* Play(const IViewable& card);
    /*
     * Reveal a card from the top of the deck, optionally taking a number of
     * cards to reveal (defaulting to 1).
     */
	void Reveal(int count);

    /*
     * Shuffle the discard pile and add it to the bottom of the draw pile.
     */
	void Shuffle();

	/*
	 * Take a card from the deck and remove it.
	 */
	void Trash(const Card* card);

	const std::vector<const Card*>& draw_pile() const;
	const std::vector<const Card*>& hand() const;
	bool hand_has_actions() const;
	std::vector<const IViewable*>* hand_viewable() const;
	int size() const;
	const std::vector<const Card*>& tableau() const;
	std::vector<const IViewable*>* tableau_viewable() const;
	int victory_points(const GameState& game) const;
private:
    /*
     * Cards in the discard pile.
     */
    std::vector<const domonion::Card*> discard_pile_;

    /*
     * Cards (immediately) available for drawing.
     */
    std::vector<const domonion::Card*> draw_pile_;

    /*
     * Cards in hand.
     */
    std::vector<const domonion::Card*> hand_;

    /*
     * Cards in play.
     */
    std::vector<const domonion::Card*> tableau_;

    Deck(const Deck& other);
    Deck& operator=(const Deck& other);

    std::vector<const IViewable*>* CopyCards(std::vector<const Card*> items) const;

	/*
	 * Return a count of the cards that can be drawn.
	 */
	int CountDrawableCards() const;
};

}

#endif /* DOMONION_DECK_H_ */
