#ifndef PLAYER_H
#define PLAYER_H

#include <string>

#include "deck.h"

class Player {

public:
	Player();
	~Player();

private:
    
    std::string name;
    
    Deck& deck;

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
