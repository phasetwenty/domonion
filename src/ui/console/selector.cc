/*
 * selector.cc
 *
 *  Created on: Mar 14, 2013
 *      Author: chris
 */

#include <cstdlib>

#include <ui/console/selector.h>

namespace domonion {
namespace console {

Selector::Selector(const std::vector<const Card*>& initial_items,
    bool multiselect) : current_item_strings_(), menu_(),
    window_(newwin(kWindowLines, kWindowCols, kWindowStarty, kWindowStartx)) {
  keypad(window_, true);
  box(window_, '|', '-');
  mvwprintw(window_, 1, 1, "Select:");

  ITEM **new_items = MakeMenuItems(initial_items);
  menu_ = new_menu(new_items);

  set_menu_format(menu_, kMenuLines, 1);
  set_menu_win(menu_, window_);
  set_menu_sub(menu_,
    derwin(window_, kMenuLines, kMenuCols, kMenuStarty, kMenuStartx));
  set_menu_mark(menu_, "*");
  post_menu(menu_);

  wrefresh(window_);
}

Selector::~Selector() {
  int count = item_count(menu_);
  if (count > 0) {
    ITEM **items = menu_items(menu_);
    for (int i = 0; i < count; ++i) {
      free_item(items[i]);
    }
  }

  EmptyCurrentItemStrings();

  free_menu(menu_);
  wclear(window_);
  delwin(window_);
}

void Selector::EmptyCurrentItemStrings() {
  for (std::vector<std::string*>::iterator it = current_item_strings_.begin();
      it != current_item_strings_.end();
      ++it) {
    delete *it;
  }
  current_item_strings_.clear();
}

const std::vector<const Card*>& Selector::GetSelection() {
  std::vector<const Card*> result;

  return result;
}

ITEM** Selector::MakeMenuItems(const std::vector<const Card*>& items) {
  EmptyCurrentItemStrings();

  int number_of_choices = items.size();
  ITEM **result = (ITEM**) calloc(number_of_choices + 1, sizeof(ITEM*));
  for (int i = 0; i < number_of_choices; ++i) {
    std::string *item = items[i]->ToString();
    current_item_strings_.push_back(item);
    result[i] = new_item(item->c_str(), "");
  }
  return result;
}

}
}
