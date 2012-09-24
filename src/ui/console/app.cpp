#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <vector>

#include <menu.h>
#include <ncurses.h>

#include <simpledeck.h>

using namespace std;

void initializeScreen();
SimpleDeck *initializeDeck();
WINDOW* initializeWindow(int lines, int cols, int starty, int startx);
ITEM** makeItems(const vector<string> source);
void updateHandMenu(MENU *menu, SimpleDeck& d);

#define MIN_LINES 12
#define MIN_COLS 80

#define WINDOW_LINES MIN_LINES
#define WINDOW_COLS MIN_COLS / 4

#define HAND_WINDOW_START_Y 0
#define HAND_WINDOW_START_X 59
#define TABLEAU_WINDOW_START_Y 0
#define TABLEAU_WINDOW_START_X 39

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

int main() {
	initializeScreen();
	getch();

	SimpleDeck& deck = *initializeDeck();
	deck.cleanupAndDraw();

	WINDOW *handWindowMain = initializeWindow(WINDOW_LINES,
			WINDOW_COLS,
			HAND_WINDOW_START_Y,
			HAND_WINDOW_START_X);
	WINDOW *handWindowSub = derwin(handWindowMain, 9, 18, 3, 1);
	WINDOW *tableauWindow = initializeWindow(WINDOW_LINES,
			WINDOW_COLS,
			TABLEAU_WINDOW_START_Y,
			TABLEAU_WINDOW_START_X);

	ITEM **initialItems = makeItems(deck.getHand());
	MENU *handMenu = new_menu(initialItems);
	set_menu_win(handMenu, handWindowMain);
	set_menu_sub(handMenu, handWindowSub);

	char ch = 0;
	while ((ch = getch()) != 'c') {
		deck.cleanupAndDraw();
		updateHandMenu(handMenu, deck);
	}

	endwin();
	return 0;
}

/*
 * Helper to convert data structures in the deck to data structures for the
 * menus.
 */
ITEM** makeItems(const vector<string> source) {
	/*
	 * Perhaps there's a way to do this without copies?
	 */
	int numberOfChoices = source.size();
	char **itemStrings = (char**)calloc(numberOfChoices + 1, sizeof(char*));
	for (int i = 0; i < (int)source.size(); ++i) {
		itemStrings[i] = (char*)calloc(source[i].length() + 1, sizeof(char));
		strcpy(itemStrings[i], source[i].c_str());
	}

	ITEM** items = (ITEM **)calloc(numberOfChoices + 1, sizeof(ITEM *));
	for (int i = 0; i < numberOfChoices; ++i) {
		items[i] = new_item(itemStrings[i], NULL);
	}

	return items;
}

SimpleDeck *initializeDeck() {
	/*
	 * Since I just put this deck on the heap, it's my responsibility to
	 * deallocate it, right?
	 */
	SimpleDeck *d = new SimpleDeck();
	for (int i = 0; i < 7; ++i) {
		d->gain("Copper");
	}
	for (int i = 0; i < 3; ++i) {
		d->gain("Estate");
	}

	return d;
}

void initializeScreen() {
	initscr();

	if (LINES < MIN_LINES || COLS < MIN_COLS) {
		printw("This screen is too small!");
		refresh();
		getch();
		endwin();
		exit(1);
	}

	cbreak();  // In case you forget, this disables line buffering.
	noecho();  // Disables terminal echo.
}

WINDOW* initializeWindow(int lines, int cols, int starty, int startx) {
	WINDOW* result = newwin(lines, cols, starty, startx);
	box(result, '|', '-');
	wrefresh(result);
	return result;
}

void updateHandMenu(MENU *menu, SimpleDeck& d) {
	unpost_menu(menu);

	/* Create items */
	ITEM** newItems = makeItems(d.getHand());

	int oldNumberOfChoices = item_count(menu);
	ITEM** oldItems = menu_items(menu);
	for (int i = 0; i < oldNumberOfChoices; ++i) {
		free_item(oldItems[i]);
	}

	set_menu_items(menu, newItems);
	free(oldItems);

	post_menu(menu);
	wrefresh(menu_win(menu));
}
