#pragma once
#include <SFML/Graphics.hpp>
#include <random>  
#include <chrono>

namespace Constants {

    inline constexpr float SCREEN_WIDTH = 1200.0f;
    inline constexpr float SCREEN_HEIGHT = 600.0f;

    inline constexpr float BALL_RADIUS = 12.0f;
    inline constexpr float BALL_HORIZONTAL_SPEED_FACTOR = 1.0f;
    inline constexpr float BALL_VERTICAL_SPEED_FACTOR = 0.8f;
    inline constexpr float BALL_INITIAL_SPEED = 350.0f;
    inline constexpr float BALL_MAX_SPEED = 800.0f;
    inline constexpr float BALL_SPEED_INCREASE = 50.0f;
    inline constexpr float BALL_MAX_Y = 0.6f;

    inline constexpr float PADDLE_WIDTH = 20.0f;
    inline constexpr float PADDLE_HEIGHT = 100.0f;

    inline constexpr float PADDLE_OFFSET = 50.0f;
    inline constexpr float LINE_OFFSET = 2.0f;
    inline constexpr float SCORE_OFFSET = 200.0f;

    inline constexpr short MAX_GOALS = 10;

    inline constexpr float HIT_SOUND_VOLUME = 70.0f;
    inline constexpr float GOAL_SOUND_VOLUME = 80.0f;

    inline sf::Font globalFont = []() {
        sf::Font f;
        if (!f.openFromFile("resources/arial.ttf")) {
            throw std::runtime_error("Can't load font arial.ttf");
        }
        return f;
    }();

    inline const sf::Color PLAYER_COLOR = sf::Color::Cyan;
    inline const sf::Color BOT_COLOR = sf::Color::Magenta;
    inline const sf::Color BALL_COLOR = sf::Color::White;
}

namespace Random {
    inline std::mt19937& getRNG() {
        static std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
        return rng;
    }

    inline float floatInRange(float min, float max) {
        std::uniform_real_distribution<float> dist(min, max);
        return dist(getRNG());
    }

    inline float sign() {
        return floatInRange(0.0f, 1.0f) < 0.5f ? -1.0f : 1.0f;
    }
}