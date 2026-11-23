#pragma once

#include "controllers/IController.hpp"

class HumanController : public IController
{
public:
    Action getAction() const override;
};