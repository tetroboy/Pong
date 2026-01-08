#pragma once
#include "GameState.h"
#include "../Utils/Constants.h"
#include <SFML/Graphics.hpp>

class PauseState : public GameState {
private:
    enum class PauseOption {
        Resume,
        ExitToMenu
    };

    std::unique_ptr<sf::Text> pauseText;
    std::unique_ptr<sf::Text> resumeText;
    std::unique_ptr<sf::Text> exitText;
    
    PauseOption selectedOption = PauseOption::Resume;

public:
    explicit PauseState(Game& g);
    void handleEvents( const sf::Event& event) override;
    void update(float dt) override;
    void render(sf::RenderWindow& window) override;
};