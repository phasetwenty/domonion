/*
 * objectview.h
 *
 *  Created on: Jan 18, 2013
 *      Author: chris
 */
#ifndef DOMONION_CARDVIEW_H
#define DOMONION_CARDVIEW_H

#include <menu.h>
#include <ncurses.h>
#include <string>
#include <vector>

#include <card.h>

class CardView {
public:
  CardView(const std::vector<Card>& items, int window_starty, int window_startx);
  virtual ~CardView() { }

  const std::string Current() const;
  void ItemDown();
  void ItemUp();
  virtual MENU* UpdateMenu(const std::vector<Card>& items);
protected:
  MENU *menu_;
  WINDOW *sub_;
  WINDOW *window_;

  virtual WINDOW* InitializeWindow(int lines,
    int cols,
    int starty,
    int startx);

  /*
   * Helper to convert data structures in the deck to data structures for the
   * menus.
   */
  virtual ITEM **MakeItems(const std::vector<Card> source);
private:
  static const int kMenuLines = 9;
  static const int kMenuCols = 18;
  static const int kMenuStartx = 3;
  static const int kMenuStarty = 1;
  static const int kWindowCols = 20;
  static const int kWindowLines = 12;

};

#endif // DOMONION_CARDVIEW_H
