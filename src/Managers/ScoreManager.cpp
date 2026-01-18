#include "ScoreManager.h"

void ScoreManager::incrementPlayer() {
    m_playerScore++;
    notify(GameEvent::PlayerGoal);
}

void ScoreManager::incrementBot() {
    m_botScore++;
    notify(GameEvent::BotGoal);
}

void ScoreManager::registerObserver(std::shared_ptr<Observer> obs) {
    m_observers.emplace_back(obs);
}

void ScoreManager::unregisterObserver(std::shared_ptr<Observer> obs) {
    m_observers.erase(
        std::remove_if(m_observers.begin(), m_observers.end(),
            [&obs](const std::weak_ptr<Observer>& w) { return w.lock() == obs; }),
        m_observers.end()
    );
}

void ScoreManager::notify(GameEvent event) {
    for (auto it = m_observers.begin(); it != m_observers.end(); ) {
        if (auto obs = it->lock()) {
            obs->onNotify(*this, event);
            ++it;
        } else {
            it = m_observers.erase(it);
        }
    }
}