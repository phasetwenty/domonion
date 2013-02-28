/*
 * handview.cc
 *
 *  Created on: Jan 18, 2013
 *      Author: chris
 */
#include <ui/console/infoview.h>

InfoView::InfoView() : current_info_(new std::string("")),
    window_(newwin(kWindowLines, kWindowCols, kWindowStarty, kWindowStartx)) {
  ReinitializeWindow();
  wrefresh(window_);
}

InfoView::~InfoView() {
  delete current_info_;
}

void InfoView::ReinitializeWindow() {
  keypad(window_, true);
  box(window_, '|', '-');
}

void InfoView::Update(const IViewable& viewable) {
  wclear(window_);
  ReinitializeWindow();

  delete current_info_;
  current_info_ = viewable.Info();

  mvwprintw(window_, 1, 1, current_info_->c_str());
  wrefresh(window_);
}
