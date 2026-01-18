#include "MenuState.h"

MenuState::MenuState(Game& g) : GameState(g),
    m_title(Constants::globalFont, "PONG", 80),
    m_easyText(Constants::globalFont, "EASY", 40),
    m_normalText(Constants::globalFont, "NORMAL", 40),
    m_hardText(Constants::globalFont, "HARD", 40),
    m_exitText(Constants::globalFont, "EXIT", 50)
{
    m_title.setFillColor(sf::Color::White);
    m_title.setPosition({Constants::SCREEN_WIDTH / 2.0f - static_cast<float>(m_title.getCharacterSize()), static_cast<float>(m_title.getCharacterSize())});

    m_easyText.setPosition({Constants::SCREEN_WIDTH / 2.0f - static_cast<float>(m_easyText.getCharacterSize()), Constants::SCREEN_HEIGHT / 3.0f});
    m_normalText.setPosition({Constants::SCREEN_WIDTH / 2.0f - static_cast<float>(m_normalText.getCharacterSize()), Constants::SCREEN_HEIGHT / 2.0f});
    m_hardText.setPosition({Constants::SCREEN_WIDTH / 2.0f - static_cast<float>(m_hardText.getCharacterSize()), Constants::SCREEN_HEIGHT / 1.5f});
    m_exitText.setPosition({Constants::SCREEN_WIDTH / 2.0f - static_cast<float>(m_exitText.getCharacterSize()), Constants::SCREEN_HEIGHT - static_cast<float>(m_exitText.getCharacterSize() * 2)});

    updateHighlight();
}

void MenuState::updateHighlight() {
    m_easyText.setFillColor(selectedOption == MenuOption::Easy ? sf::Color::Yellow : sf::Color::White);
    m_normalText.setFillColor(selectedOption == MenuOption::Normal ? sf::Color::Yellow : sf::Color::White);
    m_hardText.setFillColor(selectedOption == MenuOption::Hard ? sf::Color::Yellow : sf::Color::White);
    m_exitText.setFillColor(selectedOption == MenuOption::Exit ? sf::Color::Yellow : sf::Color::Red);
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
    window.draw(m_title);
    window.draw(m_easyText);
    window.draw(m_normalText);
    window.draw(m_hardText);
    window.draw(m_exitText);
}