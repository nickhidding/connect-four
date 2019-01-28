
#ifndef FIELD_H_
#define FIELD_H_

#include <iostream>
#include <vector>

#include "Cell.h"

namespace connectfour {
    
    class Field {
    public:
        Field(const Field&) = default;
        Field(Field&&) = default;
        Field& operator=(const Field&) = default;
        Field& operator=(Field&&) = default;
        
        Field(int width, int height);

        ~Field();

        int getWidth() const;
        int getHeight() const;

        void reset();

        bool isFull() const;

        Cell* cellAt(unsigned int x, unsigned int y) const;

        std::vector<std::vector<Cell>> getCells() const;

        bool setDiscAt(unsigned int x, unsigned int y, Player *player);

        bool dropDiscAt(unsigned int x, Player *player);

        Player* checkForWin();

    private:
        int m_width;
        int m_height;
        std::vector<std::vector<Cell>> m_cells;
    };
}

#endif
