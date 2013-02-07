/*
 * supplypileview.h
 *
 *  Created on: Jan 24, 2013
 *      Author: chris
 */

#ifndef DOMONION_SUPPLYPILEVIEW_H_
#define DOMONION_SUPPLYPILEVIEW_H_

#include <menu.h>
#include <ncurses.h>
#include <vector>

#include <supplypile.h>

class SupplyPileView {
public:
  SupplyPileView(const std::vector<SupplyPile>& piles);
  virtual ~SupplyPileView();

  const SupplyPile& CurrentPile() const;
  int CurrentIndex() const;
  void ItemDown();
  void ItemUp();
  void SetActive();
  void SetInactive();
  virtual void Update();

protected:
  virtual ITEM** MakeMenuItems();

private:
  static const int kColorPairActive = 1;
  static const int kColorPairInactive = 2;

  static const int kMenuLines = 9;
  static const int kMenuCols = 18;
  static const int kMenuStartx = 1;
  static const int kMenuStarty = 1;
  static const int kWindowCols = 20;
  static const int kWindowLines = 12;
  static const int kWindowStartx = 0;
  static const int kWindowStarty = 0;

  const std::vector<SupplyPile>& piles_;

  MENU *menu_;
  WINDOW *window_;

  WINDOW* InitializeWindow(int lines, int cols, int starty, int startx);
};

#endif /* DOMONION_SUPPLYPILEVIEW_H_ */
