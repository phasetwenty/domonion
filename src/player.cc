#include <player.h>

class SimpleDeck;

Player::Player(SimpleDeck& deck) {
  deck_ = &deck;
}

SimpleDeck& Player::deck() const {
  return *deck_;
}

Player::~Player() {
}

