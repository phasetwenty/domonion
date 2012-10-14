/*
 * basictreasure.cc
 *
 *  Created on: Oct 10, 2012
 *      Author: chris
 */

#include <basictreasure.h>

using namespace std;

BasicTreasure::BasicTreasure(string name, int coin_provided, int cost,
                             string text, string type)
    : Card(name, cost, text, type) {
  coin_provided_ = coin_provided;
}

BasicTreasure::~BasicTreasure() {

}

int BasicTreasure::coin_provided() const {
  return coin_provided_;
}
