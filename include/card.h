#ifndef DOMONION_CARD_H
#define DOMONION_CARD_H

#include <string>

class Card {
public:
  Card(std::string name, int cost, std::string text, std::string type);
  ~Card();

  /*
   * Call to play the card. It will modify the game state in the course of
   * resolving.
   */
  void play();

  int cost() const;
  std::string name() const;
  std::string text() const;
private:
  /*
   * Cost
   * Essentially an int (probably even something smaller). Peddler, for example, has adjustable
   * cost also consider cards like bridge which changes all cards' costs. May need to change this
   * to something more flexible (such as if introducing Alchemy cards).
   */
  int cost_;

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
  std::string type_;

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
};

#endif // DOMONION_CARD_H
