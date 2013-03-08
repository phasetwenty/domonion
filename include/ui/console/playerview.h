/*
 * playerview.h
 *
 *  Created on: Feb 26, 2013
 *      Author: chris
 */

#ifndef DOMONION_CONSOLE_PLAYERVIEW_H_
#define DOMONION_CONSOLE_PLAYERVIEW_H_

#include <player.h>

namespace domonion {
namespace console {

class PlayerView {
public:
  PlayerView();
  virtual ~PlayerView();

  void Update(const Player& player);
private:
  static const int kWindowLines = 10;
  static const int kWindowCols = 20;
  static const int kWindowStarty = 12;
  static const int kWindowStartx = 60;

  WINDOW *window_;

  void ReinitializeWindow();

  PlayerView(const PlayerView& other);
  PlayerView& operator=(const PlayerView& other);
};

}
}

#endif /* DOMONION_CONSOLE_PLAYERVIEW_H_ */
