#pragma once
#include "GameState.h"
#include "../Utils/Constants.h"
#include <SFML/Graphics.hpp>

class PauseState : public GameState {
private:
    Game& game;
    std::unique_ptr<sf::Text> pauseText;
    std::unique_ptr<sf::Text> resumeText;
    std::unique_ptr<sf::Text> exitText;
    int selectedOption = 0;  // 0 = Resume, 1 = Exit to Menu

public:
    explicit PauseState(Game& g);
    void handleEvents(Game& game, const sf::Event& event) override;
    void update(Game& game, float dt) override;
    void render(Game& game, sf::RenderWindow& window) override;
};