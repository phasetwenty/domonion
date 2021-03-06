/*
 * handview.cc
 *
 *  Created on: Jan 18, 2013
 *      Author: chris
 */
#include <ui/console/infoview.h>

namespace domonion {
namespace console {

InfoView::InfoView(int lines, int cols, int starty, int startx) :
  current_info_(new std::string("")), window_(newwin(lines, cols, starty, startx)) {
  ReinitializeWindow();
  wrefresh(window_);
}

InfoView::~InfoView() {
  delete current_info_;

  wclear(window_);
  wborder(window_, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
  wrefresh(window_);
  delwin(window_);
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

}
}
