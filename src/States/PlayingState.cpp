#include "PlayingState.h"
#include <iostream>
#include <SFML/Window/Keyboard.hpp>

PlayingState::PlayingState(Game& g) : GameState(g) {
    auto& factory = game.getFactory();
    auto& score = game.getScoreManager();

    m_player = factory.createPlayerPaddle();
    m_bot = factory.createBotPaddle();
    m_ball = factory.createBall();

    m_bot->setDifficulty(game.getDifficulty());

    if (!m_hitBuffer.loadFromFile("resources/hit.mp3")) {
        std::cout << "erro hit.mp3" << std::endl;
    }
    if (!m_goalBuffer.loadFromFile("resources/bounce.mp3")) {
        std::cout << "erro goal.mp3" << std::endl;
    }

    m_hitSound = std::make_unique<sf::Sound>(m_hitBuffer);
    m_goalSound = std::make_unique<sf::Sound>(m_goalBuffer);

    m_hitSound->setVolume(Constants::HIT_SOUND_VOLUME);
    m_goalSound->setVolume(Constants::GOAL_SOUND_VOLUME);

    score.registerObserver(std::shared_ptr<Observer>(&m_uiManager, [](Observer*){}));
    resetBall();
}

PlayingState::~PlayingState() {
    game.getScoreManager().unregisterObserver(std::shared_ptr<Observer>(&m_uiManager, [](Observer*){}));
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

    if (!m_ball || !m_player || !m_bot) return;

    m_player->update(dt);

    m_bot->update(dt, *m_ball);

    m_ball->update(dt);
    
    if (!m_ball || !m_player || !m_bot) return;

    sf::FloatRect ballBounds = m_ball->getBounds();
    sf::FloatRect playerBounds = m_player->getBounds();
    sf::FloatRect botBounds = m_bot->getBounds();

    if (ballBounds.findIntersection(playerBounds).has_value() && playerBounds.position.x > 0) {
        float ballRight = ballBounds.position.x + ballBounds.size.x;
        float paddleRight = playerBounds.position.x + playerBounds.size.x;
        if (ballRight > playerBounds.position.x) {
            m_ball->setPosition({paddleRight + m_ball->getRadius(), m_ball->getPosition().y});
            
        }
        m_hitSound->play();
        m_ball->bounceHorizontal(playerBounds);
    }
    if (ballBounds.findIntersection(botBounds).has_value() && botBounds.position.x > 0) {
        float ballLeft = ballBounds.position.x;
        float botLeft = botBounds.position.x;
        if (ballLeft < botLeft + botBounds.size.x) {
            m_ball->setPosition({botLeft - m_ball->getRadius(), m_ball->getPosition().y});
        }
        m_hitSound->play();
        m_ball->bounceHorizontal(botBounds);
    }

    
    auto& score = game.getScoreManager();
    if (m_ball->outOfBoundsLeft()) {
        score.incrementBot();
        m_goalSound->play();
        resetBall();

    } else if (m_ball->outOfBoundsRight()) {
        score.incrementPlayer();
        m_goalSound->play();
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
    line.setFillColor({100, 100, 100});
    line.setPosition({(Constants::SCREEN_WIDTH / 2) - Constants::LINE_OFFSET, 0});
    window.draw(line);

    m_player->render(window);
    m_bot->render(window);
    m_ball->render(window);

    m_uiManager.render(window, game.getScoreManager().getPlayerScore(), game.getScoreManager().getBotScore());
}

void PlayingState::resetBall() {
    m_ball->setPosition(sf::Vector2f(
        Constants::SCREEN_WIDTH / 2.0f,
        Constants::SCREEN_HEIGHT / 2.0f
    )); 

    float xDir = Random::sign();

    sf::Vector2f newVel(xDir, Random::floatInRange(-0.3f, 0.3f));
    float length = std::hypot(newVel.x, newVel.y);
    if (length > 0.1f) {
        newVel.x /= length;
        newVel.y /= length;
    }

    m_ball->setVelocity(newVel);
    m_ball->setSpeed(m_ball->getInitialSpeed());
}