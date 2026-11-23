#pragma once

#include "game/Action.hpp"

class IController
{
public:
    virtual ~IController() = default;

    virtual Action getAction() const = 0;
};