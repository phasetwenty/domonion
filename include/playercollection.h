#ifndef PLAYERCOLLECTION_H
#define PLAYERCOLLECTION_H

class PlayerCollection {

public:
	PlayerCollection();
	~PlayerCollection();

};

#endif // PLAYERCOLLECTION_H
/*
 * This was an impulsive decision. I'm thinking I want to wrap something like a 
 * linked list. Operations I need are:
 * * Whose turn it is now
 * * Who is the player to the left/next
 * * Who is the player to the left/previous
 */