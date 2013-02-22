#include <player.h>

class SimpleDeck;

Player::Player(SimpleDeck *deck) : deck_(deck) { }

Player::~Player() {
  delete deck_;
}

SimpleDeck& Player::deck() const {
  return *deck_;
}


