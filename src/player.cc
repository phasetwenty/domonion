#include <player.h>

class Deck;

Player::Player(Deck *deck) :
  actions_(0), buys_(0), coin_(0), deck_(deck), phase_(kUndefined) { }

Player::~Player() {
  delete deck_;
}

int Player::AddCoin(int c) {
  coin_ += c;
  return coin_;
}

void Player::EndTurn() {
  actions_ = 0;
  buys_ = 0;
  coin_ = 0;
}

int Player::SpendBuy() {
  buys_ = buys_ > 0 ? buys_ - 1 : 0;
  return buys_;
}

int Player::SpendCoin(int c) {
  coin_ -= c;
  return coin_;
}

void Player::StartTurn() {
  actions_ = 1;
  buys_ = 1;
  coin_ = 0;
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

Player::Phases Player::phase() const {
  return phase_;
}

void Player::set_phase(Phases value) {
  phase_ = value;
}
