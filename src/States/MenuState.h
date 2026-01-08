#pragma once
#include "GameState.h"
#include <SFML/Graphics.hpp>

class MenuState : public GameState {
private:
    enum class MenuOption {
        Easy,
        Normal,
        Hard,
        Exit
    };

    std::unique_ptr<sf::Text> title;
    std::unique_ptr<sf::Text> easyText;
    std::unique_ptr<sf::Text> normalText;
    std::unique_ptr<sf::Text> hardText;
    std::unique_ptr<sf::Text> exitText;
    
    MenuOption selectedOption = MenuOption::Normal;  
    void MenuState::updateHighlight();
public:
    explicit MenuState(Game& g);
    void handleEvents(const sf::Event& event) override;
    void update(float dt) override;
    void render(sf::RenderWindow& window) override;
};