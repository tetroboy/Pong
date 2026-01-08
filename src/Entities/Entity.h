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
    
    sf::Vector2f velocity;
    std::unique_ptr<sf::Shape> shape;

public:
    virtual ~Entity() = default;

    virtual void update(float dt) = 0;
    virtual void render(sf::RenderWindow& window) const;

    sf::Vector2f getPosition() const { return shape->getPosition(); }
    void setPosition(const sf::Vector2f& pos) { shape->setPosition(pos); }

    void move(const sf::Vector2f& offset) { shape->move(offset); }

    sf::FloatRect getBounds() const {return shape->getGlobalBounds(); }

    sf::Vector2f getVelocity() const { return velocity; }
    void setVelocity(const sf::Vector2f& vel) { velocity = vel; }
};