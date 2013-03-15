/*
 * selector.cc
 *
 *  Created on: Mar 14, 2013
 *      Author: chris
 */

#include <ui/console/selector.h>

namespace domonion {
namespace console {

Selector::Selector(const std::vector<const Card*>& initial_items,
    bool multiselect) : menu_(),
    window_(newwin(kWindowLines, kWindowCols, kWindowStarty, kWindowStartx)) {
  keypad(window_, true);
  box(window_, '|', '-');
  mvwprintw(window_, 1, 1, "Select:");
  wrefresh(window_);

  ITEM **new_items = MakeMenuItems(initial_items);
  menu_ = new_menu(new_items);

  set_menu_format(menu_, kMenuLines, 1);
  set_menu_win(menu_, window_);
  set_menu_sub(menu_,
    derwin(window_, kMenuLines, kMenuCols, kMenuStarty, kMenuStartx));
  set_menu_mark(menu_, "*");
  post_menu(menu_);


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


const std::vector<const Card*>& Selector::GetSelection() {
  std::vector<const Card*> result;

  return result;
}

ITEM** Selector::MakeMenuItems(const std::vector<const Card*>& items) {
  return 0;
}

}
}
