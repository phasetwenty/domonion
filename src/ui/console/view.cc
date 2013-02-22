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

View::View(std::vector<IViewable*> *initial_items,
    int window_starty,
    int window_startx) : current_items_(initial_items) {
  window_ = InitializeWindow(kWindowLines,
    kWindowCols,
    window_starty,
    window_startx);

  init_pair(kColorPairActive, COLOR_WHITE, COLOR_RED);
  init_pair(kColorPairInactive, COLOR_WHITE, COLOR_BLACK);

  ITEM **new_items = MakeMenuItems();
  menu_ = new_menu(new_items);

  set_menu_win(menu_, window_);
  set_menu_sub(menu_,
    derwin(window_, kMenuLines, kMenuCols, kMenuStarty, kMenuStartx));
  set_menu_mark(menu_, " ");
  post_menu(menu_);

  wrefresh(window_);
}

View::~View() {
  EmptyCurrentItemStrings();

  current_items_->clear();
  delete current_items_;

  int count = item_count(menu_);
  ITEM **items = menu_items(menu_);
  for (int i = 0; i < count; ++i) {
    free_item(items[i]);
  }

  free_menu(menu_);
}

int View::CurrentIndex() const {
  return item_index(current_item(menu_));
}

const IViewable& View::CurrentItem() const {
  return *((*current_items_)[CurrentIndex()]);
}

void View::EmptyCurrentItemStrings() {
  for (std::vector<std::string*>::iterator it = current_item_strings_.begin();
      it != current_item_strings_.end();
      ++it) {
    delete *it;
  }
  current_item_strings_.clear();
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

bool View::IsEmpty() const {
  return current_items_->empty();
}

void View::ItemDown() {
  menu_driver(menu_, REQ_DOWN_ITEM);
  wrefresh(window_);
}

void View::ItemUp() {
  menu_driver(menu_, REQ_UP_ITEM);
  wrefresh(window_);
}

ITEM** View::MakeMenuItems() {
  /*
   * Perhaps there's a way to do this without copies?
   */
  EmptyCurrentItemStrings();

  int number_of_choices = current_items_->size();
  ITEM **result = (ITEM**) calloc(number_of_choices + 1, sizeof(ITEM*));
  for (int i = 0; i < number_of_choices; ++i) {
    std::string *item = (*current_items_)[i]->ToString();
    current_item_strings_.push_back(item);
    result[i] = new_item(item->c_str(), "");
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
  current_items_->clear();
  delete current_items_;
  current_items_ = items;

  ITEM **new_items = MakeMenuItems();

  unpost_menu(menu_);
  ITEM **old_items = menu_items(menu_);
  int count = item_count(menu_);
  for (int i = 0; i < count; ++i) {
    free_item(old_items[i]);
  }

  set_menu_items(menu_, new_items);
  post_menu(menu_);
  wrefresh(window_);
}
