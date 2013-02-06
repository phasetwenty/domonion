/*
 * playerview.h
 *
 *  Created on: Jan 21, 2013
 *      Author: chris
 */

#ifndef DOMONION_PLAYERVIEW_H_
#define DOMONION_PLAYERVIEW_H_

#include <ui/console/cardview.h>
#include <ui/console/infoview.h>
#include <player.h>

class PlayerView {
public:
  PlayerView(const Player& player);
  ~PlayerView();

  void CleanupAndDraw();
  void ItemDown();
  void ItemUp();
  void PlayCard();
  void WindowLeft();
  void WindowRight();

private:
  static const int kWindowHandStartX = 59;
  static const int kWindowHandStartY = 0;
  static const int kWindowTableauStartX = 39;
  static const int kWindowTableauStartY = 0;
  static const int kCardViewCount = 2;

  const Player *player_;

  CardView *card_views_[2];
  CardView *active_;
  InfoView *info_view_;

  void UpdateInfoView();

};

#endif /* DOMONION_PLAYERVIEW_H_ */
