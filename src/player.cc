#include <player.h>

domonion::Player::Player(std::string name, Deck *deck) :
  actions_(0), buys_(0), coin_(0), deck_(deck), name_(name) {

}

domonion::Player::~Player() {
  delete deck_;
}

int domonion::Player::AddCoin(int c) {
  coin_ += c;
  return coin_;
}

void domonion::Player::EndTurn() {
  actions_ = 0;
  buys_ = 0;
  coin_ = 0;
}

int domonion::Player::SpendBuy() {
  buys_ = buys_ > 0 ? buys_ - 1 : 0;
  return buys_;
}

int domonion::Player::SpendCoin(int c) {
  coin_ -= c;
  return coin_;
}

void domonion::Player::StartTurn() {
  actions_ = 1;
  buys_ = 1;
  coin_ = 0;
}

int domonion::Player::actions() const {
  return actions_;
}

int domonion::Player::buys() const {
  return buys_;
}

int domonion::Player::coin() const {
  return coin_;
}

domonion::Deck& domonion::Player::deck() const {
  return *deck_;
}

const std::string& domonion::Player::name() const {
  return name_;
}

int domonion::Player::victory_points() const {
  return deck_->victory_points();
}
