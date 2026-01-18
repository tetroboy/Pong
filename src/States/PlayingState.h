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
    std::unique_ptr<PlayerPaddle> m_player;
    std::unique_ptr<BotPaddle> m_bot;
    std::shared_ptr<Ball> m_ball;
    UIManager m_uiManager;
    sf::Clock m_gameClock;
    sf::SoundBuffer m_hitBuffer;
    sf::SoundBuffer m_goalBuffer;
    std::unique_ptr<sf::Sound> m_hitSound;
    std::unique_ptr<sf::Sound> m_goalSound;

    void resetBall();

public:
    explicit PlayingState(Game& game);
    ~PlayingState();
    void handleEvents(const sf::Event& event) override;
    void update(float dt) override;
    void render(sf::RenderWindow& window) override;
};