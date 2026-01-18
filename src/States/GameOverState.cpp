#include "GameOverState.h"

GameOverState::GameOverState(Game& g, GameResult res) : 
 m_titleText(Constants::globalFont, "", 100),
 m_messageText(Constants::globalFont, "", 40),
 GameState(g), result(res)
{
    m_titleText.setFillColor(result == GameResult::Victory ? sf::Color::Green : sf::Color::Red);
    m_titleText.setPosition(sf::Vector2f(Constants::SCREEN_WIDTH / 2.0f, Constants::SCREEN_HEIGHT / 4.0f));
    result == GameResult::Victory ? m_titleText.setString("WIN!") : m_titleText.setString("LOSE!");
    result == GameResult::Victory ? m_messageText.setString("You win!") : m_messageText.setString("You lose!");

    m_messageText.setFillColor(sf::Color::White);
    m_messageText.setPosition(sf::Vector2f(Constants::SCREEN_WIDTH / 2.0f, Constants::SCREEN_HEIGHT / 2.0f));

}

void GameOverState::handleEvents(const sf::Event& event) {
    if (event.is<sf::Event::KeyPressed>()) {
        auto* key = event.getIf<sf::Event::KeyPressed>();
        if (key && (key->scancode == sf::Keyboard::Scancode::Enter || key->scancode == sf::Keyboard::Scancode::Escape) ) {
           game.getWindow().close();
        }
    }
}

void GameOverState::update(float dt) {
}

void GameOverState::render(sf::RenderWindow& window) {
    window.clear(sf::Color::Black);

    window.draw(m_titleText);
    window.draw(m_messageText);
}