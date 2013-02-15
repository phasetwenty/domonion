#ifndef DOMONION_SUPPLYPILE_H
#define DOMONION_SUPPLYPILE_H

#include <card.h>
#include <interfaces.h>

class SupplyPile : public IViewable {

public:
    SupplyPile(const Card *card, int initial_count);
    SupplyPile(const SupplyPile& other);
    virtual ~SupplyPile();
    virtual bool operator==(const SupplyPile& other) const;

    /*
     *
     */
    bool BuyOrGain();
    std::string Info() const;
    std::string ToString() const;

    const Card& card() const;
    int count() const;
    std::string name() const;
private:
    const Card *card_;

    int count_;

    /*
     * Properties added in other sets:
     * * Trade Route tokens
     * * Embargo tokens
     */
};

#endif // DOMONION_SUPPLYPILE_H

/*
 * "This class should contain the logic for determining its starting count:
 * 10 for nonvictory Kingdom cards, each constant for standard treasures.
 * Victory and Curses depend on the game state (player count, mostly)"
 *
 * I've changed my mind on this. Cards should know how many they should start
 * with. This does complicate the cards (requiring they reference the game
 * state) unfortunately.
 */
