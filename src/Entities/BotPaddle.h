#pragma once
#include "Paddle.h"
#include "Ball.h"
#include <cmath>

class BotPaddle : public Paddle {
private:
    float m_botSpeedFactor = 0.8f;
    std::shared_ptr<const Ball> m_ball;
public:
    void setDifficulty(Difficulty diff);
    void update(float dt); 
    void setBall(std::shared_ptr<Ball> ball) {
        m_ball = ball;
    }
};