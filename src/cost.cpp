#include "cost.h"

Cost::Cost(int defaultCost, int (*costFunction)(GameState*)) {
    this->defaultCost = defaultCost;
    this->costFunction = costFunction;
}

Cost::get(GameState* gameState) {
    return (Cost::*costFunction)(gameState);
}

Cost::~Cost() {
    // Do I need to delete the cost function pointer?
}

Cost::staticCost(GameState* gameState) {
    return defaultCost;
}