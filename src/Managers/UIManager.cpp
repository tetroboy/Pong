#include "UIManager.h"
#include <iostream>

UIManager::UIManager() {
    
    m_playerText = std::make_unique<sf::Text>(Constants::globalFont, "", 40);
    m_botText = std::make_unique<sf::Text>(Constants::globalFont, "", 40);

    m_playerText->setFillColor(sf::Color::Cyan);
    m_playerText->setPosition({Constants::SCORE_OFFSET, Constants::SCREEN_HEIGHT / 4.0f});

    m_botText->setFillColor(sf::Color::Magenta);
    m_botText->setPosition({Constants::SCREEN_WIDTH - Constants::SCORE_OFFSET, Constants::SCREEN_HEIGHT / 4.0f});
    
}

void UIManager::onNotify(GameEvent event) {
    if (event == GameEvent::PlayerGoal || event == GameEvent::BotGoal) {
        m_playerText->setScale({1.5f, 1.5f});
        m_botText->setScale({1.5f, 1.5f});
    }
}

void UIManager::render(sf::RenderWindow& window, int playerScore, int botScore) {
    if (m_playerText->getScale().x > 1.0f) {
        sf::Vector2f currentScale = m_playerText->getScale() * 0.95f;
        m_playerText->setScale(currentScale);
        m_botText->setScale(currentScale);
    }

    if (m_playerText) m_playerText->setString(std::to_string(playerScore));
    if (m_botText) m_botText->setString(std::to_string(botScore));
    
    if (m_playerText) window.draw(*m_playerText);
    if (m_botText) window.draw(*m_botText);
}