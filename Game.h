
#ifndef GAME_H_
#define GAME_H_

#include "Player.h"

namespace ConnectFour {
    class Game {
        public:

            Game();
            ~Game();

        private:
            Player * m_players[2];
            int m_current_player;
    };
}

#endif
