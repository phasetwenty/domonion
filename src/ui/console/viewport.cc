/*
 * viewport.cc
 *
 *  Created on: Jan 18, 2013
 *      Author: chris
 */
#include <menu.h>
#include <ncurses.h>

#include <gamestate.h>
#include <ui/console/handview.h>
#include <ui/console/infoview.h>
#include <ui/console/tableauview.h>

class Viewport {
public:
  Viewport(GameState *game) {
    game_ = game;

    hand_view_ = new HandView(game_->CurrentPlayer().deck().hand());
    info_view_ = new InfoView();
    tableau_view_ = new TableauView(game_->CurrentPlayer().deck().tableau());
  }

  ~Viewport() {
    endwin();
  }

  void RunForever() {
/*    int ch = 0;

    while ((ch = getch()) != 'q') {
      switch (ch) {
      case KEY_DOWN: {
        menu_driver(menu_hand_, REQ_DOWN_ITEM);
        wrefresh(window_hand_);
        UpdateInfo();
        break;
      }
      case KEY_UP: {
        menu_driver(menu_hand_, REQ_UP_ITEM);
        wrefresh(hand_window_main);
        UpdateInfo();
        break;
      }
      case 10: {

         * In example 22 of the menus tutorial:
         * http://tldp.org/HOWTO/NCURSES-Programming-HOWTO/menus.html
         * The example does not use the KEY_ENTER constant to compare the enter key. Why?

        const char *name = item_name(current_item(menu_hand_));
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
    }*/
  }

private:
  GameState *game_;
  HandView* hand_view_;
  InfoView *info_view_;
  TableauView *tableau_view_;
};
