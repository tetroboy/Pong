#pragma once
#include <vector>
#include <functional>

enum class GameEvent { PlayerGoal, BotGoal, Hit };

class Observer {
public:
    virtual ~Observer() = default;
    virtual void onNotify(GameEvent event) = 0;
};

class ScoreManager {
private:
    int playerScore = 0;
    int botScore = 0;
    std::vector<Observer*> observers;

public:
    void incrementPlayer();
    void incrementBot();
    void registerObserver(Observer* obs);
    void notify(GameEvent event);
    int getPlayerScore() const { return playerScore; }
    int getBotScore() const { return botScore; }
};