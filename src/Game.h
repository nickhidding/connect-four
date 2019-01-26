
#ifndef GAME_H_
#define GAME_H_

#include <stdexcept>
#include <vector>
#include <algorithm>

#include "Player.h"
#include "IView.h"
#include "GameState.h"

namespace connectfour {

    class Game {
    public:
        Game(const Game&) = default;
        Game(Game&&) = default;
        Game& operator=(const Game&) = default;
        Game& operator=(Game&&) = default;
        ~Game() = default;
        
        Game();

        void start(int players);

        GameState getState() const;

        Player getCurrentPlayer() const;

        void getGrid(); // TODO return info

        void attach(IView &view);
        void detach(IView &view);
        void notify();
        std::vector<IView*> getObservers() const;

        std::vector<Player> getPlayers() const;
    private:
        GameState m_gameState;
        std::vector<Player> m_players;
        std::vector<IView*> m_observers;
        int m_current_player;
    };
}

#endif
