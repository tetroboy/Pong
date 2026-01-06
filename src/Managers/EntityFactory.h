#pragma once
#include <memory>
#include "../Entities/Ball.h"
#include "../Entities/Paddle.h"
#include "../Entities/PlayerPaddle.h" 
#include "../Entities/BotPaddle.h"

class EntityFactory {
public:
    std::unique_ptr<Ball> createBall();
    std::unique_ptr<Paddle> createPlayerPaddle();
    std::unique_ptr<BotPaddle> createBotPaddle();  
};