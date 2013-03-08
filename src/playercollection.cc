#include <iterator>
#include <sstream>
#include <vector>

#include <player.h>
#include <playercollection.h>

domonion::PlayerCollection::PlayerCollection(int player_count) : players_(),
    players_it_() {
  std::stringstream ss;
  for (int i = 0; i < player_count; ++i) {
    ss.str("");
    ss << "Player " << i + 1;
    players_.push_back(new Player(ss.str(), new Deck()));
  }

  players_it_ = players_.begin();
}

domonion::PlayerCollection::~PlayerCollection() {
  for (std::vector<Player*>::const_iterator it = players_.begin();
      it != players_.end();
      ++it) {
    delete *it;
  }
}

domonion::Player& domonion::PlayerCollection::Advance() {
  if (*players_it_ == players_.back()) {
    players_it_ = players_.begin();
  } else {
    std::advance(players_it_, 1);
  }

  return current();
}

domonion::Player& domonion::PlayerCollection::current() const {
  return **players_it_;
}

const std::vector<domonion::Player*>& domonion::PlayerCollection::players() const {
  return players_;
}

