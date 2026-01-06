#include "Entity.h"

void Entity::render(sf::RenderWindow& window) const {
    if (shape) {
        shape->setPosition(position);
        window.draw(*shape);
    }
}

sf::FloatRect Entity::getBounds() const {
    return shape ? shape->getGlobalBounds() : sf::FloatRect();
}