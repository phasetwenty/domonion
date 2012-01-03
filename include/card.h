#ifndef CARD_H
#define CARD_H

class Card {

public:
	Card();
	~Card();
	
private:
	/*
	 * Cost
	 * Essentially an int (probably even something smaller). Peddler, for 
	 * example, has adjustable cost also consider cards like bridge which 
	 * changes all cards' costs. May need to change this to something more 
	 * flexible.
	 */
    Cost& cost;
    
	/*
	 * Card text
	 * should be pretty basic, but may need some formatting power?
	 */
	std::string text;

	/*
	 * Effect
	 * Should be a collection of effect objects. For example, a copper
	 * has a + 1 coin effect (which should be indistinguishable from an 
	 * action's + coin effect). 
	 * 
	 * The effects have an explicit (and often important) order.
	 */
	
	/*
	 * Reaction
	 * Another instance of the effect. Does it need to be separate? I'm on 
	 * the fence.
	 */
	
	/*
	 * Type
	 * Types are pretty straightforward. The only thing I can think of right
	 * now is that cards can have multiple types. When checking if a card is
	 * of a specific type, it should look more like "if <type> is in the 
	 * types <card> has".
	 */
	
	
	/*
	 * Subtype
	 * This is most important for checking for attacks, but still applies to
	 * reactions.
	 * 
	 * Would it make sense to separate the effects into the types? For 
	 * example, you have your default effect when the card is played. The 
	 * attack could resolve separately. I think it may also help for 
	 * checking the card types.
	 */

	/*
	 * Metadata
	 * Some metadata cards need not (but do not affect gameplay) gameplay 
	 * include:
	 * * Dominion set
	 * * Card categories like Trash and Defenses 
	 */
};

#endif // CARD_H
