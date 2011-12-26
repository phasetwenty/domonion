#ifndef GAMESTATE_H
#define GAMESTATE_H



/*
 * GameState
 * All of the state of the game in progress.
 */
class GameState {
public:
	GameState();
	~GameState();
    
private:
    

};

#endif // GAMESTATE_H

/*
 * Things tracked in the game state (directly or indirectly):
 * Players
 * Supply piles
 * * How to optionally include supplies: Colony, Platinum
 * Turns
 * The state of the current turn
 * * Actions/Treasures in play / tableau
 * * Actions/Buy/Coin count
 */