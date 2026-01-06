#pragma once
#include <SFML/Graphics.hpp>

class Game;

class GameState {
public:
    virtual ~GameState() = default;
    virtual void handleEvents(Game& game, const sf::Event& event) = 0;
    virtual void update(Game& game, float dt) = 0;
    virtual void render(Game& game, sf::RenderWindow& window) = 0;
};