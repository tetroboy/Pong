#pragma once
#include "Entity.h"
#include "../Utils/Constants.h"

class Paddle : public Entity {
protected:
    float m_speed = 350.0f;

public:
    Paddle();
    virtual void update(float dt) override;  
    void moveUp(float dt);
    void moveDown(float dt);
};