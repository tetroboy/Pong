#include "EntityFactory.h"

std::unique_ptr<Ball> EntityFactory::createBall() {
    auto ball = std::make_unique<Ball>();
    return ball;
}

std::unique_ptr<Paddle> EntityFactory::createPlayerPaddle() {
    auto paddle = std::make_unique<PlayerPaddle>();  
    paddle->setPosition({Constants::PADDLE_OFFSET, Constants::SCREEN_HEIGHT / 2});
    return paddle;
}

std::unique_ptr<BotPaddle> EntityFactory::createBotPaddle() {
    auto paddle = std::make_unique<BotPaddle>();
    paddle->setPosition({Constants::SCREEN_WIDTH - Constants::PADDLE_OFFSET, Constants::SCREEN_HEIGHT / 2});
    return paddle;
}