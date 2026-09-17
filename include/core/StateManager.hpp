#pragma once

#include "core/GameState.hpp"

#include <memory>

class StateManager
{
public:
    void changeState(std::unique_ptr<GameState> state);
    void applyPendingChange();

    GameState* getCurrentState();

private:
    std::unique_ptr<GameState> currentState_;
    std::unique_ptr<GameState> pendingState_;
};