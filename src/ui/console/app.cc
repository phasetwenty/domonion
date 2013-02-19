#include <iostream>


#include <menu.h>
#include <ncurses.h>

#include <cards/basictreasure.h>
#include <cards/basicvictory.h>
#include <player.h>
#include <ui/console/viewport.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

SimpleDeck* InitializeDeck();

int main() {
  /*
   * This pair of statements is to pause the game so that the debugger can be
   * attached.
   */
  initscr();
  getch();

  std::vector<Player*> *players = new std::vector<Player*>;
  for (int i = 0; i < 4; ++i) {
    Player *p = new Player(*InitializeDeck());
    players->push_back(p);
  }

  Card *chapel = new Card("Chapel", 2, 10, "Chapel 4 cards", "type");
  Card *chancellor = new Card("Chancellor", 2, 10, "(2) Chancellor effect", "type");

  std::vector<SupplyPile*> *piles = new std::vector<SupplyPile*>;
  piles->push_back(new SupplyPile(chapel, chapel->initial_supply()));
  piles->push_back(new SupplyPile(chancellor, chancellor->initial_supply()));

  GameState *game = new GameState(players, piles);
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
      viewport->PlayCard();
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

SimpleDeck *InitializeDeck() {
  /*
   * Since I just put this deck on the heap, it's my responsibility to
   * deallocate it, right?
   */
  SimpleDeck *d = new SimpleDeck();

  for (int i = 0; i < 7; ++i) {
    BasicTreasure *b =  new BasicTreasure("Copper", 1, 0, 10, "(1)", "Treasure");
    d->Gain(b);
  }
  for (int i = 0; i < 3; ++i) {
    BasicVictory *v =  new BasicVictory("Estate", 2, 10, ")1(", "Victory");
    d->Gain(v);
  }

  return d;
}
