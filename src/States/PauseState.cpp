#include "PauseState.h"
#include "PlayingState.h"
#include "MenuState.h"


PauseState::PauseState(Game& g) : game(g) {

    pauseText = std::make_unique<sf::Text>(Constants::globalFont,"PAUSED",80);
    resumeText = std::make_unique<sf::Text>(Constants::globalFont,"RESUME",50);
    exitText = std::make_unique<sf::Text>(Constants::globalFont,"EXIT",50);
    
    pauseText.get()->setFillColor(sf::Color::Yellow);
    pauseText.get()->setPosition(sf::Vector2f(350.f, 100.f));

    resumeText.get()->setFillColor(sf::Color::Cyan);
    resumeText.get()->setPosition(sf::Vector2f(350.f, 250.f));

    exitText.get()->setFillColor(sf::Color::Red);
    exitText.get()->setPosition(sf::Vector2f(350.f, 350.f));
}

void PauseState::handleEvents(Game& game, const sf::Event& event) {
    if (event.is<sf::Event::KeyPressed>()) {
        auto* key = event.getIf<sf::Event::KeyPressed>();
        if (key->scancode == sf::Keyboard::Scancode::Down) {
            selectedOption = 1;
        } else if (key->scancode == sf::Keyboard::Scancode::Up) {
            selectedOption = 0;
        } else if (key->scancode == sf::Keyboard::Scancode::Enter) {
            if (selectedOption == 0) {
                game.changeState(std::make_unique<PlayingState>(game));
            } else {
                game.getWindow().close();
            }
        } else if (key->scancode == sf::Keyboard::Scancode::Escape) {
            game.changeState(std::make_unique<PlayingState>(game));
        }
    }
}

void PauseState::update(Game& game, float dt) {
    resumeText.get()->setFillColor(selectedOption == 0 ? sf::Color::Yellow : sf::Color::Cyan);
    exitText.get()->setFillColor(selectedOption == 1 ? sf::Color::Yellow : sf::Color::Cyan);
}

void PauseState::render(Game& game, sf::RenderWindow& window) {
    window.clear(sf::Color(0, 0, 0, 200));  

    if(pauseText) window.draw(*pauseText.get());
    if(resumeText) window.draw(*resumeText.get());
    if(exitText) window.draw(*exitText.get());
}