#include "PlayingState.h"
#include <iostream>
#include <SFML/Window/Keyboard.hpp>

PlayingState::PlayingState(Game& g) : GameState(g) {
    auto& factory = game.getFactory();
    auto& score = game.getScoreManager();

    auto playerPaddle = factory.createPlayerPaddle();
    auto botPaddle = factory.createBotPaddle();
    auto ball = factory.createBall();

    botPaddle->setDifficulty(game.getDifficulty());

    entities.push_back(std::move(playerPaddle));
    entities.push_back(std::move(botPaddle));
    entities.push_back(std::move(ball));

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
    auto* ball = dynamic_cast<Ball*>(entities[2].get());
    auto* player = dynamic_cast<PlayerPaddle*>(entities[0].get());  // если PlayerPaddle отдельный класс
    auto* bot = dynamic_cast<BotPaddle*>(entities[1].get());

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
        ball->reset();

    } else if (ball->outOfBoundsRight()) {
        score.incrementPlayer();
        goalSound->play();
        ball->reset();
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

    for (auto& entity : entities) entity->render(window);

    uiManager.render(window, game.getScoreManager().getPlayerScore(), game.getScoreManager().getBotScore());
}