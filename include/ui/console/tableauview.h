/*
 * tableauview.h
 *
 *  Created on: Jan 18, 2013
 *      Author: chris
 */
#ifndef DOMONION_TABLEAUVIEW_H
#define DOMONION_TABLEAUVIEW_H

#include <card.h>
#include <ui/console/cardview.h>

class TableauView : public CardView {
public:
  TableauView(const std::vector<Card>& tableau) :
      CardView(tableau, kWindowStartY, kWindowStartX) { }

  ~TableauView();

private:
  static const int kWindowStartX = 39;
  static const int kWindowStartY = 0;
};

#endif // DOMONION_TABLEAUVIEW_H
