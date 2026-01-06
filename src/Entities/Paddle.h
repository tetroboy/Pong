#pragma once
#include "Entity.h"
#include "../Utils/Constants.h"

class Paddle : public Entity {
protected:
    float speed = 350.0f;
    float width = Constants::PADDLE_WIDTH;
    float height = Constants::PADDLE_HEIGHT;

public:
    Paddle();
    virtual void update(float dt) override;  
    void moveUp(float dt);
    void moveDown(float dt);
};