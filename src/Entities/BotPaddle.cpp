#include "BotPaddle.h"
#include <cmath>

void BotPaddle::setDifficulty(Difficulty diff) {
    switch (diff) {
        case Difficulty::Easy:   botSpeedFactor = 0.6f; break;
        case Difficulty::Normal: botSpeedFactor = 0.8f; break;
        case Difficulty::Hard:   botSpeedFactor = 1.0f; break;
    }
}

void BotPaddle::update(float dt, const Ball& ball) {
    Paddle::update(dt);

    if (ball.getVelocity().x > 0) {
        float ballY = ball.getPosition().y;
        float paddleY = shape->getPosition().y;

        float diff = ballY - paddleY;
        float botSpeed = speed * botSpeedFactor;

        if (std::abs(diff) > 30.0f) {
            if (diff > 0) {
                shape->move(sf::Vector2f(0.0f, botSpeed * dt));
            } else {
                shape->move(sf::Vector2f(0.0f, -botSpeed * dt));
            }
        }
    }

    Paddle::update(dt);
}