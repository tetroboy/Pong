#include "Ball.h"

Ball::Ball() {

    shape = std::make_unique<sf::CircleShape>(radius);
    shape->setFillColor(sf::Color::White);
    shape->setOrigin({radius, radius});
    velocity.x = 1;
    velocity.y = 1;
    resetPosition();
}

void Ball::update(float dt) {

    shape->move({
        velocity.x * currentSpeed * Constants::BALL_HORIZONTAL_SPEED_FACTOR * dt,
        velocity.y * currentSpeed * Constants::BALL_VERTICAL_SPEED_FACTOR * dt
    });

    sf::Vector2f pos = shape->getPosition();

    if (pos.y - radius < 0) {
        shape->setPosition({pos.x, radius});
        velocity.y = -velocity.y;
    }

    if (pos.y + radius > Constants::SCREEN_HEIGHT) {
        shape->setPosition({pos.x, Constants::SCREEN_HEIGHT - radius});
        velocity.y = -velocity.y;
    }
}

void Ball::bounceHorizontal(const sf::FloatRect& paddleBounds) {
    velocity.x = -velocity.x;

    sf::Vector2f pos = shape->getPosition();
    float hitOffset = (pos.y - paddleBounds.position.y - paddleBounds.size.y / 2.0f)
                    / (paddleBounds.size.y / 2.0f);

    float maxY = 0.6f;
    velocity.y = hitOffset * maxY;

    float length = std::hypot(velocity.x, velocity.y);
    if (length > 0.1f) {
        velocity.x /= length;
        velocity.y /= length;
    }

    currentSpeed += speedIncrease;
    currentSpeed = std::min(currentSpeed, maxSpeed);
}

bool Ball::outOfBoundsLeft() const {
    return shape->getPosition().x - radius < 0;
}

bool Ball::outOfBoundsRight() const {
    return shape->getPosition().x + radius > Constants::SCREEN_WIDTH;
}

void Ball::resetPosition() {
    shape->setPosition({Constants::SCREEN_WIDTH / 2.0f, Constants::SCREEN_HEIGHT / 2.0f}); 
}

float Ball::getRadius() const {
    return radius;
}