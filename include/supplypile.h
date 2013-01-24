#ifndef DOMONION_SUPPLYPILE_H
#define DOMONION_SUPPLYPILE_H

class Card;

class SupplyPile {

public:
    SupplyPile(const Card& card, int initial_count);
    SupplyPile(const SupplyPile& other);
    virtual ~SupplyPile();
    virtual bool operator==(const SupplyPile& other) const;

    bool BuyOrGain();

    const Card& card() const;
    int count() const;

private:
    /*
     * The card that this pile represents. I don't expect any manipulation on
     * the card here so I'm going to const it.
     */
    const Card& card_;

    int count_;

    /*
     * Properties added in other sets?
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
