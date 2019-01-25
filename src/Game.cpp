
#include "Game.h"

using namespace std;
using namespace connectfour;

Game::Game(int players) {
    if (players < 1 || players > 2) {
        throw std::invalid_argument("invalid number of players");
    }
    
    m_players.push_back(Player("Player 1", false, "red"));
    m_players.push_back(Player("Player 2", (players == 1), "blue"));
}

std::vector<Player> Game::getPlayers() const {
    return std::vector<Player>(m_players);
}
