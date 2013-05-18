#include <card.h>
#include <cards/sets/dominion.h>
#include <ui/console/selector.h>

#include <iostream>
#include <unistd.h>
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

  domonion::console::Selector s(cards, 1u, 1u);
  const std::vector<const domonion::Card*> result = s.GetSelection();

  endwin();

  for (std::vector<const domonion::Card*>::const_iterator it = result.begin();
      it != result.end();
      ++it) {
    std::cout << (*it)->name() << std::endl;
  }

  sleep(3u);

  return 0;
}
