#pragma once
#include "Paddle.h"
#include <SFML/Window/Keyboard.hpp>

class PlayerPaddle : public Paddle {
public:
    void update(float dt) override;
};