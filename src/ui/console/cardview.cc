/*
 * cardview.cc
 *
 *  Created on: Jan 18, 2013
 *      Author: chris
 */
#include <cstdlib>
#include <cstring>

#include <ui/console/cardview.h>

CardView::CardView(const std::vector<Card>& items,
    int window_starty,
    int window_startx) {
  items_ = &items;
  window_ = InitializeWindow(kWindowLines,
    kWindowCols,
    window_starty,
    window_startx);
  WINDOW *window_sub = derwin(window_,
    kMenuLines,
    kMenuCols,
    kMenuStarty,
    kMenuStartx);
  menu_ = InitializeMenu(window_, window_sub, *items_);
}

MENU* CardView::InitializeMenu(WINDOW *window,
    WINDOW *subwindow,
    std::vector<Card> initialItems) {
  ITEM **items = MakeItems(initialItems);
  MENU *result = new_menu(items);

  set_menu_win(result, window);
  set_menu_sub(result, subwindow);
  set_menu_mark(result, " ");
  post_menu(result);

  return result;
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

const std::vector<Card>& CardView::items() const {
  return *items_;
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

void CardView::set_items(std::vector<Card>& value) {
  // TODO: probably not instant update but some bookkeeping surely.
  items_ = &value;
}

