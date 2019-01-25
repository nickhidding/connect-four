
#ifndef GAME_H_
#define GAME_H_

#include <stdexcept>
#include <vector>

#include "Player.h"

namespace connectfour {

    class Game {
    public:
        Game(const Game&) = default;
        Game(Game&&) = default;
        Game& operator=(const Game&) = default;
        Game& operator=(Game&&) = default;
        ~Game() = default;
        
        Game(int players);

        std::vector<Player> getPlayers() const;
    private:
        std::vector<Player> m_players;
        int m_current_player;
    };
}

#endif
