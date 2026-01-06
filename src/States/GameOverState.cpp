#include "GameOverState.h"
#include <iostream>

GameOverState::GameOverState(Game& g, bool victory) : game(g), isVictory(victory) {
    
    titleText = std::make_unique<sf::Text>(Constants::globalFont , isVictory ? "WIN!" : "LOSE!", 100);
    titleText->setFillColor(isVictory ? sf::Color::Green : sf::Color::Red);
    titleText->setPosition(sf::Vector2f(Constants::SCREEN_WIDTH / 2, Constants::SCREEN_HEIGHT / 4));

    messageText = std::make_unique<sf::Text>(Constants::globalFont , isVictory ? "You win!" : "You lose!", 40);
    messageText->setFillColor(sf::Color::White);
    messageText->setPosition(sf::Vector2f(Constants::SCREEN_WIDTH / 2, Constants::SCREEN_HEIGHT / 2));

}

void GameOverState::handleEvents(Game& game, const sf::Event& event) {
    if (event.is<sf::Event::KeyPressed>()) {
        auto* key = event.getIf<sf::Event::KeyPressed>();
        if (key && (key->scancode == sf::Keyboard::Scancode::Enter || key->scancode == sf::Keyboard::Scancode::Escape) ) {
           game.getWindow().close();
        }
    }
}

void GameOverState::update(Game& game, float dt) {
}

void GameOverState::render(Game& game, sf::RenderWindow& window) {
    window.clear(sf::Color::Black);

    if (titleText) window.draw(*titleText.get());
    if (messageText) window.draw(*messageText.get());
}