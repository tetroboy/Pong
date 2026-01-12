#include "Paddle.h"
#include <algorithm>

Paddle::Paddle() {
    m_shape = std::make_unique<sf::RectangleShape>(sf::Vector2f(m_width, m_height));
    m_shape->setFillColor({200, 200, 255});
    m_shape->setOrigin({m_width / 2.0f, m_height / 2.0f});
    
    m_shape->setPosition({Constants::PADDLE_OFFSET + m_width / 2.0f, Constants::SCREEN_HEIGHT / 2.0f});
}

void Paddle::update(float dt) {
    sf::Vector2f pos = m_shape->getPosition();
    pos.y = std::clamp(pos.y, m_height / 2.0f, Constants::SCREEN_HEIGHT - m_height / 2.0f);
    m_shape->setPosition(pos);
}

void Paddle::moveUp(float dt) {
    m_shape->move({0.0f, -m_speed * dt});
}

void Paddle::moveDown(float dt) {
    m_shape->move({0.0f, m_speed * dt});
}