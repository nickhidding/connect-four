
#ifndef FIELD_H_
#define FIELD_H_

#include <iostream>

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

        Cell* cellAt(int x, int y) const;

        void setDiscAt(int x, int y, Player *player);

    private:
        int m_width;
        int m_height;
        Cell **m_cells;
    };
}

#endif
