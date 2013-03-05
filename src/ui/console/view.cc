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

View::View(std::vector<const IViewable*> *initial_items,
    int window_starty,
    int window_startx) : current_items_(initial_items),
    current_item_strings_(new std::vector<std::string*>),
    window_(newwin(kWindowLines, kWindowCols, window_starty, window_startx)) {
  ReinitializeWindow();

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
  delete current_item_strings_;

  current_items_->clear();
  delete current_items_;

  int count = item_count(menu_);
  ITEM **items = menu_items(menu_);
  for (int i = 0; i < count; ++i) {
    free_item(items[i]);
  }

  unpost_menu(menu_);
  free_menu(menu_);

  wborder(window_, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
  wrefresh(window_);
  delwin(window_);
}

void View::EmptyCurrentItemStrings() {
  for (std::vector<std::string*>::iterator it = current_item_strings_->begin();
      it != current_item_strings_->end();
      ++it) {
    delete *it;
  }
  current_item_strings_->clear();
}

void View::ReinitializeWindow() {
  keypad(window_, true);
  box(window_, '|', '-');
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
    current_item_strings_->push_back(item);
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

void View::Update(std::vector<const IViewable*> *items) {
  unpost_menu(menu_);
  wclear(window_);
  ReinitializeWindow();

  ITEM **old_items = menu_items(menu_);
  int count = item_count(menu_);
  for (int i = 0; i < count; ++i) {
    free_item(old_items[i]);
  }
  current_items_->clear();
  delete current_items_;
  current_items_ = items;

  if (items->size() > 0) {
    ITEM **new_items = MakeMenuItems();

    set_menu_items(menu_, new_items);
    post_menu(menu_);
  }
  wrefresh(window_);
}

int View::current_index() const {
  return item_index(::current_item(menu_));
}

const IViewable& View::current_item() const {
  return *((*current_items_)[current_index()]);
}
