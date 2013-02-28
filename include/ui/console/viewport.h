/*
 * viewport.h
 *
 *  Created on: Jan 21, 2013
 *      Author: chris
 */

#ifndef DOMONION_VIEWPORT_H_
#define DOMONION_VIEWPORT_H_
/*
 * viewport.cc
 *
 *  Created on: Jan 18, 2013
 *      Author: chris
 */
#include <menu.h>
#include <ncurses.h>

#include <gamestate.h>
#include <ui/console/infoview.h>
#include <ui/console/playerview.h>
#include <ui/console/view.h>

class Viewport {
public:
  Viewport(GameState *game);
  ~Viewport();

  void CleanupAndDraw();
  void Execute();
  void ItemDown();
  void ItemUp();
  void PlayCard();
  void WindowLeft();
  void WindowRight();

private:
  static const int kMinLines = 12;
  static const int kMinCols = 80;
  static const int kSelectableViewCount = 3;
  static const int kWindowHandStartX = 59;
  static const int kWindowHandStartY = 0;
  static const int kWindowSupplyStartX = 0;
  static const int kWindowSupplyStartY = 0;
  static const int kWindowTableauStartX = 39;
  static const int kWindowTableauStartY = 0;

  int active_index_;
  GameState *game_;
  View *hand_view_;
  InfoView info_view_;
  PlayerView player_view_;
  View *selectable_views_[kSelectableViewCount];
  View *supply_view_;
  View *tableau_view_;

  Viewport();
  Viewport(const Viewport& other);
  Viewport& operator=(const Viewport& other);
};

#endif /* DOMONION_VIEWPORT_H_ */
