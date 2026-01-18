#pragma once
#include "Entity.h"
#include "../Utils/Constants.h"
#include <iostream>
class Ball : public Entity {
private:     
    float m_currentSpeed = Constants::BALL_INITIAL_SPEED;                     
public:
    Ball();
    void update(float dt) override;
    void bounceHorizontal(const sf::FloatRect& paddleBounds);
    bool outOfBoundsLeft() const;
    bool outOfBoundsRight() const;
    void setSpeed(float speed){ m_currentSpeed = speed; }
};