/*
 * handview.cc
 *
 *  Created on: Jan 18, 2013
 *      Author: chris
 */
#include <ui/console/infoview.h>

InfoView::InfoView() {
  window_ = newwin(10, 80, 12, 0);

  keypad(window_, true);
  box(window_, '|', '-');
  wrefresh(window_);
}

void InfoView::Update(std::string text) {
  mvwprintw(window_, 1, 1, text.c_str());
  wrefresh(window_);
}
