#include "Game.h"
#include "States/MenuState.h"
#include <thread>  
#include <chrono>
#include <iostream>

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

            m_currentState->handleEvents(event);  
        }
        
        m_currentState->update(dt);

        m_window.clear(sf::Color::Black);
        
        m_currentState->render(m_window);
        
        m_window.display();
        
        
    }
}

void Game::changeState(std::unique_ptr<GameState> newState) {
    m_currentState = std::move(newState);
}