/*
 * debugview.h
 *
 *  Created on: Mar 12, 2013
 *      Author: chris
 */

#ifndef DOMONION_CONSOLE_DEBUGVIEW_H_
#define DOMONION_CONSOLE_DEBUGVIEW_H_

#include <ncurses.h>
#include <vector>

#include <card.h>

namespace domonion {
namespace console {

class DebugView {
public:
  DebugView(int lines = kWindowLines, int cols = kWindowCols,
    int starty = kWindowStartY, int startx = kWindowStartX);
  virtual ~DebugView();

  void Update(const std::vector<const Card*>& cards);

private:
  static const int kWindowLines = 22;
  static const int kWindowCols = 20;
  static const int kWindowStartX = 80;
  static const int kWindowStartY = 0;

  std::vector<std::string*> current_items_;
  WINDOW *window_;

  DebugView(const DebugView& other);
  DebugView& operator=(const DebugView& other);

  void ReinitializeWindow();
};

} /* namespace console */
} /* namespace domonion */

#endif /* DOMONION_CONSOLE_DEBUGVIEW_H_ */
