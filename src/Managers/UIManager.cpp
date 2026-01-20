#include "UIManager.h"

UIManager::UIManager() : m_playerText(Constants::globalFont, "", 40)
    , m_botText(Constants::globalFont, "", 40) {
    
    m_playerText.setFillColor(sf::Color::Cyan);
    m_playerText.setPosition({Constants::SCORE_OFFSET, Constants::SCREEN_HEIGHT / 4.0f});

    m_botText.setFillColor(sf::Color::Magenta);
    m_botText.setPosition({Constants::SCREEN_WIDTH - Constants::SCORE_OFFSET, Constants::SCREEN_HEIGHT / 4.0f});
    m_playerText.setString(std::to_string(0));
    m_botText.setString(std::to_string(0));
    animateScoreText(1.0f);
}

void UIManager::onNotify(const ScoreManager& score, GameEvent event) {
    m_playerText.setString(std::to_string(score.getPlayerScore()));
    m_botText.setString(std::to_string(score.getBotScore()));

    if (event == GameEvent::PlayerGoal || event == GameEvent::BotGoal) {
        animateScoreText(1.5f);
    }
}

void UIManager::animateScoreText(float textScale) {
    m_playerText.setScale({textScale, textScale});
    m_botText.setScale({textScale, textScale});
}

void UIManager::render(sf::RenderWindow& window) {
    if (m_playerText.getScale().x > 1.0f) {
        sf::Vector2f currentScale = m_playerText.getScale() * 0.95f;
        animateScoreText(currentScale.x);
    }
    window.draw(m_playerText);
    window.draw(m_botText);
}