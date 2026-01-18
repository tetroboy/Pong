#pragma once
#include "GameState.h"
#include <SFML/Graphics.hpp>
#include "PlayingState.h"
#include "../Utils/Constants.h"
#include <iostream>

class MenuState : public GameState {
private:
    enum class MenuOption {
        Easy,
        Normal,
        Hard,
        Exit
    };

    sf::Text m_title;
    sf::Text m_easyText;
    sf::Text m_normalText;
    sf::Text m_hardText;
    sf::Text m_exitText;

    MenuOption selectedOption = MenuOption::Normal;  
    void updateHighlight();
public:
    explicit MenuState(Game& g);
    void handleEvents(const sf::Event& event) override;
    void update(float dt) override;
    void render(sf::RenderWindow& window) override;
};