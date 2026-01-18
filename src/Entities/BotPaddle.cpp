#include "BotPaddle.h"
#include <cmath>

void BotPaddle::setDifficulty(Difficulty diff) {
    switch (diff) {
        case Difficulty::Easy:   m_botSpeedFactor = 0.6f; break;
        case Difficulty::Normal: m_botSpeedFactor = 0.8f; break;
        case Difficulty::Hard:   m_botSpeedFactor = 1.0f; break;
    }
}

void BotPaddle::update(float dt) {
    Paddle::update(dt);

    if (!m_ball) return;

    if (m_ball->getVelocity().x > 0) {
        float ballY = m_ball->getPosition().y;
        float paddleY = getPosition().y;

        float diff = ballY - paddleY;
        float botSpeed = m_speed * m_botSpeedFactor;

        if (std::abs(diff) > 30.0f) {
            if (diff > 0) {
                m_shape->move({0.0f, botSpeed * dt});
            } else {
                m_shape->move({0.0f, -botSpeed * dt});
            }
        }
    }

    Paddle::update(dt);
}