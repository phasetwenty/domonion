#include <ncurses.h>
#include <iostream>
#include <stdlib.h>
#include <vector>

#include <simpledeck.h>

using namespace std;

void initializeScreen();
void printHand(WINDOW *w, SimpleDeck d);

#define MIN_LINES 12
#define MIN_COLS 80

#define HAND_WINDOW_MIN_LINES MIN_LINES
#define HAND_WINDOW_MIN_COLS MIN_COLS / 4

int main() {
	initializeScreen();

	if (LINES < MIN_LINES || COLS < MIN_COLS) {
		printw("This screen is too small!");
		refresh();
		getch();
		endwin();
		exit(1);
	}

	printw("%d rows and %d columns.", LINES, COLS);

	int handWindowLines = HAND_WINDOW_MIN_LINES;
	// Intentional rounding down of this division.
	int handWindowCols = HAND_WINDOW_MIN_COLS;
	if (COLS / 4 > handWindowCols) {
		handWindowCols = COLS / 4;
	}

	WINDOW *handWindow = newwin(handWindowLines,
			handWindowCols,
			0,
			COLS - handWindowCols - 1);
	box(handWindow, 0, 0);
	wrefresh(handWindow);

	SimpleDeck d = SimpleDeck();
	d.gain("Copper");
	d.gain("Copper");
	d.gain("Copper");
	d.gain("Copper");
	d.gain("Copper");
	d.gain("Copper");
	d.gain("Copper");
	d.gain("Estate");
	d.gain("Estate");
	d.gain("Estate");

	char ch = 0;
	while ((ch = getch()) != 'c') {
		d.cleanupAndDraw();
		printHand(handWindow, d);
	}

	endwin();
	return 0;
}

void initializeScreen() {
	initscr();
	cbreak();
	noecho();
}

void printHand(WINDOW *win, SimpleDeck d) {
	werase(win);
	wmove(win, 0, 0);

	vector<string> hand = d.getHand();
	for(vector<string>::iterator it = hand.begin();
			it != hand.end();
			++it) {
		wprintw(win, "%s\n", it->c_str());
	}

	wrefresh(win);
}
