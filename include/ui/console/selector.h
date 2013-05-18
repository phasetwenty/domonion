/*
 * selector.h
 *
 *  Created on: Mar 14, 2013
 *      Author: chris
 */

#ifndef DOMONION_CONSOLE_SELECTOR_H_
#define DOMONION_CONSOLE_SELECTOR_H_

#include <card.h>

#include <menu.h>
#include <ncurses.h>
#include <vector>

namespace domonion {
namespace console {

/*
 * Designed prompt the user to select items in a list (such as Cards or
 * SupplyPiles) and return the selection to the owner.
 */
class Selector {
public:
  static const int kSelectAll = -1;

  /*
   * TODO Currently expects a container of cards, but it should be easily
   * replaced with the IViewable interface once initial development is done.
   */
  Selector(const std::vector<const Card*>& items,
    unsigned int min_selection,
    unsigned int max_selection);
  ~Selector();

  const std::vector<const Card*>& GetSelection();

private:
  static const int kMenuCols = 18;
  static const int kMenuLines = 10;
  static const int kMenuStartx = 1;
  static const int kMenuStarty = 2;
  static const int kWindowCols = 20;
  static const int kWindowLines = 12;
  static const int kWindowStartx = 30;
  static const int kWindowStarty = 5;

  std::vector<std::string*> current_item_strings_;
  const std::vector<const Card*>& items_;
  unsigned int max_selection_;
  MENU *menu_;
  unsigned int min_selection_;
  std::vector<const Card*> selection_;
  WINDOW *window_;

  Selector();
  Selector(const Selector& other);

  ITEM** MakeMenuItems(const std::vector<const Card*>& items);
  bool ValidateMenuSelection();

  Selector& operator=(const Selector& other);
};

} /* namespace console */
} /* namespace domonion */

#endif /* DOMONION_CONSOLE_SELECTOR_H_ */
