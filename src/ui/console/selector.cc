/*
 * selector.cc
 *
 *  Created on: Mar 14, 2013
 *      Author: chris
 */

#include <ui/console/selector.h>

namespace domonion {
namespace console {

Selector::Selector(const std::vector<std::string>& initial_items,
    bool multiselect) : menu_(),
    window_(newwin(kWindowLines, kWindowCols, kWindowStarty, kWindowStartx)) {

}

Selector::~Selector() {
  int count = item_count(menu_);
  if (count > 0) {
    ITEM **items = menu_items(menu_);
    for (int i = 0; i < count; ++i) {
      free_item(items[i]);
    }
  }

  free_menu(menu_);
  wclear(window_);
  delwin(window_);
}


std::vector<std::string>& Selector::GetSelection() {
  std::vector<std::string> result;

  return result;
}

ITEM** Selector::MakeMenuItems(const std::vector<std::string>& items) {
  return 0;
}

}
}
