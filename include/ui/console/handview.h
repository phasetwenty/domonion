/*
 * handview.h
 *
 *  Created on: Jan 18, 2013
 *      Author: chris
 */
#ifndef DOMONION_HANDVIEW_H
#define DOMONION_HANDVIEW_H

#include <card.h>
#include <ui/console/cardview.h>

template class std::vector<Card>;

class HandView : public CardView {
public:
  HandView(const std::vector<Card>& hand) :
      CardView(hand, kWindowStartY, kWindowStartX) { }

  ~HandView();

private:
  static const int kWindowStartX = 59;
  static const int kWindowStartY = 0;
};

#endif // DOMONION_HANDVIEW_H
