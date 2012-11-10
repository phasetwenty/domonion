#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <vector>

#include <menu.h>
#include <ncurses.h>

#include <cards/basictreasure.h>
#include <cards/basicvictory.h>
#include <deck.h>

using namespace std;

void initializeScreen();
SimpleDeck *initializeDeck();
MENU *initializeMenu(WINDOW *window,
		WINDOW *subwindow,
		vector<Card> initialItems);
WINDOW *initializeWindow(int lines, int cols, int starty, int startx);
ITEM **makeItems(const vector<Card> source);
void playAction(MENU *handMenu, MENU *tableauMenu,  SimpleDeck& d);
void updateMenu(MENU *menu, ITEM **newItems);

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
	deck.cleanup_and_draw();

	WINDOW *handWindowMain = initializeWindow(WINDOW_LINES,
			WINDOW_COLS,
			HAND_WINDOW_START_Y,
			HAND_WINDOW_START_X);
	WINDOW *handWindowSub = derwin(handWindowMain, 9, 18, 3, 1);
	WINDOW *tableauWindowMain = initializeWindow(WINDOW_LINES,
			WINDOW_COLS,
			TABLEAU_WINDOW_START_Y,
			TABLEAU_WINDOW_START_X);
	WINDOW *tableauWindowSub = derwin(tableauWindowMain, 9, 18, 3, 1);

	MENU *handMenu = initializeMenu(handWindowMain,
			handWindowSub,
			deck.hand());
	MENU *tableauMenu = initializeMenu(tableauWindowMain,
			tableauWindowSub,
			deck.tableau());

	int ch = 0;
	while ((ch = getch()) != 'q') {
		switch (ch) {
		case KEY_DOWN: {
			menu_driver(handMenu, REQ_DOWN_ITEM);
			wrefresh(handWindowMain);
			break;
		} case KEY_UP: {
			menu_driver(handMenu, REQ_UP_ITEM);
			wrefresh(handWindowMain);
			break;
		} case 10: {
			/*
			 * In example 22 of the menus tutorial:
			 * http://tldp.org/HOWTO/NCURSES-Programming-HOWTO/menus.html
			 * The example does not use the KEY_ENTER constant to compare the enter key. Why?
			 */
			const char *name = item_name(current_item(handMenu));
			deck.play(string(name));
			playAction(handMenu, tableauMenu, deck);
			break;
		} default: {
			deck.cleanup_and_draw();
			updateMenu(handMenu, makeItems(deck.hand()));
			break;
		}
		}
	}

	endwin();
	return 0;
}

/*
 * Helper to convert data structures in the deck to data structures for the
 * menus.
 */
ITEM **makeItems(const vector<Card> source) {
	/*
	 * Perhaps there's a way to do this without copies?
	 */
	int numberOfChoices = source.size();
	char **itemStrings = (char**)calloc(numberOfChoices + 1, sizeof(char*));
	for (int i = 0; i < (int)source.size(); ++i) {
		itemStrings[i] = (char*)calloc(source[i].name().length() + 1, sizeof(char));
		strcpy(itemStrings[i], source[i].name().c_str());
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
      BasicTreasure b = BasicTreasure("Copper", 1, 0, "(1)", "Treasure");
	  d->gain(b);
	}
	for (int i = 0; i < 3; ++i) {
	  BasicVictory v = BasicVictory("Estate", 2, ")1(", "Victory");
	  d->gain(v);
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

	keypad(stdscr, TRUE);
	cbreak();  // In case you forget, this disables line buffering.
	noecho();  // Disables terminal echo.
}

MENU *initializeMenu(WINDOW *window, WINDOW *subwindow, vector<Card> initialItems) {
	ITEM **items = makeItems(initialItems);
	MENU *result = new_menu(items);

	set_menu_win(result, window);
	set_menu_sub(result, subwindow);
	set_menu_mark(result, " ");
	post_menu(result);

	return result;
}

WINDOW *initializeWindow(int lines, int cols, int starty, int startx) {
	WINDOW *result = newwin(lines, cols, starty, startx);
	keypad(result, TRUE);
	box(result, '|', '-');
	wrefresh(result);
	return result;
}

/*
 * Updates the hand and tableau menus. Intended to be called after having played
 * a card.
 */
void playAction(MENU *handMenu, MENU *tableauMenu, SimpleDeck& d) {
	ITEM **newHandItems = makeItems(d.hand());
	updateMenu(handMenu, newHandItems);

	ITEM **newTableauItems = makeItems(d.tableau());
	updateMenu(tableauMenu, newTableauItems);
}

/*
 * Update a menu with new items. The window containing the menu is refreshed.
 */
void updateMenu(MENU *menu, ITEM **newItems) {
	unpost_menu(menu);

	int oldNumberOfChoices = item_count(menu);
	ITEM **oldItems = menu_items(menu);
	for (int i = 0; i < oldNumberOfChoices; ++i) {
		free_item(oldItems[i]);
	}

	set_menu_items(menu, newItems);
	free(oldItems);

	post_menu(menu);
	wrefresh(menu_win(menu));
}
