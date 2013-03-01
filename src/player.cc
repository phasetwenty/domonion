#include <player.h>

class Deck;

Player::Player(Deck *deck) : deck_(deck), actions_(0), buys_(0), coin_(0) { }

Player::~Player() {
  delete deck_;
}

int Player::AddCoin(int c) {
  coin_ += c;
  return coin_;
}

int Player::SpendCoin(int c) {
  coin_ -= c;
  return coin_;
}

int Player::actions() const {
  return actions_;
}

int Player::buys() const {
  return buys_;
}

int Player::coin() const {
  return coin_;
}

Deck& Player::deck() const {
  return *deck_;
}


