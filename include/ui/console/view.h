/*
 * view.h
 *
 *  Created on: Jan 18, 2013
 *      Author: chris
 */
#ifndef DOMONION_VIEW_H
#define DOMONION_VIEW_H

#include <menu.h>
#include <ncurses.h>
#include <string>
#include <vector>

#include <interfaces.h>

class View {
public:
  View();
  View(const std::vector<IViewable*> *initial_items,
    int window_starty,
    int window_startx);
  virtual ~View() { }

  const IViewable& CurrentItem() const;
  const int CurrentIndex() const;
  void ItemDown();
  void ItemUp();
  void SetActive();
  void SetInactive();
  void Update(std::vector<IViewable*> *items);

private:
  static const int kColorPairActive = 1;
  static const int kColorPairInactive = 2;

  static const int kMenuLines = 9;
  static const int kMenuCols = 18;
  static const int kMenuStartx = 1;
  static const int kMenuStarty = 1;
  static const int kWindowCols = 20;
  static const int kWindowLines = 12;

  const std::vector<IViewable*> *current_items_;

  MENU *menu_;
  WINDOW *window_;

  WINDOW* InitializeWindow(int lines,
    int cols,
    int starty,
    int startx);

  ITEM **MakeMenuItems(const std::vector<IViewable*> *items);
};

#endif // DOMONION_VIEW_H
