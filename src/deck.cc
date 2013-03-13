/*
 * deck.cc
 *
 *  Created on: Jun 29, 2012
 *      Author: chris
 */
#include <assert.h>
#include <algorithm>
#include <stdlib.h>
#include <time.h>

#include <card.h>
#include <cards/basicvictory.h>
#include <deck.h>

namespace domonion {

Deck::Deck() : discard_pile_(), draw_pile_(), hand_(), tableau_() {
  srand(time(NULL));
}

Deck::~Deck() {
  std::vector<const Card*> items[4] = { discard_pile_, draw_pile_, hand_, tableau_ };

  for (int i = 0; i < 4; ++i) {
    items[i].clear();
  }
}

bool CardComparer(const Card *lhs, const Card *rhs);

/*
 * When Seaside is on the table, you have to remember not to clean up cards with
 * Duration.
 */
void Deck::CleanupAndDraw() {
  while (!hand_.empty()) {
    discard_pile_.push_back(hand_[0]);
    hand_.erase(hand_.begin());
  }

  while (!tableau_.empty()) {
    discard_pile_.push_back(tableau_.back());
    tableau_.erase(tableau_.begin());
  }

  Draw(5);
}

std::vector<const IViewable*>* Deck::CopyCards(
    std::vector<const Card*> items) const {
  std::vector<const IViewable*> *result =
    new std::vector<const IViewable*>;

  for (std::vector<const Card*>::const_iterator it = items.begin();
      it != items.end();
      ++it) {
    result->push_back(*it);
  }

  return result;
}

int Deck::CountDrawableCards() const {
  return draw_pile_.size() + discard_pile_.size();
}


int Deck::Draw(int count) {
  int drawn_count = 0;
  while (!draw_pile_.empty() && drawn_count < count) {
    hand_.insert(hand_.end(), draw_pile_.front());
    draw_pile_.erase(draw_pile_.begin());
    drawn_count++;
  }

  if (drawn_count < count && CountDrawableCards() > 0) {
    // In the future, a shuffling event may be needed.
    Shuffle();

    while (!draw_pile_.empty() && drawn_count < count) {
      hand_.insert(hand_.end(), draw_pile_.front());
      draw_pile_.erase(draw_pile_.begin());
      drawn_count++;
    }
  }

  std::sort(hand_.begin(), hand_.end(), CardComparer);
  return drawn_count;
}

/*
 * In the future, I'll need to gain cards into the hand and the top of the
 * draw pile.
 */
void Deck::Gain(const Card *card) {
  discard_pile_.push_back(card);
}

/*
 * Moves a card from the hand to the tableau. The user is responsible for taking
 * appropriate action to "play" the card.
 *
 * The return value is the card played.
 */
const Card* Deck::Play(const IViewable& card) {
  /*
   * At first I wanted to return a null value when the card isn't found. Then I
   * thought, this should be an uncommon case: the user should already know that
   * the card is in the hand and shouldn't be requesting plays of cards that
   * aren't there.
   */
  /*
   * TODO: In the event a card cannot be played, such as plain victory cards
   * or curses, do something. It's not clear yet if introducing this
   * information into the deck will harm the separation of concerns.
   *
   * Perhaps a property isPlayable() would work: the card will have to be
   * aware of the game state anyway, so it would be appropriate to know the
   * answer.
   */
  std::string *needle = card.ToString();
  const Card *result = NULL;

  std::vector<const Card*>::iterator it = hand_.begin();
  for (; it != hand_.end(); ++it) {
    if (*needle == (*it)->name()) {
      result = *it;
      break;
    }
  }

  hand_.erase(it);
  tableau_.push_back(result);

  delete needle;
  return result;
}

/*
 * Cards that require reveals:
 * * Spy
 * * Thief
 * * Library sort of
 * * Adventurer
 *
 * Lesser or different reveals:
 * * Moat
 * * Bureaucrat
 */

/*
 * This is troublesome. I need to provide these cards so that another
 * context can manipulate the revealed cards and possibly the rest of the
 * deck based on what it finds. Options include
 * * Changing the method signature to take a function to run on the revealed cards.
 * * Adding a member `revealedCards` which is populated by this method? Might
 *   need more thought.
 */
void Deck::Reveal(int count) {

}

/*
 * In base Dominion, you can assume that the draw pile is empty when shuffling.
 * This won't be the case in future sets (Inn, for example, will break it).
 */
void Deck::Shuffle() {
  /*
   * Publicized this method to provide an interface for the game start
   * initialization.
   */

  assert(draw_pile_.empty());

  random_shuffle(discard_pile_.begin(), discard_pile_.end());

  draw_pile_ = discard_pile_;
  discard_pile_ = std::vector<const Card*>();
}

const std::vector<const Card*>& Deck::draw_pile() const {
  return draw_pile_;
}

const std::vector<const Card*>& Deck::hand() const {
  return hand_;
}

bool Deck::hand_has_actions() const {
  for (std::vector<const Card*>::const_iterator it = hand_.begin();
      it != hand_.end();
      ++it) {
    if ((*it)->is_action()) {
      return true;
    }
  }

  return false;
}

std::vector<const IViewable*>* Deck::hand_viewable() const {
  return CopyCards(hand_);
}

const std::vector<const Card*>& Deck::tableau() const {
  return tableau_;
}

std::vector<const IViewable*>* Deck::tableau_viewable() const {
  return CopyCards(tableau_);
}

int Deck::victory_points() const {
  int result = 0;
  std::vector<const Card*> piles[] = { discard_pile_, draw_pile_, hand_, tableau_ };
  for (int i = 0; i < 4; ++i) {
    for (std::vector<const Card*>::const_iterator it = piles[i].begin();
        it != piles[i].end();
        ++it) {
      const cards::BasicVictory *v =
        dynamic_cast<const cards::BasicVictory*>(*it);
      if (v != 0) {
        result += v->points_provided();
      }
    }
  }
  return result;
}

bool CardComparer(const Card *lhs, const Card *rhs) {
  return *lhs < *rhs;
}

}

