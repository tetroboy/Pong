#include "ScoreManager.h"

void ScoreManager::incrementPlayer() {
    m_playerScore++;
    notify(GameEvent::PlayerGoal);
}

void ScoreManager::incrementBot() {
    m_botScore++;
    notify(GameEvent::BotGoal);
}

void ScoreManager::registerObserver(Observer* obs) {
    m_observers.push_back(obs);
}

void ScoreManager::notify(GameEvent event) {
    for (auto* obs : m_observers) {
        obs->onNotify(event);
    }
}