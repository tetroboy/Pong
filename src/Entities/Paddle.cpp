#include "Paddle.h"

Paddle::Paddle() {
    m_shape = std::make_unique<sf::RectangleShape>(sf::Vector2f(Constants::PADDLE_WIDTH, Constants::PADDLE_HEIGHT));
    m_shape->setFillColor({200, 200, 255});
    m_shape->setOrigin({Constants::PADDLE_WIDTH / 2.0f, Constants::PADDLE_HEIGHT / 2.0f});
    
    m_shape->setPosition({Constants::PADDLE_OFFSET + Constants::PADDLE_WIDTH / 2.0f, Constants::SCREEN_HEIGHT / 2.0f});
}

void Paddle::update(float dt) {
    sf::Vector2f pos = m_shape->getPosition();
    pos.y = std::clamp(pos.y, Constants::PADDLE_HEIGHT / 2.0f, Constants::SCREEN_HEIGHT - Constants::PADDLE_HEIGHT / 2.0f);
    m_shape->setPosition(pos);
}

void Paddle::moveUp(float dt) {
    m_shape->move({0.0f, -m_speed * dt});
}

void Paddle::moveDown(float dt) {
    m_shape->move({0.0f, m_speed * dt});
}