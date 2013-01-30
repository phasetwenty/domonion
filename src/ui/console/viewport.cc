/*
 * viewport.cc
 *
 *  Created on: Jan 18, 2013
 *      Author: chris
 */
#include <menu.h>
#include <ncurses.h>
#include <cstdlib>

#include <gamestate.h>
#include <ui/console/playerview.h>
#include <ui/console/viewport.h>

Viewport::Viewport(GameState *game) {
  game_ = game;

  initscr();
  keypad(stdscr, TRUE);
  cbreak(); // In case you forget, this disables line buffering.
  noecho(); // Disables terminal echo.
  curs_set(0); // Hides the terminal cursor.
  start_color();
  getch();

  if (LINES < kMinLines || COLS < kMinCols) {
    printw("This screen is too small!");
    refresh();
    getch();
    endwin();
    exit(1);
  }

  game_->players()->current().deck().CleanupAndDraw();
  player_view_ = new PlayerView(game_->players()->current());
}

Viewport::~Viewport() {
  endwin();
}

void Viewport::CleanupAndDraw() {
  player_view_->CleanupAndDraw();
}

void Viewport::ItemDown() {
  player_view_->ItemDown();
}

void Viewport::ItemUp() {
  player_view_->ItemUp();
}

void Viewport::PlayCard() {
  player_view_->PlayCard();
}

PlayerView& Viewport::player_view() const {
  return *player_view_;
}
