#include <card.h>

Card::Card(std::string name,
  int cost,
  int initial_supply,
  std::string text,
  std::string type) :
  cost_(cost), initial_supply_(initial_supply), name_(name), text_(text), type_(type) {
}

std::string* Card::Info() const {
  return new std::string(text());
}

std::string* Card::ToString() const {
  return new std::string(name());
}

int Card::initial_supply() const {
  return initial_supply_;
}

int Card::cost() const {
  return cost_;
}

bool Card::is_playable() const {
  return true;
}

const std::string& Card::name() const {
  return name_;
}

const std::string& Card::text() const {
  return text_;
}

bool Card::operator==(const Card& other) {
  return name() == other.name();
}
