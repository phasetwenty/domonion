#include <vector>

#include <player.h>
#include <playercollection.h>

PlayerCollection::PlayerCollection(int player_count) : players_(),
    players_it_() {
  for (int i = 0; i < player_count; ++i) {
    players_.push_back(new Player(new Deck()));
  }

  players_it_ = players_.begin();
}

PlayerCollection::~PlayerCollection() {
  for (std::vector<Player*>::const_iterator it = players_.begin();
      it != players_.end();
      ++it) {
    delete *it;
  }
}

Player& PlayerCollection::Advance() {
  players_it_ = players_it_ == players_.end() ?
    players_.begin() :
    players_it_ + 1;

  return current();
}

Player& PlayerCollection::current() const {
  return **players_it_;
}

const std::vector<Player*>& PlayerCollection::players() const {
  return players_;
}

