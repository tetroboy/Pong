#include "Game.h"

Game::Game() 
    : m_window(sf::VideoMode(sf::Vector2u(Constants::SCREEN_WIDTH, Constants::SCREEN_HEIGHT)), "Pong")  
{
    m_window.setFramerateLimit(60);
    changeState(std::make_unique<MenuState>(*this));
}

void Game::run() {
    sf::Clock clock;
    while (m_window.isOpen()) {
        float dt = clock.restart().asSeconds();
        
        while (auto eventOpt = m_window.pollEvent()) {
            const sf::Event& event = *eventOpt;  

            if (event.is<sf::Event::Closed>()) {
                m_window.close();
            }

            getCurrentState().handleEvents(event); 
        }
        
        getCurrentState().update(dt);

        m_window.clear(sf::Color::Black);
        
        getCurrentState().render(m_window);
        
        m_window.display();
    }
}

void Game::pushState(std::unique_ptr<GameState> state) {
    stateStack.push_back(std::move(state));
}

void Game::popState() {
    if (!stateStack.empty()) {
        stateStack.pop_back();
    }
}

void Game::changeState(std::unique_ptr<GameState> state) {
    stateStack.clear();
    stateStack.push_back(std::move(state));
}

GameState& Game::getCurrentState() {
    if (stateStack.empty()) {
        throw std::runtime_error("No active state!");
    }
    return *stateStack.back();
}