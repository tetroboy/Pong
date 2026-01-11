#include "PlayingState.h"
#include <iostream>
#include <SFML/Window/Keyboard.hpp>

PlayingState::PlayingState(Game& g) : GameState(g) {
    auto& factory = game.getFactory();
    auto& score = game.getScoreManager();

    player = factory.createPlayerPaddle();
    bot = factory.createBotPaddle();
    ball = factory.createBall();

    bot->setDifficulty(game.getDifficulty());

    if (!hitBuffer.loadFromFile("resources/hit.mp3")) {
        std::cout << "erro hit.mp3" << std::endl;
    }
    if (!goalBuffer.loadFromFile("resources/bounce.mp3")) {
        std::cout << "erro goal.mp3" << std::endl;
    }

    hitSound = std::make_unique<sf::Sound>(hitBuffer);
    goalSound = std::make_unique<sf::Sound>(goalBuffer);

    hitSound->setVolume(Constants::HIT_SOUND_VOLUME);
    goalSound->setVolume(Constants::GOAL_SOUND_VOLUME);

    score.registerObserver(&uiManager);
    resetBall();
}

void PlayingState::handleEvents(const sf::Event& event) {
    if (event.is<sf::Event::KeyPressed>()) {
        if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>()) {
            if (keyPressed->scancode == sf::Keyboard::Scancode::Escape) {    
                game.changeState(std::make_unique<PauseState>(game));
            }
        }
    }
}

void PlayingState::update(float dt) {

    if (!ball || !player || !bot) return;

    player->update(dt);

    bot->update(dt, *ball);

    ball->update(dt);
    
    if (!ball || !player || !bot) return;

    sf::FloatRect ballBounds = ball->getBounds();
    sf::FloatRect playerBounds = player->getBounds();
    sf::FloatRect botBounds = bot->getBounds();

    if (ballBounds.findIntersection(playerBounds).has_value() && playerBounds.position.x > 0) {
        float ballRight = ballBounds.position.x + ballBounds.size.x;
        float paddleRight = playerBounds.position.x + playerBounds.size.x;
        if (ballRight > playerBounds.position.x) {
            ball->setPosition(sf::Vector2f(paddleRight + ball->getRadius(), ball->getPosition().y));
            
        }
        hitSound->play();
        ball->bounceHorizontal(playerBounds);
    }
    if (ballBounds.findIntersection(botBounds).has_value() && botBounds.position.x > 0) {
        float ballLeft = ballBounds.position.x;
        float botLeft = botBounds.position.x;
        if (ballLeft < botLeft + botBounds.size.x) {
            ball->setPosition(sf::Vector2f(botLeft - ball->getRadius(), ball->getPosition().y));
        }
        hitSound->play();
        ball->bounceHorizontal(botBounds);
    }

    
    auto& score = game.getScoreManager();
    if (ball->outOfBoundsLeft()) {
        score.incrementBot();
        goalSound->play();
        resetBall();

    } else if (ball->outOfBoundsRight()) {
        score.incrementPlayer();
        goalSound->play();
        resetBall();
    }

    if (score.getPlayerScore() >= Constants::MAX_GOALS) {
        game.changeState(std::make_unique<GameOverState>(game,GameResult::Victory)); 
    } else if (score.getBotScore() >= Constants::MAX_GOALS) {
        game.changeState(std::make_unique<GameOverState>(game,GameResult::Defeat));
    }
}

void PlayingState::render(sf::RenderWindow& window) {
    sf::RectangleShape line(sf::Vector2f(Constants::LINE_OFFSET * 2, Constants::SCREEN_HEIGHT));
    line.setFillColor(sf::Color(100, 100, 100));
    line.setPosition(sf::Vector2f((Constants::SCREEN_WIDTH / 2) - Constants::LINE_OFFSET, 0));
    window.draw(line);

    player->render(window);
    bot->render(window);
    ball->render(window);

    uiManager.render(window, game.getScoreManager().getPlayerScore(), game.getScoreManager().getBotScore());
}

void PlayingState::resetBall() {
    ball->resetPosition(); 

    float xDir = Random::sign();

    sf::Vector2f newVel(xDir, Random::floatInRange(-0.3f, 0.3f));
    float length = std::hypot(newVel.x, newVel.y);
    if (length > 0.1f) {
        newVel.x /= length;
        newVel.y /= length;
    }

    ball->setVelocity(newVel);
    ball->setSpeed(ball->getInitialSpeed());
}