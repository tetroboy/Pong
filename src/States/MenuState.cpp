#include "MenuState.h"
#include "PlayingState.h"
#include "../Utils/Constants.h"
#include <iostream>

MenuState::MenuState(Game& g) : game(g) {

    title = std::make_unique<sf::Text>(Constants::globalFont,"PONG",80);
    exitText = std::make_unique<sf::Text>(Constants::globalFont,"EXIT",50);
    
    easyText = std::make_unique<sf::Text>(Constants::globalFont,"EASY", 40);
    normalText = std::make_unique<sf::Text>(Constants::globalFont,"NORMAL", 40);
    hardText = std::make_unique<sf::Text>(Constants::globalFont,"HARD", 40);

    title.get()->setFillColor(sf::Color::White);
    title.get()->setPosition(sf::Vector2f(Constants::SCREEN_WIDTH / 2 - title.get()->getCharacterSize(),title.get()->getCharacterSize() ));

    exitText.get()->setPosition(sf::Vector2f(Constants::SCREEN_WIDTH / 2 - exitText.get()->getCharacterSize(), Constants::SCREEN_HEIGHT - (exitText.get()->getCharacterSize() * 2)));
    easyText.get()->setPosition(sf::Vector2f(Constants::SCREEN_WIDTH / 2 - easyText.get()->getCharacterSize(), Constants::SCREEN_HEIGHT / 3));
    normalText.get()->setPosition(sf::Vector2f(Constants::SCREEN_WIDTH / 2 - normalText.get()->getCharacterSize(), Constants::SCREEN_HEIGHT / 2));
    hardText.get()->setPosition(sf::Vector2f(Constants::SCREEN_WIDTH / 2 - hardText.get()->getCharacterSize(), Constants::SCREEN_HEIGHT / 1.5));

    updateHighlight();
}

void MenuState::updateHighlight() {
    easyText->setFillColor(selectedOption == 0 ? sf::Color::Yellow : sf::Color::White);
    normalText->setFillColor(selectedOption == 1 ? sf::Color::Yellow : sf::Color::White);
    hardText->setFillColor(selectedOption == 2 ? sf::Color::Yellow : sf::Color::White);
    exitText->setFillColor(selectedOption == 3 ? sf::Color::Yellow : sf::Color::Red);
}


void MenuState::handleEvents(Game& game, const sf::Event& event) {
    if (event.is<sf::Event::KeyPressed>()) {
        auto* key = event.getIf<sf::Event::KeyPressed>();
        if (key->scancode == sf::Keyboard::Scancode::Down) {
            selectedOption = (selectedOption + 1) % 4;
            updateHighlight();
        } else if (key->scancode == sf::Keyboard::Scancode::Up) {
            selectedOption = (selectedOption - 1 + 4) % 4;
            updateHighlight();
        } else if (key->scancode == sf::Keyboard::Scancode::Enter) {
            if (selectedOption == 3) {
                game.getWindow().close();
            } else {
                Difficulty diff;
                if (selectedOption == 0) diff = Difficulty::Easy;
                else if (selectedOption == 1) diff = Difficulty::Normal;
                else diff = Difficulty::Hard;

                game.setDifficulty(diff);
                game.changeState(std::make_unique<PlayingState>(game));
            }
        }
        
    }
}

void MenuState::update(Game& game, float dt) {
    updateHighlight();
}

void MenuState::render(Game& game, sf::RenderWindow& window) {
    window.clear(sf::Color::Black);
    if (title) window.draw(*title.get());
    if (easyText) window.draw(*easyText.get());
    if (normalText) window.draw(*normalText.get());
    if (hardText) window.draw(*hardText.get());
    if (exitText) window.draw(*exitText.get());
}