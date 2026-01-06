#include "Ball.h"
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <mutex>

Ball::Ball() {

    shape = std::make_unique<sf::CircleShape>(radius);
    shape->setFillColor(sf::Color::White);
    shape->setOrigin(sf::Vector2f(radius, radius));
    velocity.x = 1;
    velocity.y = 1;
    static bool seeded = false;
    if (!seeded) {
        std::srand(static_cast<unsigned>(std::time(nullptr)));
        seeded = true;
    }
    setPosition({Constants::SCREEN_WIDTH / 2, Constants::SCREEN_HEIGHT / 2});
    reset(); 
}

void Ball::update(float dt) {
    
    const float horizontalSpeedFactor = 1.0f;  
    const float verticalSpeedFactor = 0.8f;    

    position.x += velocity.x * currentSpeed * horizontalSpeedFactor * dt;
    position.y += velocity.y * currentSpeed * verticalSpeedFactor * dt;

    if (position.y - radius < 0) {
        position.y = radius;              
        velocity.y = -velocity.y;         
    }

    if (position.y + radius > Constants::SCREEN_HEIGHT) {
        position.y = Constants::SCREEN_HEIGHT - radius; 
        velocity.y = -velocity.y;
    }
}

void Ball::bounceHorizontal(const sf::FloatRect& paddleBounds) {
    velocity.x = -velocity.x;

    float hitOffset = (position.y - paddleBounds.position.y - paddleBounds.size.y / 2.0f) 
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
    return position.x + radius < 0;
}

bool Ball::outOfBoundsRight() const {
    return position.x - radius > Constants::SCREEN_WIDTH;
}

void Ball::reset() {
    position = { Constants::SCREEN_WIDTH / 2.0f, Constants::SCREEN_HEIGHT / 2.0f };
    float xDir = (std::rand() % 2 == 0) ? 1.0f : -1.0f;

    velocity.x = xDir;
    velocity.y = (static_cast<float>(std::rand()) / RAND_MAX - 0.5f) * 0.6f;  // Y максимум ±0.3

    float length = std::hypot(velocity.x, velocity.y);
    if (length > 0.1f) {
        velocity /= length;
    }

    currentSpeed = initialSpeed;
}

float Ball::getRadius() const {
    return radius;
}