#pragma once
#include "ScoreManager.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include "../Utils/Constants.h"

class UIManager : public Observer {
private:
    sf::Text m_playerText;
    sf::Text m_botText;

    void animateScoreText(float textScale);

public:
    UIManager();
    void onNotify(const ScoreManager& score, GameEvent event) override;
    void render(sf::RenderWindow& window);
};