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
    /*
     * Card bank? Some object that handles the collection of Supply piles for 
     * all cards that need to be out. It would be inappropriate for the game 
     * state to have to track all that information on its own.
     */
};

#endif // GAMESTATE_H

/*
 * Things tracked in the game state (directly or indirectly):
 * Players
 * Supply piles
 * * How to optionally include supplies: Colony, Platinum
 * Turns
 * The state of the current turn
 * * Whose turn it is
 * * Actions/Treasures in play / tableau
 * * Actions/Buy/Coin count
 */
