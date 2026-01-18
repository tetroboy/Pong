#pragma once
#include "GameState.h"
#include "PlayingState.h"
#include "../Utils/Constants.h"
#include <SFML/Graphics.hpp>

class PauseState : public GameState {
private:
    enum class PauseOption {
        Resume,
        ExitToMenu
    };

    sf::Text m_pauseText;
    sf::Text m_resumeText;
    sf::Text m_exitText;
    
    PauseOption selectedOption = PauseOption::Resume;

public:
    explicit PauseState(Game& g);
    void handleEvents( const sf::Event& event) override;
    void update(float dt) override;
    void render(sf::RenderWindow& window) override;
};