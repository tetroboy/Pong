#pragma once
#include "ScoreManager.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include "../Utils/Constants.h"

class UIManager : public Observer {
private:
    std::unique_ptr<sf::Text> titleText;
    std::unique_ptr<sf::Text> playerText;
    std::unique_ptr<sf::Text> botText;

public:
    UIManager();
    void onNotify(GameEvent event) override;
    void render(sf::RenderWindow& window, int playerScore, int botScore);
};