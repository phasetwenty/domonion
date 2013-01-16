#include "card.h"

Card::Card(std::string name, int cost, std::string text, std::string type) {
  name_ = name;
  cost_ = cost;
  text_ = text;
  type_ = type;
}

std::string Card::name() const {
  return name_;
}

Card::~Card() {

}
