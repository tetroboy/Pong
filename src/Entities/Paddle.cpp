#include "Paddle.h"
#include <algorithm>

Paddle::Paddle() {
    shape = std::make_unique<sf::RectangleShape>(sf::Vector2f(width, height));
    shape->setFillColor(sf::Color(200, 200, 255));
    shape->setOrigin(sf::Vector2f(width / 2, height / 2)); 
    setPosition({Constants::PADDLE_OFFSET, Constants::SCREEN_HEIGHT / 2}); 
}

void Paddle::update(float dt) {
    position.y = std::clamp(position.y, height / 2.0f, Constants::SCREEN_HEIGHT - height / 2.0f);
}

void Paddle::moveUp(float dt) {
    position.y -= speed * dt;
}

void Paddle::moveDown(float dt) {
    position.y += speed * dt;
}