#pragma once
#include <SFML/Graphics.hpp>

class Game;

class GameState {

protected:
    Game& game;

public:
    explicit GameState(Game& g) : game(g) {}
    virtual ~GameState() = default;

    virtual void handleEvents(const sf::Event& event) = 0;
    virtual void update(float dt) = 0;
    virtual void render(sf::RenderWindow& window) = 0;
};