#pragma once
#include "Entity.h"
#include "../Utils/Constants.h"
#include <iostream>
class Ball : public Entity {
private:
    float initialSpeed = 350.0f;     
    float currentSpeed = initialSpeed;
    float speedIncrease = 50.0f;      
    float maxSpeed = 800.0f;        
    float radius = Constants::BALL_RADIUS;          
public:
    Ball();
    void update(float dt) override;
    void bounceHorizontal(const sf::FloatRect& paddleBounds);
    bool outOfBoundsLeft() const;
    bool outOfBoundsRight() const;
    void reset();
    float getRadius() const; 
};