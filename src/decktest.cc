/*
 * decktest.cpp
 *
 *  Created on: Jul 6, 2012
 *      Author: chris
 */

#include "../include/simpledeck.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std;

int main() {
	SimpleDeck* d = new SimpleDeck();

	d->gain("Copper");
	d->gain("Copper");
	d->gain("Copper");
	d->gain("Copper");
	d->gain("Copper");
	d->gain("Copper");
	d->gain("Copper");
	d->gain("Estate");
	d->gain("Estate");
	d->gain("Estate");

	d->cleanupAndDraw();

	return 0;
}
