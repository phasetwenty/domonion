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
  View(std::vector<IViewable*> *initial_items,
    int window_starty,
    int window_startx);
  virtual ~View();

  const IViewable& CurrentItem() const;
  int CurrentIndex() const;
  bool IsEmpty() const;
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

  std::vector<IViewable*> *current_items_;
  std::vector<std::string*> *current_item_strings_;

  MENU *menu_;
  WINDOW *window_;

  View();
  View(const View& other);
  View& operator=(const View& other);

  void EmptyCurrentItemStrings();

  WINDOW* InitializeWindow(int lines,
    int cols,
    int starty,
    int startx);

  ITEM **MakeMenuItems();


};

#endif // DOMONION_VIEW_H
