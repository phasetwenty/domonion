/*
 * debugview.cc
 *
 *  Created on: Mar 12, 2013
 *      Author: chris
 */

#include <ui/console/debugview.h>

namespace domonion {
namespace console {

DebugView::DebugView(int lines, int cols, int starty, int startx) :
  current_items_(), window_(newwin(lines, cols, starty, startx)) {
  ReinitializeWindow();
  wrefresh(window_);
}

DebugView::~DebugView() {
  current_items_.clear();

  wclear(window_);
  wborder(window_, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
  wrefresh(window_);
  delwin(window_);
}

void DebugView::ReinitializeWindow() {
  keypad(window_, true);
  box(window_, '|', '-');
}

void DebugView::Update(const std::vector<const Card*>& cards) {
  wclear(window_);
  ReinitializeWindow();

  current_items_.clear();

  for (std::vector<const Card*>::const_iterator it = cards.begin();
    it != cards.end(); ++it) {
    current_items_.push_back((*it)->ToString());
  }

  for (unsigned i = 0; i < current_items_.size(); ++i) {
    if (i > (unsigned)kWindowLines) {
      break;
    }
    mvwprintw(window_, i + 1, 1, current_items_[i]->c_str());
  }

  wrefresh(window_);
}

} /* namespace console */
} /* namespace domonion */
