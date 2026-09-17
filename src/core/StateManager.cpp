#include "core/StateManager.hpp"

#include <utility>

void StateManager::changeState(std::unique_ptr<GameState> state)
{
    pendingState_ = std::move(state);
}

void StateManager::applyPendingChange()
{
    if (pendingState_)
    {
        currentState_ = std::move(pendingState_);
    }
}

GameState* StateManager::getCurrentState()
{
    return currentState_.get();
}