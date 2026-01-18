#pragma once
#include "ScoreManager.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include "../Utils/Constants.h"

class UIManager : public Observer {
private:
    std::unique_ptr<sf::Text> m_titleText;
    std::unique_ptr<sf::Text> m_playerText;
    std::unique_ptr<sf::Text> m_botText;

public:
    UIManager();
    void onNotify(const ScoreManager& score, GameEvent event) override;
    void render(sf::RenderWindow& window, int playerScore, int botScore);
};