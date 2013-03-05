#include <iostream>
#include <menu.h>
#include <ncurses.h>
#include <sstream>

#include <cards/basictreasure.h>
#include <cards/basicvictory.h>
#include <cards/genericcard.h>
#include <player.h>
#include <ui/console/viewport.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

int main() {
  /*
   * This pair of statements is to pause the game so that the debugger can be
   * attached.
   */
  initscr();
  getch();

  GameState *g = new GameState(4);
  g->Start();
  Viewport *viewport = new Viewport(g);

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
    }

    if (g->is_ended()) {
      delete viewport;

      mvprintw(1, 1, "Scores!");

      std::stringstream ss;
      int line_no = 2;
      for (std::vector<Player*>::const_iterator it = g->players().begin();
          it != g->players().end();
          ++it) {
        ss.str("");
        ss << (*it)->name() << ": " << (*it)->victory_points();
        mvprintw(line_no++, 1, ss.str().c_str());
      }
      getch();
    }
  }

  endwin();
  return 0;
}
