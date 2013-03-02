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

Viewport::Viewport(GameState *game) :
    game_(game), info_view_(), player_view_() {
  initscr();
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

  game_->current_deck().CleanupAndDraw();

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

  player_view_.Update(game_->current_player());
  // TODO: initialize color pairs game-wide here.
}

Viewport::~Viewport() {
  delete game_;

  for (int i = 0; i < kSelectableViewCount; ++i) {
    View *item = selectable_views_[i];
    delete item;
  }

  endwin();
}

void Viewport::CleanupAndDraw() {
  game_->current_deck().CleanupAndDraw();

  Update(2, hand_view_, tableau_view_);
}

void Viewport::Execute() {
  if (selectable_views_[active_index_] == hand_view_) {
    PlayCard();
  } else if (selectable_views_[active_index_] == supply_view_) {
    const SupplyPile& pile = supply_view_->current_item_as<SupplyPile>();
    game_->Buy(pile.name());

    supply_view_->Update(game_->supply_piles_viewable());
    supply_view_->SetInactive();

    active_index_ = kSelectableViewCount - 1;
    hand_view_->SetActive();

    Update(0);
  }
}

void Viewport::ItemDown() {
  selectable_views_[active_index_]->ItemDown();
  Update(0);
}

void Viewport::ItemUp() {
  selectable_views_[active_index_]->ItemUp();
  Update(0);
}

void Viewport::PlayCard() {
  const Card& card = hand_view_->current_item_as<Card>();
  game_->current_deck().Play(card);
  card.Play(*game_);

  Update(2, hand_view_, tableau_view_);
}

void Viewport::Update(int count, ...) {
  info_view_.Update(active_view()->current_item());
  player_view_.Update(game_->current_player());

  va_list views;
  va_start(views, count);

  for (int i = 0; i < count; ++i) {
    View *view = va_arg(views, View*);
    if (view == hand_view_) {
      hand_view_->Update(game_->current_deck().hand_viewable());
    } else if (view == supply_view_) {
      supply_view_->Update(game_->supply_piles_viewable());
    } else if (view == tableau_view_) {
      tableau_view_->Update(game_->current_deck().tableau_viewable());
    }
  }
  va_end(views);
}

void Viewport::WindowLeft() {
  if (active_index_ > 0 && !selectable_views_[active_index_ - 1]->IsEmpty()) {
    active_view()->SetInactive();
    active_index_--;
    active_view()->SetActive();
    Update(0);
  }
}

void Viewport::WindowRight() {
  if (active_index_ < kSelectableViewCount - 1
    && !selectable_views_[active_index_ + 1]->IsEmpty()) {
    active_view()->SetInactive();
    active_index_++;
    active_view()->SetActive();
    Update(0);
  }
}

View* Viewport::active_view() const {
  return selectable_views_[active_index_];
}
