/*
 * playerview.cc
 *
 *  Created on: Feb 26, 2013
 *      Author: chris
 */
#include <ncurses.h>
#include <sstream>

#include <ui/console/playerview.h>

PlayerView::PlayerView() :
    window_(newwin(kWindowLines, kWindowCols, kWindowStarty, kWindowStartx)) {
  ReinitializeWindow();

  wrefresh(window_);
}

PlayerView::~PlayerView() {
  // TODO Auto-generated destructor stub
}

void PlayerView::ReinitializeWindow() {
  keypad(window_, true);
  box(window_, '|', '-');
}

void PlayerView::Update(const Player& player) {
  /*
   * Not well-documented, but
   * ss.str("");
   * clears a stringstream.
   */
  std::stringstream ss;
  ss << player.actions() << " Actions";
  mvwprintw(window_, 1, 1, ss.str().c_str());
  ss.str("");

  ss  << player.buys() << " Buys";
  mvwprintw(window_, 2, 1, ss.str().c_str());
  ss.str("");

  ss  << player.coin() << " Coin";
  mvwprintw(window_, 3, 1, ss.str().c_str());
  wrefresh(window_);
}
