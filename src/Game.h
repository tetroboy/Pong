#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "States/GameState.h"
#include "Managers/EntityFactory.h"
#include "Managers/ScoreManager.h"

class Game {
private:
    sf::RenderWindow m_window;
    std::unique_ptr<GameState> m_currentState;
    EntityFactory m_factory;
    ScoreManager m_scoreManager;
    Difficulty m_currentDifficulty = Difficulty::Normal;
public:
    Game();
    void run();

    sf::RenderWindow& getWindow() { return m_window; }
    EntityFactory& getFactory() { return m_factory; }
    ScoreManager& getScoreManager() { return m_scoreManager; }

    void changeState(std::unique_ptr<GameState> newState);

    Difficulty getDifficulty() const { return m_currentDifficulty; }
    void setDifficulty(Difficulty diff) { m_currentDifficulty = diff; }
};