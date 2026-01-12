#include "MenuState.h"
#include "PlayingState.h"
#include "../Utils/Constants.h"
#include <iostream>

MenuState::MenuState(Game& g) : GameState(g) {

    title = std::make_unique<sf::Text>(Constants::globalFont,"PONG",80);
    exitText = std::make_unique<sf::Text>(Constants::globalFont,"EXIT",50);
    
    easyText = std::make_unique<sf::Text>(Constants::globalFont,"EASY", 40);
    normalText = std::make_unique<sf::Text>(Constants::globalFont,"NORMAL", 40);
    hardText = std::make_unique<sf::Text>(Constants::globalFont,"HARD", 40);

    title->setFillColor(sf::Color::White);
    title->setPosition({Constants::SCREEN_WIDTH / 2.0f - static_cast<float>(title->getCharacterSize()),static_cast<float>(title->getCharacterSize()) });

    exitText->setPosition({Constants::SCREEN_WIDTH / 2.0f - static_cast<float>(exitText->getCharacterSize()), Constants::SCREEN_HEIGHT - static_cast<float>(exitText->getCharacterSize() * 2)});
    easyText->setPosition({Constants::SCREEN_WIDTH / 2.0f - static_cast<float>(easyText->getCharacterSize()), Constants::SCREEN_HEIGHT / 3.0f});
    normalText->setPosition({Constants::SCREEN_WIDTH / 2.0f - static_cast<float>(normalText->getCharacterSize()), Constants::SCREEN_HEIGHT / 2.0f});
    hardText->setPosition({Constants::SCREEN_WIDTH / 2.0f - static_cast<float>(hardText->getCharacterSize()), Constants::SCREEN_HEIGHT / 1.5f});

    updateHighlight();
}

void MenuState::updateHighlight() {
    easyText->setFillColor(selectedOption == MenuOption::Easy ? sf::Color::Yellow : sf::Color::White);
    normalText->setFillColor(selectedOption == MenuOption::Normal ? sf::Color::Yellow : sf::Color::White);
    hardText->setFillColor(selectedOption == MenuOption::Hard ? sf::Color::Yellow : sf::Color::White);
    exitText->setFillColor(selectedOption == MenuOption::Exit ? sf::Color::Yellow : sf::Color::Red);
}


void MenuState::handleEvents(const sf::Event& event) {
    if (event.is<sf::Event::KeyPressed>()) {
        auto* key = event.getIf<sf::Event::KeyPressed>();
        if (key->scancode == sf::Keyboard::Scancode::Down) {
            switch (selectedOption) {
                case MenuOption::Easy:   selectedOption = MenuOption::Normal; break;
                case MenuOption::Normal: selectedOption = MenuOption::Hard; break;
                case MenuOption::Hard:   selectedOption = MenuOption::Exit; break;
                case MenuOption::Exit:   selectedOption = MenuOption::Easy; break;
            }
        } else if (key->scancode == sf::Keyboard::Scancode::Up) {
            switch (selectedOption) {
                case MenuOption::Easy:   selectedOption = MenuOption::Exit; break;
                case MenuOption::Normal: selectedOption = MenuOption::Easy; break;
                case MenuOption::Hard:   selectedOption = MenuOption::Normal; break;
                case MenuOption::Exit:   selectedOption = MenuOption::Hard; break;
            }
        } else if (key->scancode == sf::Keyboard::Scancode::Enter) {
            switch (selectedOption) {
                case MenuOption::Easy:
                case MenuOption::Normal:
                case MenuOption::Hard:
                    game.setDifficulty(static_cast<Difficulty>(static_cast<int>(selectedOption)));
                    game.changeState(std::make_unique<PlayingState>(game));
                    break;
                case MenuOption::Exit:
                    game.getWindow().close();
                    break;
            }
        }
        
    }
}

void MenuState::update(float dt) {
    updateHighlight();
}

void MenuState::render(sf::RenderWindow& window) {
    window.clear(sf::Color::Black);
    if (title) window.draw(*title);
    if (easyText) window.draw(*easyText);
    if (normalText) window.draw(*normalText);
    if (hardText) window.draw(*hardText);
    if (exitText) window.draw(*exitText);
}