#include <card.h>
#include <cards/sets/dominion.h>
#include <ui/console/selector.h>
#include <vector>

int main() {
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, true);
  getch();

  std::vector<const domonion::Card*> cards;
  domonion::cards::CouncilRoom *c = new domonion::cards::CouncilRoom;
  domonion::cards::Gardens *g = new domonion::cards::Gardens;
  domonion::cards::Smithy *m = new domonion::cards::Smithy;
  cards.push_back(c);
  cards.push_back(g);
  cards.push_back(m);

  domonion::console::Selector s(cards, false);
  s.GetSelection();

  endwin();
  return 0;
}
