/*
 * cardview.cc
 *
 *  Created on: Jan 18, 2013
 *      Author: chris
 */
#include <cstdlib>
#include <cstring>
#include <string>

#include <ui/console/cardview.h>

CardView::CardView(const std::vector<Card>& items,
    int window_starty,
    int window_startx) {
  window_ = InitializeWindow(kWindowLines,
    kWindowCols,
    window_starty,
    window_startx);
  sub_ = derwin(window_,
    kMenuLines,
    kMenuCols,
    kMenuStarty,
    kMenuStartx);
  menu_ = UpdateMenu(items);
}

const std::string CardView::Current() const {
  return std::string(item_description(current_item(menu_)));
}

WINDOW* CardView::InitializeWindow(int lines,
    int cols,
    int starty,
    int startx) {
  WINDOW *result = newwin(lines, cols, starty, startx);
  keypad(result, true);
  box(result, '|', '-');
  wrefresh(result);
  return result;
}

void CardView::ItemDown() {
  menu_driver(menu_, REQ_DOWN_ITEM);
  wrefresh(window_);
}

void CardView::ItemUp() {
  menu_driver(menu_, REQ_UP_ITEM);
  wrefresh(window_);
}

ITEM** CardView::MakeItems(const std::vector<Card> source) {
  /*
   * Perhaps there's a way to do this without copies?
   */
  int number_of_choices = source.size();
  char **item_strings = (char**) calloc(number_of_choices + 1, sizeof(char*));
  for (int i = 0; i < (int) source.size(); ++i) {
    item_strings[i] = (char*) calloc(source[i].name().length() + 1,
      sizeof(char));
    strcpy(item_strings[i], source[i].name().c_str());
  }

  ITEM** items = (ITEM **) calloc(number_of_choices + 1, sizeof(ITEM *));
  for (int i = 0; i < number_of_choices; ++i) {
    items[i] = new_item(item_strings[i], NULL);
  }

  return items;
}

MENU* CardView::UpdateMenu(const std::vector<Card>& items) {
  ITEM **new_items = MakeItems(items);
  MENU *result = new_menu(new_items);

  set_menu_win(result, window_);
  set_menu_sub(result, sub_);
  set_menu_mark(result, " ");
  post_menu(result);

  return result;
}
