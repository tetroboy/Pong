#include "Ball.h"

Ball::Ball() {

    m_shape = std::make_unique<sf::CircleShape>(Constants::BALL_RADIUS);
    m_shape->setFillColor(sf::Color::White);
    m_shape->setOrigin({Constants::BALL_RADIUS, Constants::BALL_RADIUS});
    m_velocity.x = 1;
    m_velocity.y = 1;
    setPosition({
        Constants::SCREEN_WIDTH / 2.0f,
        Constants::SCREEN_HEIGHT / 2.0f
    });
}

void Ball::update(float dt) {

    m_shape->move({
        m_velocity.x * m_currentSpeed * Constants::BALL_HORIZONTAL_SPEED_FACTOR * dt,
        m_velocity.y * m_currentSpeed * Constants::BALL_VERTICAL_SPEED_FACTOR * dt
    });

    sf::Vector2f pos = getPosition();

    if (pos.y - Constants::BALL_RADIUS < 0) {
        m_shape->setPosition({pos.x, Constants::BALL_RADIUS});
        m_velocity.y = -m_velocity.y;
    }

    if (pos.y + Constants::BALL_RADIUS > Constants::SCREEN_HEIGHT) {
        m_shape->setPosition({pos.x, Constants::SCREEN_HEIGHT - Constants::BALL_RADIUS});
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

    m_currentSpeed += Constants::BALL_SPEED_INCREASE;
    m_currentSpeed = std::min(m_currentSpeed, Constants::BALL_MAX_SPEED);
}

bool Ball::outOfBoundsLeft() const {
    return getPosition().x - Constants::BALL_RADIUS < 0;
}

bool Ball::outOfBoundsRight() const {
    return getPosition().x + Constants::BALL_RADIUS > Constants::SCREEN_WIDTH;
}
