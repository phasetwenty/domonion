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

Selector::Selector(const std::vector<const Card*>& items,
    unsigned int min_selection,
    unsigned int max_selection) :
    current_item_strings_(), items_(items), max_selection_(max_selection), menu_(),
    min_selection_(min_selection), selection_(),
    window_(newwin(kWindowLines, kWindowCols, kWindowStarty, kWindowStartx)) {
  /*
   * TODO Allow the owner to provide a prompt.
   */
  /*
   * TODO When no selection is needed, don't show the window.
   */
  box(window_, '|', '-');
  mvwprintw(window_, 1, 1, "Select:");

  ITEM **new_items = MakeMenuItems(items_);
  menu_ = new_menu(new_items);

  if (min_selection > 1 || max_selection > 1) {
    menu_opts_off(menu_, O_ONEVALUE);
  }
  set_menu_format(menu_, kMenuLines, 1);
  set_menu_win(menu_, window_);
  set_menu_sub(menu_,
      derwin(window_, kMenuLines, kMenuCols, kMenuStarty, kMenuStartx));
  set_menu_mark(menu_, "*");
  post_menu(menu_);

  wrefresh(window_);
}

Selector::~Selector() {
  /*
   * The cards in selection_ are not owned by the selector, so they are not
   * destroyed.
   */
  for (std::vector<std::string*>::iterator it = current_item_strings_.begin();
      it != current_item_strings_.end();
      ++it) {
    delete *it;
  }

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
  selection_.clear();

  bool done = false;
  int ch = 0;
  while (!done) {
    ch = getch();
    switch (ch) {
    case KEY_DOWN: {
      menu_driver(menu_, REQ_DOWN_ITEM);
      break;
    } case KEY_UP: {
      menu_driver(menu_, REQ_UP_ITEM);
      break;
    }
    case '\r':
    case ' ': {
      menu_driver(menu_, REQ_TOGGLE_ITEM);
      break;
    } case '\t': {
      done = ValidateMenuSelection();
      break;
    }
    }

    wrefresh(window_);
  }

  return selection_;
}

ITEM** Selector::MakeMenuItems(const std::vector<const Card*>& items) {
  int number_of_choices = items.size();
  ITEM **result = (ITEM**) calloc(number_of_choices + 1, sizeof(ITEM*));
  for (int i = 0; i < number_of_choices; ++i) {
    std::string *item = items[i]->ToString();
    current_item_strings_.push_back(item);
    result[i] = new_item(item->c_str(), "");
  }
  return result;
}

bool Selector::ValidateMenuSelection() {
  /*
   * Find out if the state of the menu represents the correct number of selected
   * items.
   */
  ITEM **menu_items = ::menu_items(menu_);
  for (unsigned i = 0; i < items_.size(); ++i) {
    if (item_value(menu_items[i])) {
      selection_.push_back(items_[i]);
    }
  }

  return selection_.size() >= min_selection_ &&
    selection_.size() <= max_selection_;
}

}
}
