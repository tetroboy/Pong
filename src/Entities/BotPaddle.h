#pragma once
#include "Paddle.h"
#include "Ball.h"

class BotPaddle : public Paddle {
private:
    float m_botSpeedFactor = 0.8f;
public:
    void setDifficulty(Difficulty diff);
    void update(float dt, const Ball& ball); 
};