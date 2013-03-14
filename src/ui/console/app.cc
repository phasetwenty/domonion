#include <iostream>
#include <menu.h>
#include <ncurses.h>
#include <sstream>

#include <cardbank.h>
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

  domonion::GameState *g = new domonion::GameState(2);

  domonion::CardBank b(2);
  g->InitializeBaseSupply(b);
  std::vector<domonion::Card*> *cards = b.Selection();
  for (std::vector<domonion::Card*>::const_iterator it = cards->begin();
      it != cards->end();
      ++it) {
    g->AddToSupply(*it);
  }
  g->Start();
  domonion::console::Viewport *viewport = new domonion::console::Viewport(g);

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
    case 9: {
      viewport->SkipPhase();
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
      for (unsigned i = 0; i < g->players().size(); ++i) {
        const domonion::Player& player = g->current_player();
        ss.str("");
        ss << player.name() << ": " << player.victory_points(*g);
        mvprintw(line_no++, 1, ss.str().c_str());

        g->NextPlayer();
      }
      getch();
    }
  }

  endwin();
  return 0;
}
