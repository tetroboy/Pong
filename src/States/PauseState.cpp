#include "PauseState.h"

PauseState::PauseState(Game& g) : GameState(g) {

    m_pauseText = std::make_unique<sf::Text>(Constants::globalFont,"PAUSED",80);
    m_resumeText = std::make_unique<sf::Text>(Constants::globalFont,"RESUME",50);
    m_exitText = std::make_unique<sf::Text>(Constants::globalFont,"EXIT",50);
    
    m_pauseText->setFillColor(sf::Color::Yellow);
    m_pauseText->setPosition({350.f, 100.f});

    m_resumeText->setFillColor(sf::Color::Cyan);
    m_resumeText->setPosition({350.f, 250.f});

    m_exitText->setFillColor(sf::Color::Red);
    m_exitText->setPosition({350.f, 350.f});
}

void PauseState::handleEvents(const sf::Event& event) {
    if (event.is<sf::Event::KeyPressed>()) {
        auto* key = event.getIf<sf::Event::KeyPressed>();
        if (key->scancode == sf::Keyboard::Scancode::Down) {
            selectedOption = (selectedOption == PauseOption::Resume) ? PauseOption::ExitToMenu : PauseOption::Resume;
        } else if (key->scancode == sf::Keyboard::Scancode::Up) {
            selectedOption = (selectedOption == PauseOption::Resume) ? PauseOption::ExitToMenu : PauseOption::Resume;
        } else if (key->scancode == sf::Keyboard::Scancode::Enter || key->scancode == sf::Keyboard::Scancode::Escape) {
            if (selectedOption == PauseOption::Resume) {
                game.changeState(std::make_unique<PlayingState>(game));
            } else {
                game.getWindow().close();
            }
        }
    }
}

void PauseState::update(float dt) {
    m_resumeText->setFillColor(selectedOption == PauseOption::Resume ? sf::Color::Yellow : sf::Color::White);
    m_exitText->setFillColor(selectedOption == PauseOption::ExitToMenu ? sf::Color::Yellow : sf::Color::Red);
}

void PauseState::render(sf::RenderWindow& window) {
    window.clear({0, 0, 0, 200});  

    if(m_pauseText) window.draw(*m_pauseText);
    if(m_resumeText) window.draw(*m_resumeText);
    if(m_exitText) window.draw(*m_exitText);
}