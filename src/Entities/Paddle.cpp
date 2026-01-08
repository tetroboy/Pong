#include "Paddle.h"
#include <algorithm>

Paddle::Paddle() {
    shape = std::make_unique<sf::RectangleShape>(sf::Vector2f(width, height));
    shape->setFillColor(sf::Color(200, 200, 255));
    shape->setOrigin(sf::Vector2f(width / 2.0f, height / 2.0f));
    
    shape->setPosition(sf::Vector2f(Constants::PADDLE_OFFSET + width / 2.0f, Constants::SCREEN_HEIGHT / 2.0f));
}

void Paddle::update(float dt) {
    sf::Vector2f pos = shape->getPosition();
    pos.y = std::clamp(pos.y, height / 2.0f, Constants::SCREEN_HEIGHT - height / 2.0f);
    shape->setPosition(pos);
}

void Paddle::moveUp(float dt) {
    shape->move(sf::Vector2f(0.0f, -speed * dt));
}

void Paddle::moveDown(float dt) {
    shape->move(sf::Vector2f(0.0f, speed * dt));
}