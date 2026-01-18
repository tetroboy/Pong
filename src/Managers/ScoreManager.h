#pragma once
#include <vector>
#include <functional>
#include <memory>

enum class GameEvent { PlayerGoal, BotGoal, Hit };

class ScoreManager;

class Observer {
public:
    virtual ~Observer() = default;
    virtual void onNotify(const ScoreManager& score, GameEvent event) = 0;
};

class ScoreManager {
private:
    int m_playerScore = 0;
    int m_botScore = 0;
    std::vector<std::weak_ptr<Observer>> m_observers;

public:
    void incrementPlayer();
    void incrementBot();
    void registerObserver(std::shared_ptr<Observer> obs);
    void unregisterObserver(std::shared_ptr<Observer> obs);
    void notify(GameEvent event);
    int getPlayerScore() const { return m_playerScore; }
    int getBotScore() const { return m_botScore; }
};