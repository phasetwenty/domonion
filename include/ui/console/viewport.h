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

class Viewport {
public:
  Viewport(GameState *game);
  ~Viewport();

  void CleanupAndDraw();
  void ItemDown();
  void ItemUp();
  void PlayCard();

private:
  static const int kMinLines = 12;
  static const int kMinCols = 80;

  GameState *game_;
  PlayerView *player_view_;
};

#endif /* DOMONION_VIEWPORT_H_ */
