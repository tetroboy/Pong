#pragma once
#include "GameState.h"
#include "../Game.h"
#include "../Entities/Entity.h"
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../Managers/ScoreManager.h"
#include "../Managers/UIManager.h"
#include "../Managers/EntityFactory.h"
#include "../Entities/Ball.h"
#include "../Entities/Paddle.h"
#include "../Entities/PlayerPaddle.h"
#include "../Entities/BotPaddle.h" 
#include "PauseState.h"
#include "MenuState.h"
#include "GameOverState.h"

class PlayingState : public GameState {
private:
    Game& game;
    std::vector<std::unique_ptr<Entity>> entities;
    UIManager uiManager;
    sf::Clock gameClock;
    sf::SoundBuffer hitBuffer;
    sf::SoundBuffer goalBuffer;
    std::unique_ptr<sf::Sound> hitSound;
    std::unique_ptr<sf::Sound> goalSound;
public:
    PlayingState(Game& game);
    void handleEvents(Game& game,const sf::Event& event) override;
    void update(Game& game, float dt) override;
    void render(Game& game, sf::RenderWindow& window) override;
};