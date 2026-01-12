#include "Ball.h"

Ball::Ball() {

    m_shape = std::make_unique<sf::CircleShape>(m_radius);
    m_shape->setFillColor(sf::Color::White);
    m_shape->setOrigin({m_radius, m_radius});
    m_velocity.x = 1;
    m_velocity.y = 1;
    resetPosition();
}

void Ball::update(float dt) {

    m_shape->move({
        m_velocity.x * m_currentSpeed * Constants::BALL_HORIZONTAL_SPEED_FACTOR * dt,
        m_velocity.y * m_currentSpeed * Constants::BALL_VERTICAL_SPEED_FACTOR * dt
    });

    sf::Vector2f pos = m_shape->getPosition();

    if (pos.y - m_radius < 0) {
        m_shape->setPosition({pos.x, m_radius});
        m_velocity.y = -m_velocity.y;
    }

    if (pos.y + m_radius > Constants::SCREEN_HEIGHT) {
        m_shape->setPosition({pos.x, Constants::SCREEN_HEIGHT - m_radius});
        m_velocity.y = -m_velocity.y;
    }
}

void Ball::bounceHorizontal(const sf::FloatRect& paddleBounds) {
    m_velocity.x = -m_velocity.x;

    sf::Vector2f pos = m_shape->getPosition();
    float hitOffset = (pos.y - paddleBounds.position.y - paddleBounds.size.y / 2.0f)
                    / (paddleBounds.size.y / 2.0f);

    float maxY = 0.6f;
    m_velocity.y = hitOffset * maxY;

    float length = std::hypot(m_velocity.x, m_velocity.y);
    if (length > 0.1f) {
        m_velocity.x /= length;
        m_velocity.y /= length;
    }

    m_currentSpeed += m_speedIncrease;
    m_currentSpeed = std::min(m_currentSpeed, m_maxSpeed);
}

bool Ball::outOfBoundsLeft() const {
    return m_shape->getPosition().x - m_radius < 0;
}

bool Ball::outOfBoundsRight() const {
    return m_shape->getPosition().x + m_radius > Constants::SCREEN_WIDTH;
}

void Ball::resetPosition() {
    m_shape->setPosition({Constants::SCREEN_WIDTH / 2.0f, Constants::SCREEN_HEIGHT / 2.0f}); 
}

float Ball::getRadius() const {
    return m_radius;
}