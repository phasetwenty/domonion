#include <card.h>

Card::Card(std::string name,
  int cost,
  int initial_supply,
  std::string text,
  std::string type) :
  cost_(cost), initial_supply_(initial_supply), name_(name), text_(text), type_(type) {
}

Card::~Card() {

}

std::string Card::Info() const {
  return text();
}

bool Card::IsPlayable() const {
  return true;
}

std::string Card::ToString() const {
  return name();
}

int Card::initial_supply() const {
  return initial_supply_;
}

std::string Card::name() const {
  return name_;
}

std::string Card::text() const {
  return text_;
}
