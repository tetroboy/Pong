#include "GameOverState.h"
#include <iostream>

GameOverState::GameOverState(Game& g, GameResult res) : GameState(g), result(res) {
    
    titleText = std::make_unique<sf::Text>(Constants::globalFont, 
                                           result == GameResult::Victory ? "WIN!" : "LOSE!", 
                                           100);
    titleText->setFillColor(result == GameResult::Victory ? sf::Color::Green : sf::Color::Red);
    titleText->setPosition(sf::Vector2f(Constants::SCREEN_WIDTH / 2, Constants::SCREEN_HEIGHT / 4));

    messageText = std::make_unique<sf::Text>(Constants::globalFont, 
                                             result == GameResult::Victory ? "You win!" : "You lose!", 
                                             40);
    messageText->setFillColor(sf::Color::White);
    messageText->setPosition(sf::Vector2f(Constants::SCREEN_WIDTH / 2, Constants::SCREEN_HEIGHT / 2));

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

    if (titleText) window.draw(*titleText);
    if (messageText) window.draw(*messageText);
}