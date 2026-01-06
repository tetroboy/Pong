#pragma once
#include <SFML/Graphics.hpp>

namespace Constants {

    inline constexpr float SCREEN_WIDTH = 1200.0f;
    inline constexpr float SCREEN_HEIGHT = 600.0f;

    inline constexpr float BALL_RADIUS = 12.0f;

    inline constexpr float PADDLE_WIDTH = 20.0f;
    inline constexpr float PADDLE_HEIGHT = 100.0f;

    inline constexpr float PADDLE_OFFSET = 50.0f;
    inline constexpr float LINE_OFFSET = 2.0f;
    inline constexpr float SCORE_OFFSET = 200.0f;

    inline sf::Font globalFont = []() {
        sf::Font f;
        if (!f.openFromFile("resources/arial.ttf")) {
            throw std::runtime_error("Не удалось загрузить шрифт arial.ttf");
        }
        return f;
    }();

    inline const sf::Color PLAYER_COLOR = sf::Color::Cyan;
    inline const sf::Color BOT_COLOR = sf::Color::Magenta;
    inline const sf::Color BALL_COLOR = sf::Color::White;
}