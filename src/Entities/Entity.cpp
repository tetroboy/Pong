#include "Entity.h"

void Entity::render(sf::RenderWindow& window) const {
    if (shape) {
        window.draw(*shape);
    }
}
