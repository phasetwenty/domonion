/*
 * supplypileview.cc
 *
 *  Created on: Jan 24, 2013
 *      Author: chris
 */
#include <cstdlib>
#include <cstring>

#include <ui/console/supplypileview.h>

SupplyPileView::SupplyPileView(const std::vector<SupplyPile>& piles) :
    piles_(piles) {
  window_ = InitializeWindow(kWindowLines,
    kWindowCols,
    kWindowStarty,
    kWindowStartx);

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

SupplyPileView::~SupplyPileView() {
  // TODO Auto-generated destructor stub
}

const SupplyPile& SupplyPileView::CurrentPile() const {
  return piles_[CurrentIndex()];
}

int SupplyPileView::CurrentIndex() const {
  return item_index(current_item(menu_));
}

WINDOW* SupplyPileView::InitializeWindow(int lines,
    int cols,
    int starty,
    int startx) {
  WINDOW *result = newwin(lines, cols, starty, startx);
  keypad(result, true);
  box(result, '|', '-');
  wrefresh(result);
  return result;
}

void SupplyPileView::ItemDown() {
  menu_driver(menu_, REQ_DOWN_ITEM);
  wrefresh(window_);
}

void SupplyPileView::ItemUp() {
  menu_driver(menu_, REQ_UP_ITEM);
  wrefresh(window_);
}

ITEM** SupplyPileView::MakeMenuItems() {
  /*
   * Perhaps there's a way to do this without copies?
   */
  int number_of_choices = piles_.size();
  char **item_strings = (char**) calloc(number_of_choices + 1, sizeof(char*));
  for (int i = 0; i < (int)piles_.size(); ++i) {
    item_strings[i] = (char*) calloc(piles_[i].name().length() + 1,
      sizeof(char));
    sprintf(item_strings[i], "%s (%d)", piles_[i].name().c_str(), piles_[i].count());
  }

  ITEM** items = (ITEM **) calloc(number_of_choices + 1, sizeof(ITEM *));
  for (int i = 0; i < number_of_choices; ++i) {
    items[i] = new_item(item_strings[i], NULL);
  }

  return items;
}

void SupplyPileView::SetActive() {
  set_menu_fore(menu_, COLOR_PAIR(kColorPairActive));
  wrefresh(window_);
}

void SupplyPileView::SetInactive() {
  set_menu_fore(menu_, COLOR_PAIR(kColorPairInactive));
  wrefresh(window_);
}

void SupplyPileView::Update() {
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
