/*
 * BasicVictory.cpp
 *
 *  Created on: Oct 28, 2012
 *      Author: chris
 */

#include <string>

#include <cards/basicvictory.h>

using namespace std;

BasicVictory::BasicVictory(string name, int cost, string text, string type)
  : Card(name, cost, text, type) { }

BasicVictory::~BasicVictory() {
  // TODO Auto-generated destructor stub
}

