/*
 * playerview.cc
 *
 *  Created on: Jan 21, 2013
 *      Author: chris
 */
#include <ui/console/cardview.h>
#include <ui/console/infoview.h>
#include <ui/console/playerview.h>

PlayerView::PlayerView(const Player& player) :
  player_(&player), info_view_(new InfoView()) {
  /*
   * Hardcoding the hand to be the first view, arbitrarily.
   */
  card_views_[0] = new CardView(player_->deck().hand(),
    kWindowHandStartY,
    kWindowHandStartX);
  card_views_[1] = new CardView(player_->deck().tableau(),
    kWindowTableauStartY,
    kWindowTableauStartX);
  active_ = card_views_[0];
  active_->SetActive();

  card_views_[1]->SetInactive();
  UpdateInfoView();
}

void PlayerView::CleanupAndDraw() {
  player_->deck().CleanupAndDraw();

  for (int i = 0; i < kCardViewCount; ++i) {
    card_views_[i]->Update();
  }

  UpdateInfoView();
}

void PlayerView::ItemDown() {
  active_->ItemDown();
  UpdateInfoView();
}

void PlayerView::ItemUp() {
  active_->ItemUp();
  UpdateInfoView();
}

void PlayerView::PlayCard() {
  player_->deck().Play(active_->CurrentCard().name());

  /*
   * This is an irresponsible hard code but I'm doing it anyway to prototype my
   * idea.
   */
  for (int i = 0; i < kCardViewCount; ++i) {
    card_views_[i]->Update();
  }
  UpdateInfoView();
}

void PlayerView::UpdateInfoView() {
  info_view_->Update(active_->CurrentCard().text());
}

void PlayerView::WindowLeft() {
  if (player_->deck().tableau().size() > 0) {
    if (active_ != card_views_[1]) {
      active_->SetInactive();
    }

    active_ = card_views_[1];
    active_->SetActive();
    UpdateInfoView();
  }
}

void PlayerView::WindowRight() {
  if (player_->deck().hand().size() > 0) {
    if (active_ != card_views_[0]) {
      active_->SetInactive();
    }

    active_ = card_views_[0];
    active_->SetActive();
    UpdateInfoView();
  }
}
