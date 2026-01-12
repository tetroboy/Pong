#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

enum class Difficulty {
    Easy,
    Normal,
    Hard
};

class Entity {
protected:
    
    sf::Vector2f m_velocity;
    std::unique_ptr<sf::Shape> m_shape;

public:
    virtual ~Entity() = default;

    virtual void update(float dt) = 0;
    virtual void render(sf::RenderWindow& window) const;

    sf::Vector2f getPosition() const { return m_shape->getPosition(); }
    void setPosition(const sf::Vector2f& pos) { m_shape->setPosition(pos); }

    void move(const sf::Vector2f& offset) { m_shape->move(offset); }

    sf::FloatRect getBounds() const {return m_shape->getGlobalBounds(); }

    sf::Vector2f getVelocity() const { return m_velocity; }
    void setVelocity(const sf::Vector2f& vel) { m_velocity = vel; }
};