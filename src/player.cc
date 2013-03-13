#include <gamestate.h>
#include <player.h>

namespace domonion {

Player::Player(std::string name, Deck *deck) :
  actions_(0), buys_(0), coin_(0), deck_(deck), name_(name) {

}

Player::~Player() {
  delete deck_;
}

int Player::AddActions(int a) {
  return ChangeIntMember(actions_, a);
}

int Player::AddBuys(int b) {
  return ChangeIntMember(buys_, b);
}

int Player::AddCoin(int c) {
  return ChangeIntMember(coin_, c);
}

int Player::ChangeIntMember(int& member, int amount) {
  member = member + amount >= 0 ? member + amount : 0;
  return member;
}

void Player::EndTurn() {
  actions_ = 0;
  buys_ = 0;
  coin_ = 0;
}

int Player::SpendAction() {
  return ChangeIntMember(actions_, -1);
}

int Player::SpendBuy() {
  return ChangeIntMember(buys_, -1);
}

int Player::SpendCoin(int c) {
  return ChangeIntMember(coin_, -c);
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

const std::string& Player::name() const {
  return name_;
}

int Player::victory_points(const GameState& game) const {
  return deck_->victory_points(game);
}

}
