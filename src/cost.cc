#include "include/cost.h"

Cost::Cost(int defaultCost, int (Cost::*costFunction)(GameState&)) {
    this->defaultCost = defaultCost;
    this->costFunction = costFunction;
}

int Cost::get(GameState& gameState) {
    return (*this.*costFunction)(gameState);
}

Cost::~Cost() {
    // Do I need to delete the cost function pointer?
}

int Cost::getDefault(GameState& gameState) {
    return defaultCost;
}