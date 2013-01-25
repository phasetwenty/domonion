/*
 * supplypileview.h
 *
 *  Created on: Jan 24, 2013
 *      Author: chris
 */

#ifndef DOMONION_SUPPLYPILEVIEW_H_
#define DOMONION_SUPPLYPILEVIEW_H_

#include <ncurses.h>

class SupplyPileView {
public:
  SupplyPileView();
  virtual ~SupplyPileView();

private:
  static const int kMenuLines = 9;
  static const int kMenuCols = 18;
  static const int kMenuStartx = 1;
  static const int kMenuStarty = 1;
  static const int kWindowCols = 20;
  static const int kWindowLines = 12;
  static const int kWindowStartx = 0;
  static const int kWindowStarty = 0;

  MENU *menu_;
  WINDOW *window_;
};

#endif /* DOMONION_SUPPLYPILEVIEW_H_ */
