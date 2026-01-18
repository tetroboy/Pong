#pragma once
#include "Entity.h"
#include "../Utils/Constants.h"
#include <iostream>
class Ball : public Entity {
private:
    float m_initialSpeed = 350.0f;     
    float m_currentSpeed = m_initialSpeed;
    float m_speedIncrease = 50.0f;      
    float m_maxSpeed = 800.0f;        
    float m_radius = Constants::BALL_RADIUS;          
public:
    Ball();
    void update(float dt) override;
    void bounceHorizontal(const sf::FloatRect& paddleBounds);
    bool outOfBoundsLeft() const;
    bool outOfBoundsRight() const;
    float getRadius() const; 
    float getInitialSpeed() const{ return m_initialSpeed; }
    void setSpeed(float speed){ m_currentSpeed = speed; }
};