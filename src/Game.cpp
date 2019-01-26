
#include "Game.h"

using namespace std;
using namespace connectfour;

Game::Game() : m_game_state(GameState::MENU) {}

void Game::start(int players) {
    if (players < 1 || players > 2) {
        throw std::invalid_argument("invalid number of players");
    }
    
    m_players.push_back(Player("Player 1", false, "red"));
    m_players.push_back(Player("Player 2", (players == 1), "yellow"));
    m_current_player = 0;
    m_game_state = GameState::STARTED;
    notify();
}

void Game::reset() {
    m_players.clear();
    m_current_player = 0;
    m_game_state = GameState::MENU;
    notify();
}

GameState Game::getState() const {
    return m_game_state;
}

std::vector<Player> Game::getPlayers() const {
    return std::vector<Player>(m_players);
}

Player Game::getCurrentPlayer() const {
    return m_players.at(m_current_player);
}

void Game::dropDisc(int x) {
    std::cout << "dropDisc " + std::to_string(x) << std::endl;
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
