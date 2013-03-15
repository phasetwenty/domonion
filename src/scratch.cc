#include <card.h>
#include <cards/sets/dominion.h>
#include <ui/console/selector.h>
#include <vector>

int main() {
  initscr();
  cbreak();
  noecho();
  getch();

  std::vector<const domonion::Card*> cards;
  domonion::cards::CouncilRoom *c = new domonion::cards::CouncilRoom;
  cards.push_back(c);

  domonion::console::Selector s(cards, false);
  getch();

  endwin();
  return 0;
}
