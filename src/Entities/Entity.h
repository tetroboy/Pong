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
sf::Vector2f position;
    virtual ~Entity() = default;

    virtual void update(float dt) = 0;
    virtual void render(sf::RenderWindow& window) const;

    sf::FloatRect getBounds() const;
    sf::Vector2f getPosition() const { return position; }
    void setPosition(const sf::Vector2f& pos) { position = pos; }

    sf::Vector2f getVelocity() const { return velocity; }
    void setVelocity(const sf::Vector2f& vel) { velocity = vel; }
};