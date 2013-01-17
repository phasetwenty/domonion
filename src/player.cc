#include <player.h>

class SimpleDeck;

Player::Player(SimpleDeck& deck) {
  deck_ = deck;
}

const SimpleDeck& Player::deck() const {
  return deck_;
}

Player::~Player() {
}

