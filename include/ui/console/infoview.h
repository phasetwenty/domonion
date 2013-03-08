/*
 * infoview.cc
 *
 *  Created on: Jan 18, 2013
 *      Author: chris
 */
#ifndef DOMONION_CONSOLE_INFOVIEW_H
#define DOMONION_CONSOLE_INFOVIEW_H

#include <ncurses.h>
#include <interfaces.h>

namespace domonion {
namespace console {


class InfoView {
public:
  InfoView();
  ~InfoView();
  void Update(const IViewable& viewable);
private:
  static const int kWindowLines = 10;
  static const int kWindowCols = 60;
  static const int kWindowStarty = 12;
  static const int kWindowStartx = 0;

  std::string *current_info_;
  WINDOW *window_;

  InfoView(const InfoView& other);
  InfoView& operator=(const InfoView& other);

  void ReinitializeWindow();
};

}
}

#endif // DOMONION_CONSOLE_INFOVIEW_H
