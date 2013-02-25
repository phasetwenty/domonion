/*
 * basictreasure.cc
 *
 *  Created on: Oct 10, 2012
 *      Author: chris
 */

#include <cards/basictreasure.h>

BasicTreasure::BasicTreasure(std::string name,
    int coin_provided,
    int cost,
    int initial_supply,
    std::string text,
    std::string type) :
    Card(name, cost, initial_supply, text, type),
    coin_provided_(coin_provided) {}

BasicTreasure::~BasicTreasure() {

}

int BasicTreasure::coin_provided() const {
  return coin_provided_;
}
