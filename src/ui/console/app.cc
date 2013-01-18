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
#include <gamestate.h>
#include <player.h>

GameState* initializeGame();
void initializeScreen();
SimpleDeck *initializeDeck();
MENU *initializeMenu(WINDOW *window,
  WINDOW *subwindow,
  std::vector<Card> initialItems);
WINDOW *initializeWindow(int lines, int cols, int starty, int startx);
ITEM **makeItems(const std::vector<Card> source);
void playAction(MENU *handMenu, MENU *tableauMenu, SimpleDeck& d);
void updateInfo(WINDOW *info_window, MENU *menu);
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

  SimpleDeck& deck = *initializeDeck();
  deck.cleanup_and_draw();

  WINDOW *hand_window_main = initializeWindow(WINDOW_LINES,
    WINDOW_COLS,
    HAND_WINDOW_START_Y,
    HAND_WINDOW_START_X);
  WINDOW *hand_window_sub = derwin(hand_window_main, 9, 18, 3, 1);

  WINDOW *info_window_main = initializeWindow(10, MIN_COLS, 12, 0);

  WINDOW *tableau_window_main = initializeWindow(WINDOW_LINES,
    WINDOW_COLS,
    TABLEAU_WINDOW_START_Y,
    TABLEAU_WINDOW_START_X);
  WINDOW *tableau_window_sub = derwin(tableau_window_main, 9, 18, 3, 1);

  MENU *hand_menu = initializeMenu(hand_window_main,
    hand_window_sub,
    deck.hand());
  MENU *tableau_menu = initializeMenu(tableau_window_main,
    tableau_window_sub,
    deck.tableau());

  int ch = 0;
  while ((ch = getch()) != 'q') {
    switch (ch) {
    case KEY_DOWN: {
      menu_driver(hand_menu, REQ_DOWN_ITEM);
      wrefresh(hand_window_main);
      updateInfo(info_window_main, hand_menu);
      break;
    }
    case KEY_UP: {
      menu_driver(hand_menu, REQ_UP_ITEM);
      wrefresh(hand_window_main);
      updateInfo(info_window_main, hand_menu);
      break;
    }
    case 10: {
      /*
       * In example 22 of the menus tutorial:
       * http://tldp.org/HOWTO/NCURSES-Programming-HOWTO/menus.html
       * The example does not use the KEY_ENTER constant to compare the enter key. Why?
       */
      const char *name = item_name(current_item(hand_menu));
      deck.play(std::string(name));
      playAction(hand_menu, tableau_menu, deck);
      break;
    }
    default: {
      deck.cleanup_and_draw();
      updateMenu(hand_menu, makeItems(deck.hand()));
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
ITEM **makeItems(const std::vector<Card> source) {
  /*
   * Perhaps there's a way to do this without copies?
   */
  int number_of_choices = source.size();
  char **item_strings = (char**) calloc(number_of_choices + 1, sizeof(char*));
  for (int i = 0; i < (int) source.size(); ++i) {
    item_strings[i] = (char*) calloc(source[i].name().length() + 1,
      sizeof(char));
    strcpy(item_strings[i], source[i].name().c_str());
  }

  ITEM** items = (ITEM **) calloc(number_of_choices + 1, sizeof(ITEM *));
  for (int i = 0; i < number_of_choices; ++i) {
    items[i] = new_item(item_strings[i], NULL);
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

GameState* initializeGame() {
//  std::vector<Player> *players = new std::vector<Player>;
//  for (int i = 0; i < 4; ++i) {
//    Player *p = new Player(*initializeDeck());
//    players->push_back(*p);
//  }
//
//  GameState *result = new GameState(*players);
//  return result;
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
  cbreak(); // In case you forget, this disables line buffering.
  noecho(); // Disables terminal echo.
}

MENU *initializeMenu(WINDOW *window,
    WINDOW *subwindow,
    std::vector<Card> initialItems) {
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

void updateInfo(WINDOW *info_window, MENU *menu) {
  mvwprintw(info_window, 1, 1, item_name(current_item(menu)));
  wrefresh(info_window);
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
