#include "Game.h"
#include "States/MenuState.h"
#include <thread>  
#include <chrono>
#include <iostream>

Game::Game() 
    : window(sf::VideoMode(sf::Vector2u(Constants::SCREEN_WIDTH, Constants::SCREEN_HEIGHT)), "Pong")  
{
    window.setFramerateLimit(60);
    changeState(std::make_unique<MenuState>(*this));
}

void Game::run() {
    sf::Clock clock;
    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();
        
        while (auto eventOpt = window.pollEvent()) {
            const sf::Event& event = *eventOpt;  

            if (event.is<sf::Event::Closed>()) {
                window.close();
            }

            currentState->handleEvents(event);  
        }
        
        currentState->update(dt);

        window.clear(sf::Color::Black);
        
        currentState->render(window);
        
        window.display();
        
        
    }
}

void Game::changeState(std::unique_ptr<GameState> newState) {
    currentState = std::move(newState);
}