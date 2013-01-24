#include <card.h>

Card::Card(std::string name,
    int cost,
    int initial_supply,
    std::string text,
    std::string type) {
  name_ = name;
  cost_ = cost;
  initial_supply_ = initial_supply;
  text_ = text;
  type_ = type;
}

Card::~Card() {

}

std::string Card::name() const {
  return name_;
}

std::string Card::text() const {
  return text_;
}
