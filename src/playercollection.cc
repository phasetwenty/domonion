#include <vector>

#include <player.h>
#include <playercollection.h>

PlayerCollection::PlayerCollection(std::vector<Player*> *players) : players_(players) {
  players_it_ = players_->begin();
}

Player const& PlayerCollection::current() const {
  return **players_it_;
}

PlayerCollection::~PlayerCollection() {
}

