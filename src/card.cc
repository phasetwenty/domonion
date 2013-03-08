#include <algorithm>
#include <stdarg.h>
#include <vector>

#include <card.h>
#include <gamestate.h>

domonion::Card::Card(std::string name, int cost, int initial_supply,
    std::string text, int types_count, ...) :
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

domonion::Card::~Card() {
  delete[] types_;
}

std::string* domonion::Card::Info() const {
  return new std::string(text());
}

std::string* domonion::Card::ToString() const {
  return new std::string(name());
}

int domonion::Card::initial_supply() const {
  return initial_supply_;
}

int domonion::Card::cost() const {
  return cost_;
}

bool domonion::Card::is_action() const {
  return is_type(kAction);
}

bool domonion::Card::is_playable(const GameState& game) const {
  bool result = false;
  switch (game.current_phase()) {
  case GameState::kAction: {
    result = is_action();
    break;
  } case GameState::kBuy: {
    result = is_treasure();
    break;
  }
  }
  return result;
}

bool domonion::Card::is_treasure() const {
  return is_type(kTreasure);
}

bool domonion::Card::is_type(Types t) const {
  for (int i = 0; i < types_count_; ++i) {
    if (types_[i] == t) {
      return true;
    }
  }

  return false;
}

const std::string& domonion::Card::name() const {
  return name_;
}

const std::string& domonion::Card::text() const {
  return text_;
}

bool domonion::Card::operator==(const Card& other) const {
  return name() == other.name();
}

bool domonion::Card::operator<(const Card& other) const {
  // TODO: Complete this overload to work in the general case.
  if (is_treasure() && !other.is_treasure()) {
    return true;
  }

  return false;
}
