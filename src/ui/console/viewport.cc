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

  player_view_ = new PlayerView(game_->players()->current());

  initscr();

  if (LINES < kMinLines || COLS < kMinCols) {
    printw("This screen is too small!");
    refresh();
    getch();
    endwin();
    exit(1);
  }

  keypad(stdscr, TRUE);
  cbreak(); // In case you forget, this disables line buffering.
  noecho(); // Disables terminal echo.
}

Viewport::~Viewport() {
  endwin();
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
