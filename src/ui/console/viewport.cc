/*
 * viewport.cc
 *
 *  Created on: Jan 18, 2013
 *      Author: chris
 */
#include <cstdlib>
#include <menu.h>
#include <ncurses.h>
#include <stdarg.h>

#include <ui/console/viewport.h>

namespace domonion {
namespace console {

Viewport::Viewport(GameState *game) :
    game_(game), info_view_(), player_view_() {
  keypad(stdscr, TRUE);
  cbreak(); // In case you forget, this disables line buffering.
  noecho(); // Disables terminal echo.
  curs_set(0); // Hides the terminal cursor.
  start_color();
  use_default_colors(); // After activating color, this prevents white-on-gray.

  if (LINES < kMinLines || COLS < kMinCols) {
    printw("This screen is too small!");
    refresh();
    getch();
    endwin();
    exit(1);
  }

  hand_view_ = new View(game_->current_deck().hand_viewable(),
    kWindowHandStartY,
    kWindowHandStartX);
  supply_view_ = new View(game_->supply_piles_viewable(),
    kWindowSupplyStartY,
    kWindowSupplyStartX);
  tableau_view_ = new View(game_->current_deck().tableau_viewable(),
    kWindowTableauStartY,
    kWindowTableauStartX);

  selectable_views_[0] = supply_view_;
  selectable_views_[1] = tableau_view_;
  selectable_views_[2] = hand_view_;

  supply_view_->SetInactive();
  tableau_view_->SetInactive();

  hand_view_->SetActive();
  active_index_ = 2;

  info_view_.Update(active_view()->current_item());
  player_view_.Update(game_->current_player());
  // TODO: initialize color pairs game-wide here.
}

Viewport::~Viewport() {
  for (int i = 0; i < kSelectableViewCount; ++i) {
    View *item = selectable_views_[i];
    delete item;
  }
}

void Viewport::ChangeActive(int view_index) {
  active_view()->SetInactive();
  active_index_ = view_index;
  active_view()->SetActive();

  UpdateMinor();
}

void Viewport::Execute() {
  if (!active_view()->IsEmpty()) {
    if (active_view() == hand_view_) {
      const Card& card = hand_view_->current_item_as<Card>();
      game_->PlayCard(card);

    } else if (active_view() == supply_view_) {
      const SupplyPile& pile = supply_view_->current_item_as<SupplyPile>();
      game_->Buy(pile.name());

      supply_view_->Update(game_->supply_piles_viewable());
      supply_view_->SetInactive();

      active_index_ = kSelectableViewCount - 1;
      hand_view_->SetActive();
    }

    UpdateAll();
    while (active_view()->IsEmpty()) {
      ChangeActive(active_index_ - 1);
    }
  }
}

void Viewport::ItemDown() {
  if (!active_view()->IsEmpty()) {
    active_view()->ItemDown();
    UpdateMinor();
  }
}

void Viewport::ItemUp() {
  if (!active_view()->IsEmpty()) {
    active_view()->ItemUp();
    UpdateMinor();
  }
}

void Viewport::SkipPhase() {
  game_->ChangePhase(true);
  UpdateAll();
}

void Viewport::UpdateAll() {
  UpdateInfoView();
  player_view_.Update(game_->current_player());

  hand_view_->Update(game_->current_deck().hand_viewable());
  supply_view_->Update(game_->supply_piles_viewable());
  tableau_view_->Update(game_->current_deck().tableau_viewable());
}

void Viewport::UpdateInfoView() {
  if (!active_view()->IsEmpty()) {
    info_view_.Update(active_view()->current_item());
  }
}

void Viewport::UpdateMinor() {
  /*
   * This method currently only updates the InfoView, but I believe that will
   * change as development moves forward.
   */
  UpdateInfoView();
}

void Viewport::WindowLeft() {
  if (active_index_ > 0 && !selectable_views_[active_index_ - 1]->IsEmpty()) {
    ChangeActive(active_index_ - 1);
  }
}

void Viewport::WindowRight() {
  if (active_index_ < kSelectableViewCount - 1
    && !selectable_views_[active_index_ + 1]->IsEmpty()) {
    ChangeActive(active_index_ + 1);
  }
}

View* Viewport::active_view() const {
  return selectable_views_[active_index_];
}

}
}
