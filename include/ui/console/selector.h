/*
 * selector.h
 *
 *  Created on: Mar 14, 2013
 *      Author: chris
 */

#ifndef DOMONION_CONSOLE_SELECTOR_H_
#define DOMONION_CONSOLE_SELECTOR_H_

#include <menu.h>
#include <ncurses.h>

class std::vector<std::string>;

namespace domonion {
namespace console {

class Selector {
public:
  Selector(const std::vector<std::string>& initial_items, bool multiselect);
  ~Selector();

  std::vector<std::string>& GetSelection();

private:
  static const int kMenuCols = 18;
  static const int kMenuLines = 10;
  static const int kMenuStartx = 1;
  static const int kMenuStarty = 1;
  static const int kWindowCols = 20;
  static const int kWindowLines = 12;
  static const int kWindowStartx = 20;
  static const int kWindowStarty = 15;

  MENU *menu_;
  WINDOW *window_;

  Selector();
  Selector(const Selector& other);

  ITEM** MakeMenuItems(const std::vector<std::string>& items);

  Selector& operator=(const Selector& other);
};

} /* namespace console */
} /* namespace domonion */

#endif /* DOMONION_CONSOLE_SELECTOR_H_ */
