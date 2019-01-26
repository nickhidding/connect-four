
#include "Game.h"

using namespace std;
using namespace connectfour;

Game::Game() : m_gameState(GameState::MENU) {}

void Game::start(int players) {
    if (players < 1 || players > 2) {
        throw std::invalid_argument("invalid number of players");
    }
    
    m_players.push_back(Player("Player 1", false, "red"));
    m_players.push_back(Player("Player 2", (players == 1), "blue"));
    m_current_player = 0;
    m_gameState = GameState::STARTED;
    notify();
}

GameState Game::getState() const {
    return m_gameState;
}

std::vector<Player> Game::getPlayers() const {
    return std::vector<Player>(m_players);
}

void Game::attach(IView &view) {
    m_observers.push_back(&view);
};

void Game::detach(IView &view) {
    auto itr = std::find(m_observers.begin(), m_observers.end(), &view);
    if (itr != m_observers.end())
        m_observers.erase(itr);
};

void Game::notify() {
    for (IView *observer : m_observers) {
        observer->update();
    }
};

std::vector<IView*> Game::getObservers() const {
    return std::vector<IView*>(m_observers);
};
