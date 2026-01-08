#include "UIManager.h"
#include <iostream>

UIManager::UIManager() {
    
    playerText = std::make_unique<sf::Text>(Constants::globalFont, "", 40);
    botText = std::make_unique<sf::Text>(Constants::globalFont, "", 40);

    playerText->setFillColor(sf::Color::Cyan);
    playerText->setPosition(sf::Vector2f(Constants::SCORE_OFFSET, Constants::SCREEN_HEIGHT / 4));

    botText->setFillColor(sf::Color::Magenta);
    botText->setPosition(sf::Vector2f(Constants::SCREEN_WIDTH - Constants::SCORE_OFFSET, Constants::SCREEN_HEIGHT / 4));
    
}

void UIManager::onNotify(GameEvent event) {
    if (event == GameEvent::PlayerGoal || event == GameEvent::BotGoal) {
        playerText->setScale(sf::Vector2f(1.5f, 1.5f));
        botText->setScale(sf::Vector2f(1.5f, 1.5f));
    }
}

void UIManager::render(sf::RenderWindow& window, int playerScore, int botScore) {
    if (playerText->getScale().x > 1.0f) {
        sf::Vector2f currentScale = playerText->getScale() * 0.95f;
        playerText->setScale(currentScale);
        botText->setScale(currentScale);
    }

    if (playerText) playerText->setString(std::to_string(playerScore));
    if (botText) botText->setString(std::to_string(botScore));
    
    if (playerText) window.draw(*playerText);
    if (botText) window.draw(*botText);
}