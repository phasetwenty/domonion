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
#include <ui/console/playerview.h>
#include <ui/console/supplypileview.h>

class Viewport {
public:
  Viewport(GameState *game);
  ~Viewport();

  void CleanupAndDraw();
  void ItemDown();
  void ItemUp();
  void PlayCard();

  PlayerView& player_view();
  SupplyPileView& supply_view();

private:
  static const int kMinLines = 12;
  static const int kMinCols = 80;

  GameState *game_;
  SupplyPileView *supply_view_;
  PlayerView *player_view_;
};

#endif /* DOMONION_VIEWPORT_H_ */
