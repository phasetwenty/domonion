#ifndef PLAYER_H
#define PLAYER_H

#include <string>

#include <deck.h>

class Player {
public:
	Player(SimpleDeck *deck);
	~Player();

	SimpleDeck& deck() const;

	/*
	 * Current state
	 */
	int actions() const;
	int buys() const;
	int coin() const;

private:
    std::string name_;

    SimpleDeck *deck_;

    int actions_;
    int buys_;
    int coin_;

};

#endif // PLAYER_H

/*
 * Things to track
 * * Deck
 * * Victory token count (Prosperity and beyond)
 * * Hand
 * * Tableau: belongs to GameState or Player? I think GameState because there
 *   can only be one at a time.
 */
