/*
 * cardview.cc
 *
 *  Created on: Jan 18, 2013
 *      Author: chris
 */
#include <cstdlib>
#include <cstring>
#include <string>

#include <ui/console/view.h>

View::View() { }

View::View(const std::vector<IViewable*> *initial_items,
    int window_starty,
    int window_startx) : current_items_(initial_items) {
  window_ = InitializeWindow(kWindowLines,
    kWindowCols,
    window_starty,
    window_startx);

  init_pair(kColorPairActive, COLOR_WHITE, COLOR_RED);
  init_pair(kColorPairInactive, COLOR_WHITE, COLOR_BLACK);

  ITEM **new_items = MakeMenuItems(current_items_);
  menu_ = new_menu(new_items);

  set_menu_win(menu_, window_);
  set_menu_sub(menu_,
    derwin(window_, kMenuLines, kMenuCols, kMenuStarty, kMenuStartx));
  set_menu_mark(menu_, " ");
  post_menu(menu_);

  wrefresh(window_);
}


const int View::CurrentIndex() const {
  return item_index(current_item(menu_));
}

WINDOW* View::InitializeWindow(int lines,
    int cols,
    int starty,
    int startx) {
  WINDOW *result = newwin(lines, cols, starty, startx);
  keypad(result, true);
  box(result, '|', '-');
  wrefresh(result);
  return result;
}

void View::ItemDown() {
  menu_driver(menu_, REQ_DOWN_ITEM);
  wrefresh(window_);
}

void View::ItemUp() {
  menu_driver(menu_, REQ_UP_ITEM);
  wrefresh(window_);
}

ITEM** View::MakeMenuItems(const std::vector<IViewable*> *items) {
  /*
   * Perhaps there's a way to do this without copies?
   */
  int number_of_choices = items->size();
  char **item_strings = (char**) calloc(number_of_choices + 1, sizeof(char*));
  for (int i = 0; i < (int) items->size(); ++i) {
    item_strings[i] = (char*) calloc((*items)[i]->ToString().length() + 1,
      sizeof(char));
    strcpy(item_strings[i], (*items)[i]->ToString().c_str());
  }

  ITEM** result = (ITEM **) calloc(number_of_choices + 1, sizeof(ITEM *));
  for (int i = 0; i < number_of_choices; ++i) {
    result[i] = new_item(item_strings[i], NULL);
  }

  return result;
}

void View::SetActive() {
  set_menu_fore(menu_, COLOR_PAIR(kColorPairActive));
  wrefresh(window_);
}

void View::SetInactive() {
  set_menu_fore(menu_, COLOR_PAIR(kColorPairInactive));
  wrefresh(window_);
}

void View::Update(std::vector<IViewable*> *items) {
  ITEM **new_items = MakeMenuItems(items);

  unpost_menu(menu_);
  ITEM **old_items = menu_items(menu_);
  int count = item_count(menu_);
  for (int i = 0; i < count; ++i) {
    free_item(old_items[i]);
  }

  set_menu_items(menu_, new_items);
  post_menu(menu_);
  wrefresh(window_);

  while (!items->empty()) {
    delete items->back();
    items->pop_back();
  }
}
