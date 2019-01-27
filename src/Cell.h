
#ifndef CELL_H_
#define CELL_H_

#include <iostream>

#include "Player.h"

namespace connectfour {

    class Cell {
    public:
        Cell(const Cell& cell) = default;
        Cell(Cell&& cell) = default;
        Cell& operator=(const Cell& cell) = default;
        Cell& operator=(Cell&& cell) = default;

        Cell();
        ~Cell();

        bool isEmpty() const;

        void setPlayer(Player *player);

        Player* getPlayer();

    private:
        Player *m_player;
    };
}

#endif
