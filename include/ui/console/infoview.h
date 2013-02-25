/*
 * infoview.cc
 *
 *  Created on: Jan 18, 2013
 *      Author: chris
 */
#ifndef DOMONION_INFOVIEW_H
#define DOMONION_INFOVIEW_H

#include <ncurses.h>
#include <interfaces.h>

class InfoView {
public:
  InfoView();
  ~InfoView();
  void Update(const IViewable& viewable);
private:
  std::string *current_info_;
  WINDOW *window_;

  InfoView(const InfoView& other);
  InfoView& operator=(const InfoView& other);

  void ReinitializeWindow();
};

#endif // DOMONION_INFOVIEW_H
