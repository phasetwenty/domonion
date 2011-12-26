#ifndef COST_H
#define COST_H

/*
 * Cost
 * Provides the mechanism for getting a card's cost. It is designed to handle
 * costs that vary with the game state (e.g., Peddler).
 * 
 * Implicitly, card costs are given as a number of units called Coin, but I 
 * don't think the code needs to reflect this.
 * 
 * At this time, it does not support Potions.
 * 
 * Todo: Bridge. All cards are at minus one. Should the Card know this, or will 
 * it be up to the game state to take the cost and modify it? I think I like the
 * latter.
 * 
 */

extern GameState;

class Cost {
public:
	Cost(int defaultCost, int (*costFunction)(GameState&));
	~Cost();
    int get(GameState&);
    
private:
	/*
	 * All cards have some base cost. They have to, because of cards like 
	 * Workshop. This will generally represent the number printed at the 
	 * bottom-left of the card.
	 */
	int defaultCost;

    /*
     * 
     */
    int (Cost::*costFunction)(GameState&);
    
    /*
     * Most cards have a static cost, and this function represents it.
     */
    int staticCost(GameState& gameState);
    
    /*
     * Other cost functions would be defined here, as needed.
     */
};

#endif // COST_H
