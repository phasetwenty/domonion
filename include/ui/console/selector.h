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

class Selector {
public:
  Selector(const std::vector<const Card*>& initial_items, bool multiselect);
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
  MENU *menu_;
  WINDOW *window_;

  Selector();
  Selector(const Selector& other);

  void EmptyCurrentItemStrings();
  ITEM** MakeMenuItems(const std::vector<const Card*>& items);

  Selector& operator=(const Selector& other);
};

} /* namespace console */
} /* namespace domonion */

#endif /* DOMONION_CONSOLE_SELECTOR_H_ */
