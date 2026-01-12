#include "Entity.h"

void Entity::render(sf::RenderWindow& window) const {
    if (m_shape) {
        window.draw(*m_shape);
    }
}
