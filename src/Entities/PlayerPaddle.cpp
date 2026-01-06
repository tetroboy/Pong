#include "PlayerPaddle.h"
#include <SFML/Window/Keyboard.hpp>

void PlayerPaddle::update(float dt) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
        moveUp(dt);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
        moveDown(dt);
    }

    Paddle::update(dt);
}