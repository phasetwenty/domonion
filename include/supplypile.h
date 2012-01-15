#ifndef SUPPLYPILE_H
#define SUPPLYPILE_H

#include "card.h"

class SupplyPile {

public:
    SupplyPile(Card& card);
    SupplyPile(const SupplyPile& other);
    virtual ~SupplyPile();
    virtual SupplyPile& operator=(const SupplyPile& other);
    virtual bool operator==(const SupplyPile& other) const;
    
    int getCount() const;
    
private:
    /*
     * Card
     * The card that this pile represents.
     */
    Card *theCard;
    
    /*
     * Count
     * How many cards remain in this pile.
     */
    int currentCount;
    
    /*
     * Properties added in other sets?
     * * Trade Route tokens
     * * Embargo tokens
     */
};

#endif // SUPPLYPILE_H

/*
 * This class should contain the logic for determining its starting count:
 * 10 for nonvictory Kingdom cards, each constant for standard treasures. 
 * Victory and Curses depend on the game state (player count, mostly)
 */