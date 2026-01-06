#pragma once
#include "Paddle.h"

class PlayerPaddle : public Paddle {
public:
    void update(float dt) override;
};