#ifndef DECK_H 
#define DECK_H

extern Card;

class Deck {
public:
    /*
     * Draw, optionally taking a number of cards to draw (defaulting to 1), into
	 * the player's hand.
     */
    Card* draw(int);
    
    /*
     * Return a copy of this deck's discard pile.
     */
    Card* discardPile(); 

	/*
	 * Accepts a card into this deck. Default destination is the discard pile
	 * but you can also gain a card into the hand or on top of the draw pile.
	 */
	void gain(Card& card, std::string dest);
	
    /*
     * Reveal a card from the top of the deck, optionally taking a number of 
     * cards to reveal (defaulting to 1).
     */
    Card* reveal(int);

	/*
	 * Take a card from the deck and remove it. Returns the card that was 
	 * trashed. 
	 */
	Card& trash(Card& card);
    
private:
    /*
     * Collection of Card objects in the discard pile.
     */
    Card* discardPile;
    
    /*
     * Collection of Card objects available for drawing.
     */
    Card* drawPile;
    
    void shuffle();
};

#endif // DECK_H

/*
 * Should owner's hand be a part Deck? I mean, the cards are not considered
 * part of the deck when they're in the hand. Perhaps it's a special member
 * of the deck, in the same way that the piles are special members that make up
 * the deck.
 */
