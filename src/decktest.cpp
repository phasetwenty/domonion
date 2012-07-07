/*
 * decktest.cpp
 *
 *  Created on: Jul 6, 2012
 *      Author: chris
 */

#include "../include/simpledeck.h"

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

	d->draw(5);

	return 0;
}
