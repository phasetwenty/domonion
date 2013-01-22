
#include <menu.h>
#include <ncurses.h>

#include <cards/basictreasure.h>
#include <cards/basicvictory.h>
#include <player.h>
#include <ui/console/viewport.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

SimpleDeck* InitializeDeck();

int main() {
  std::vector<Player> *players = new std::vector<Player>;
  for (int i = 0; i < 4; ++i) {
    Player *p = new Player(*InitializeDeck());
    players->push_back(*p);
  }
  GameState *game = new GameState(*players);
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
    case 10: {
      /*
       * In example 22 of the menus tutorial:
       * http://tldp.org/HOWTO/NCURSES-Programming-HOWTO/menus.html
       * The example does not use the KEY_ENTER constant to compare the enter key. Why?
       */
      viewport->PlayCard();
      break;
    }
//    default: {
//      break;
//    }
    }
  }

  endwin();
  return 0;
}

SimpleDeck *InitializeDeck() {
  /*
   * Since I just put this deck on the heap, it's my responsibility to
   * deallocate it, right?
   */
  SimpleDeck *d = new SimpleDeck();

  for (int i = 0; i < 7; ++i) {
    BasicTreasure b = BasicTreasure("Copper", 1, 0, "(1)", "Treasure");
    d->Gain(b);
  }
  for (int i = 0; i < 3; ++i) {
    BasicVictory v = BasicVictory("Estate", 2, ")1(", "Victory");
    d->Gain(v);
  }

  return d;
}
