#include <vector>

#include <player.h>
#include <playercollection.h>

PlayerCollection::PlayerCollection(std::vector<Player*> *players) :
  players_(players), players_it_(players_->begin()) { }

const Player& PlayerCollection::current() const {
  return **players_it_;
}

PlayerCollection::~PlayerCollection() {
  for (std::vector<Player*>::const_iterator it = players_->begin();
      it != players_->end();
      ++it) {
    delete *it;
  }
  players_->clear();
  delete players_;
}

const std::vector<Player*>& PlayerCollection::players() const {
  return *players_;
}

