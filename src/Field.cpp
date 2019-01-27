
#include "Field.h"

using namespace std;
using namespace connectfour;

Field::Field(int width,
             int height)
        :
        m_width(width),
        m_height(height) {
    m_cells = new Cell*[width];
    for (int i = 0; i < width; i++) {
        m_cells[i] = new Cell[height];
    }
};

Field::~Field() {
    for (int i = 0; i < m_width; i++) {
        delete [] m_cells[i];
    }
    delete [] m_cells;
}

int Field::getWidth() const {
    return m_width;
}

int Field::getHeight() const {
    return m_height;
}

Cell* Field::cellAt(int x, int y) const {
    if (x >= m_width || y >= m_height) {
        throw std::invalid_argument("invalid cell coordinates");
    }

    return new Cell(m_cells[x][y]);
}

void Field::setDiscAt(int x, int y, Player *player) {
    if (x >= m_width || y >= m_height) {
        throw std::invalid_argument("invalid cell coordinates");
    }
    
    m_cells[x][y].setPlayer(player);
}
