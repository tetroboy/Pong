#pragma once
#include "GameState.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include "../Utils/Constants.h"
#include "../Game.h"

class GameOverState : public GameState {
private:
    Game& game;
    std::unique_ptr<sf::Text> titleText;
    std::unique_ptr<sf::Text> messageText;
    std::unique_ptr<sf::Text> menuText;
    bool isVictory;  // true = Player wins, false = Bot wins.

public:
    GameOverState(Game& g, bool victory);
    void handleEvents(Game& game, const sf::Event& event) override;
    void update(Game& game, float dt) override;
    void render(Game& game, sf::RenderWindow& window) override;
};