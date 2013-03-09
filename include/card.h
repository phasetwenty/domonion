#ifndef DOMONION_CARD_H
#define DOMONION_CARD_H

#include <string>

#include <interfaces.h>

namespace domonion {

class GameState;

class Card : public IViewable {
public:
  enum Types { kUndefined = 0, kAction, kCurse, kReaction, kTreasure, kVictory };

  Card(std::string name,
    int cost,
    int initial_supply,
    std::string text,
    int types_count,
    ...);
  ~Card();

  /*
   * Call to play the card. It will modify the game state in the course of
   * resolving.
   */
  virtual void Play(GameState& game) const = 0;
  std::string* Info() const;
  std::string* ToString() const;

  int cost() const;
  int initial_supply() const;
  bool is_action() const;
  std::string const& name() const;
  bool is_treasure() const;
  std::string const& text() const;

  bool operator<(const Card& other) const;
  bool operator==(const Card& other) const;
private:
  /*
   * Cost
   * Essentially an int (probably even something smaller). Peddler, for example, has adjustable
   * cost also consider cards like bridge which changes all cards' costs. May need to change this
   * to something more flexible (such as if introducing Alchemy cards).
   */
  int cost_;

  /*
   * Initial supply count
   * How many of this card should its corresponding supply pile contain?
   */
  int initial_supply_;

  std::string name_;
  /*
   * Card text
   * A description of what the card does.
   *
   * After having messed with the console UI, I can already see there could be use for some
   * formatting. Look into this later.
   */
  std::string text_;

  /*
   * Effect
   * An ordered collection of effect objects. For example, a copper has a + 1 coin effect
   * (which could be indistinguishable from an action's + coin effect).
   */

  /*
   * Reaction
   * Another instance of the effect. Does it need to be separate? I'm on
   * the fence.
   */

  /*
   * Type
   * Types are pretty straightforward. The only thing I can think of right
   * now is that cards can have multiple types. When checking if a card is
   * of a specific type, it should look more like "if <type> is in the
   * types <card> has".
   */
  Types *types_;
  int types_count_;

  /*
   * Subtype
   * This is most important for checking for attacks, but still applies to
   * reactions.
   *
   * Would it make sense to separate the effects into the types? For
   * example, you have your default effect when the card is played. The
   * attack could resolve separately. I think it may also help for
   * checking the card types.
   */

  /*
   * Metadata
   * Some metadata cards need but do not affect gameplay include:
   * * Dominion set
   * * Card categories like Trash and Defenses
   */
  std::string set_;

  Card();
  Card(const Card& other);

  bool is_type(Types t) const;

  Card& operator=(const Card& other);
};

}

#endif // DOMONION_CARD_H
