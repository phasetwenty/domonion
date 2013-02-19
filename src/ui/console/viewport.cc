/*
 * viewport.cc
 *
 *  Created on: Jan 18, 2013
 *      Author: chris
 */
#include <menu.h>
#include <ncurses.h>
#include <cstdlib>

#include <ui/console/viewport.h>

Viewport::Viewport(GameState *game) : game_(game) {

  initscr();
  keypad(stdscr, TRUE);
  cbreak(); // In case you forget, this disables line buffering.
  noecho(); // Disables terminal echo.
  curs_set(0); // Hides the terminal cursor.
  start_color();
  use_default_colors();  // After activating color, this prevents white-on-gray.

  if (LINES < kMinLines || COLS < kMinCols) {
    printw("This screen is too small!");
    refresh();
    getch();
    endwin();
    exit(1);
  }

  game_->CurrentPlayer().deck().CleanupAndDraw();

  hand_view_ = View(game_->CurrentPlayer().deck().hand_viewable(),
    kWindowHandStartY,
    kWindowHandStartX);
  info_view_ = InfoView();
  supply_view_ = View(game_->supply_piles_viewable(),
    kWindowSupplyStartY,
    kWindowSupplyStartX);
  tableau_view_ = View(game_->CurrentPlayer().deck().tableau_viewable(),
    kWindowTableauStartY,
    kWindowTableauStartX);

  selectable_views_[0] = supply_view_;
  selectable_views_[1] = tableau_view_;
  selectable_views_[2] = hand_view_;

  active_ = &hand_view_;

  // TODO: initialize color pairs game-wide here.
}

Viewport::~Viewport() {
  delete game_;

  endwin();
}

void Viewport::CleanupAndDraw() {
  game_->CurrentPlayer().deck().CleanupAndDraw();

  hand_view_.Update(game_->CurrentPlayer().deck().hand_viewable());
  info_view_.Update(hand_view_.CurrentItem().Info());
}

void Viewport::ItemDown() {
  active_->ItemDown();
  info_view_.Update(active_->CurrentItem().Info());
}

void Viewport::ItemUp() {
  active_->ItemUp();
  info_view_.Update(active_->CurrentItem().Info());
}

void Viewport::PlayCard() {
  game_->CurrentPlayer().deck().Play(hand_view_.CurrentItem().ToString());
  tableau_view_.Update(game_->CurrentPlayer().deck().tableau_viewable());
  hand_view_.Update(game_->CurrentPlayer().deck().hand_viewable());
  info_view_.Update(hand_view_.CurrentItem().Info());
}

void Viewport::WindowLeft() {

}

void Viewport::WindowRight() {

}
