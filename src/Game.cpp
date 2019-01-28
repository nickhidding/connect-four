
#include "Game.h"

using namespace std;
using namespace connectfour;

Game::Game() : m_game_state(GameState::MENU) {
    m_field = new Field(7, 6);
    m_winning_player = nullptr;
}

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

Game::~Game() {
    delete m_field;
}

void Game::reset() {
    m_players.clear();
    m_current_player = 0;
    m_game_state = GameState::MENU;
    m_field->reset();
    m_winning_player = nullptr;
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

Player* Game::getWinningPlayer() const {
    return new Player(*m_winning_player);
}

Field* Game::getField() const {
    return new Field(*m_field);
}

void Game::dropDisc(int x) {
    if (m_field->dropDiscAt(x, &m_players.at(m_current_player))) {
        m_current_player = (m_current_player == 0) ? 1 : 0;
    }
    notify();
    update();
}

void Game::update() {
    // Check if field is completely filled
    if (m_field->isFull()) {
        m_game_state = GameState::ENDED;
        notify();
    }

    // Check if a player has won
    Player *winning_player = m_field->checkForWin();
    if (winning_player != nullptr) {
        m_game_state = GameState::ENDED;
        m_winning_player = winning_player;
        notify();
    }
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
