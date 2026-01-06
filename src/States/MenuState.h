#pragma once
#include "GameState.h"
#include <SFML/Graphics.hpp>

class MenuState : public GameState {
private:
    Game& game;
    std::unique_ptr<sf::Text> title;
    int selectedDifficulty = 1;  // 0 = Easy, 1 = Normal, 2 = Hard
    std::unique_ptr<sf::Text> easyText;
    std::unique_ptr<sf::Text> normalText;
    std::unique_ptr<sf::Text> hardText;
    std::unique_ptr<sf::Text> exitText;
    int selectedOption = 0;  // 0 = Start, 1 = Exit
    void MenuState::updateHighlight();
public:
    explicit MenuState(Game& g);
    void handleEvents(Game& game, const sf::Event& event) override;
    void update(Game& game, float dt) override;
    void render(Game& game, sf::RenderWindow& window) override;
};