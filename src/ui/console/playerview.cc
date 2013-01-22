/*
 * playerview.cc
 *
 *  Created on: Jan 21, 2013
 *      Author: chris
 */
#include <ui/console/cardview.h>
#include <ui/console/infoview.h>
#include <ui/console/playerview.h>

PlayerView::PlayerView(const Player& player) {
  player_ = &player;

  hand_view_ = new CardView(player_->deck().hand(),
    kWindowHandStartY,
    kWindowHandStartX);
  info_view_ = new InfoView();
  tableau_view_ = new CardView(player_->deck().tableau(),
    kWindowTableauStartY,
    kWindowTableauStartX);
}

void PlayerView::ItemDown() {
  hand_view_->ItemDown();
}

void PlayerView::ItemUp() {
  hand_view_->ItemUp();
}

void PlayerView::PlayCard() {
  player_->deck().Play(hand_view_->Current());

  hand_view_->UpdateMenu(player_->deck().hand());
  tableau_view_->UpdateMenu(player_->deck().tableau());
}
