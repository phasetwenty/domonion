#include <player.h>

class Deck;

Player::Player(Deck *deck) : deck_(deck) { }

Player::~Player() {
  delete deck_;
}

Deck& Player::deck() const {
  return *deck_;
}


