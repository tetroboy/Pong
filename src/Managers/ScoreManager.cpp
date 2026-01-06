#include "ScoreManager.h"

void ScoreManager::incrementPlayer() {
    playerScore++;
    notify(GameEvent::PlayerGoal);
}

void ScoreManager::incrementBot() {
    botScore++;
    notify(GameEvent::BotGoal);
}

void ScoreManager::registerObserver(Observer* obs) {
    observers.push_back(obs);
}

void ScoreManager::notify(GameEvent event) {
    for (auto* obs : observers) {
        obs->onNotify(event);
    }
}