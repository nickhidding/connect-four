
#ifndef CELL_H_
#define CELL_H_

#include <iostream>

#include "Player.h"

namespace connectfour {

    class Cell {
    public:
        Cell(const Cell&) = default;
        Cell(Cell&&) = default;
        Cell& operator=(const Cell&) = default;
        Cell& operator=(Cell&&) = default;

        Cell();
        ~Cell();

        bool isEmpty() const;

        void setPlayer(Player *player);

        Player* getPlayer() const;

        void setMarked(bool mark);

        bool isMarked() const;

    private:
        Player *m_player;
        bool m_marked;
    };
}

#endif
