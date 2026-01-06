#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "States/GameState.h"
#include "Managers/EntityFactory.h"
#include "Managers/ScoreManager.h"

class Game {
private:
    sf::RenderWindow window;
    std::unique_ptr<GameState> currentState;
    EntityFactory factory;
    ScoreManager scoreManager;
    Difficulty currentDifficulty = Difficulty::Normal;
public:
    Game();
    void run();

    sf::RenderWindow& getWindow() { return window; }
    EntityFactory& getFactory() { return factory; }
    ScoreManager& getScoreManager() { return scoreManager; }

    void changeState(std::unique_ptr<GameState> newState);

    Difficulty getDifficulty() const { return currentDifficulty; }
    void setDifficulty(Difficulty diff) { currentDifficulty = diff; }
};