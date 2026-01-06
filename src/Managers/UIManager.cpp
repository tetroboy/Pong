#include "UIManager.h"
#include <iostream>
static sf::Font font("resources/arial.ttf");
UIManager::UIManager() {
    
    playerText = std::make_unique<sf::Text>(font, "", 40);
    botText = std::make_unique<sf::Text>(font, "", 40);

    playerText.get()->setFillColor(sf::Color::Cyan);
    playerText.get()->setPosition(sf::Vector2f(Constants::SCORE_OFFSET, Constants::SCREEN_HEIGHT / 4));

    botText.get()->setFillColor(sf::Color::Magenta);
    botText.get()->setPosition(sf::Vector2f(Constants::SCREEN_WIDTH - Constants::SCORE_OFFSET, Constants::SCREEN_HEIGHT / 4));
    
}

void UIManager::onNotify(GameEvent event) {
    if (event == GameEvent::PlayerGoal || event == GameEvent::BotGoal) {
        playerText.get()->setScale(sf::Vector2f(1.5f, 1.5f));
        botText.get()->setScale(sf::Vector2f(1.5f, 1.5f));
    }
}

void UIManager::render(sf::RenderWindow& window, int playerScore, int botScore) {
    if (playerText.get()->getScale().x > 1.0f) {
        sf::Vector2f currentScale = playerText.get()->getScale() * 0.95f;
        playerText.get()->setScale(currentScale);
        botText.get()->setScale(currentScale);
    }

    if (playerText) playerText.get()->setString(std::to_string(playerScore));
    if (botText) botText.get()->setString(std::to_string(botScore));
    
    if (playerText) window.draw(*playerText.get());
    if (botText) window.draw(*botText.get());
}