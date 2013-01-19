/*
 * infoview.cc
 *
 *  Created on: Jan 18, 2013
 *      Author: chris
 */
#ifndef DOMONION_INFOVIEW_H
#define DOMONION_INFOVIEW_H

#include <ncurses.h>
#include <string>

class InfoView {
public:
  InfoView();

  void Update(std::string text);
private:
  WINDOW *window_;
};

#endif // DOMONION_INFOVIEW_H
