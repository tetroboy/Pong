#pragma once
#include "GameState.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include "../Utils/Constants.h"
#include "../Game.h"
enum class GameResult {
        Victory,
        Defeat
    };

class GameOverState : public GameState {
private:
    sf::Text m_titleText;
    sf::Text m_messageText;
    GameResult result = GameResult::Victory;

public:
    GameOverState(Game& g, GameResult result);
    void handleEvents(const sf::Event& event) override;
    void update(float dt) override;
    void render(sf::RenderWindow& window) override;
};