#include <iostream>

#include <menu.h>
#include <ncurses.h>

#include <cards/basictreasure.h>
#include <cards/basicvictory.h>
#include <cards/genericcard.h>
#include <player.h>
#include <ui/console/viewport.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

std::vector<SupplyPile*>* InitializeSupply();

int main() {
  /*
   * This pair of statements is to pause the game so that the debugger can be
   * attached.
   */
  initscr();
  getch();

  std::vector<SupplyPile*> *piles = InitializeSupply();
  GameState *game = new GameState(4, piles);

  Viewport *viewport = new Viewport(game);

  int ch = 0;
  while ((ch = getch()) != 'q') {
    switch (ch) {
    case KEY_DOWN: {
      viewport->ItemDown();
      break;
    }
    case KEY_UP: {
      viewport->ItemUp();
      break;
    }
    case KEY_LEFT: {
      viewport->WindowLeft();
      break;
    }
    case KEY_RIGHT: {
      viewport->WindowRight();
      break;
    }
    case 10: {
      /*
       * In example 22 of the menus tutorial:
       * http://tldp.org/HOWTO/NCURSES-Programming-HOWTO/menus.html
       * The example does not use the KEY_ENTER constant to compare the enter key. Why?
       */
      viewport->Execute();
      break;
    }
    default: {
      viewport->CleanupAndDraw();
      break;
    }
    }
  }

  delete viewport;
  return 0;
}

std::vector<SupplyPile*>* InitializeSupply() {
  // Let's initialize Estates, Coppers, Chapels and Chancellors.
  std::vector<SupplyPile*> *result = new std::vector<SupplyPile*>;

  Card *estate = new BasicVictory("Estate", 2, 24, ")1(");
  Card *copper = new BasicTreasure("Copper", 1, 0, 60, "(1)");
  Card *chapel = new GenericCard("Chapel", 2, 10, "Chapel 4 cards", "type");
  Card *chancellor = new GenericCard("Chancellor", 2, 10, "(2) Chancellor effect", "type");

  result->push_back(new SupplyPile(estate));
  result->push_back(new SupplyPile(copper));
  result->push_back(new SupplyPile(chapel));
  result->push_back(new SupplyPile(chancellor));

  return result;
}
