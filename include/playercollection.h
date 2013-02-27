#ifndef DOMONION_PLAYERCOLLECTION_H
#define DOMONION_PLAYERCOLLECTION_H

#include <player.h>

template class std::vector<Player*>;

// TODO: I may want to make this more like a standard container.
class PlayerCollection {
public:
  PlayerCollection(std::vector<Player*> *players);
  ~PlayerCollection();

  void advance();

  const Player& current() const;
  const Player& next() const;
  const std::vector<Player*>& players() const;
  const Player& prev() const;

private:
  std::vector<Player*> *players_;
  std::vector<Player*>::iterator players_it_;

  PlayerCollection();
  PlayerCollection(const PlayerCollection& other);
  PlayerCollection& operator=(const PlayerCollection& other);
};

#endif // DOMONION_PLAYERCOLLECTION_H
/*
 * "I don't need this class as much as I need to provide iteration over a basic
 * data structure such as a linked list."
 * Builtin iterators cannot be coerced into providing the functionality I want.
 */
