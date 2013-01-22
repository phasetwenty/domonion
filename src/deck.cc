/*
 * simpledeck.cpp
 *
 *  Created on: Jun 29, 2012
 *      Author: chris
 */
#include <assert.h>
#include <algorithm>
#include <stdlib.h>
#include <time.h>

#include <card.h>
#include <deck.h>

/*
 * It had occurred to me to provide functionality to initialize the deck with
 * the starting cards, but it would require knowledge of things like supply
 * piles and I don't think that's necessary. Off the top of my head, it makes
 * sense for the game state to manipulate the decks using the standard
 * interface.
 */
SimpleDeck::SimpleDeck() {
  discard_pile_ = std::vector<Card>();
  draw_pile_ = std::vector<Card>();
  hand_ = std::vector<Card>();
  tableau_ = std::vector<Card>();

  srand(time(NULL));
}

SimpleDeck::~SimpleDeck() {
}

/*
 * When Seaside is on the table, you have to remember not to clean up cards with
 * Duration.
 */
void SimpleDeck::CleanupAndDraw() {
  while (!hand_.empty()) {
    discard_pile_.push_back(hand_[0]);
    hand_.erase(hand_.begin());
  }

  while (!tableau_.empty()) {
    discard_pile_.push_back(tableau_.back());
    tableau_.erase(tableau_.end());
  }

  Draw(5);
}

int SimpleDeck::Draw(int count) {
  int drawn_count = 0;
  while (!draw_pile_.empty() && drawn_count < count) {
    hand_.insert(hand_.end(), draw_pile_.front());
    draw_pile_.erase(draw_pile_.begin());
    drawn_count++;
  }

  if (drawn_count < count && count_drawable_cards() > 0) {
    // In the future, a shuffling event may be needed.
    Shuffle();

    while (!draw_pile_.empty() && drawn_count < count) {
      hand_.insert(hand_.end(), draw_pile_.front());
      draw_pile_.erase(draw_pile_.begin());
      drawn_count++;
    }
  }

  return drawn_count;
}

/*
 * In the future, I'll need to gain cards into the hand and the top of the
 * draw pile.
 */
void SimpleDeck::Gain(Card card) {
  discard_pile_.push_back(card);
}

/*
 * Moves a card from the hand to the tableau. The user is responsible for taking
 * appropriate action to "play" the card.
 *
 * The return value is the card played.
 */
Card SimpleDeck::Play(std::string card) {
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
  bool done = false;
  std::vector<Card>::iterator it = hand_.begin();
  while (!done && it != hand_.end()) {
    if (card == it->name()) {
      done = true;
    }

    if (!done) {
      it++;
    }
  }

  if (!done && it == hand_.end()) {
    // throw an exception
  }

  Card found_card = *it;
  hand_.erase(it);
  tableau_.push_back(found_card);

  return found_card;
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
void SimpleDeck::Reveal(int count) {

}

/*
 * In base Dominion, you can assume that the draw pile is empty when shuffling.
 * This won't be the case in future sets (Inn, for example, will break it).
 */
void SimpleDeck::Shuffle() {
  /*
   * Publicized this method to provide an interface for the game start
   * initialization.
   */

  assert(draw_pile_.empty());

  random_shuffle(discard_pile_.begin(), discard_pile_.end());

  draw_pile_ = discard_pile_;
  discard_pile_ = std::vector<Card>();
}

const std::vector<Card>& SimpleDeck::hand() const {
  return hand_;
}

const std::vector<Card>& SimpleDeck::tableau() const {
  return tableau_;
}

int SimpleDeck::count_drawable_cards() const {
  return draw_pile_.size() + discard_pile_.size();
}
