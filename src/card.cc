#include <algorithm>
#include <stdarg.h>
#include <vector>

#include <card.h>
#include <gamestate.h>

Card::Card(std::string name, int cost, int initial_supply, std::string text,
    int types_count, ...) :
    cost_(cost), initial_supply_(initial_supply), name_(name), text_(text),
        types_(), types_count_(types_count) {
  std::vector<Types> types_temp;

  va_list types;
  va_start(types, types_count);
  for (int i = 0; i < types_count; ++i) {
    types_temp.push_back((Types)va_arg(types, int));
  }

  types_ = new Types[types_count];
  std::copy(types_temp.begin(), types_temp.end(), types_);
}

Card::~Card() {
  delete[] types_;
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

bool Card::is_action() const {
  return is_type(kAction);
}

bool Card::is_playable(const GameState& game) const {
  bool result = false;
  switch (game.current_phase()) {
  case Player::kAction: {
    result = is_action();
    break;
  } case Player::kBuy: {
    result = is_treasure();
    break;
  }
  }
  return result;
}

bool Card::is_treasure() const {
  return is_type(kTreasure);
}

bool Card::is_type(Types t) const {
  for (int i = 0; i < types_count_; ++i) {
    if (types_[i] == t) {
      return true;
    }
  }

  return false;
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
