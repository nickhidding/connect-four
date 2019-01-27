
#include "Field.h"

using namespace std;
using namespace connectfour;

Field::Field(int width,
             int height)
        :
        m_width(width),
        m_height(height) {
    if (width < 1 || height < 1) {
        throw std::invalid_argument("invalid field size");
    }

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

Cell* Field::cellAt(unsigned int x, unsigned int y) const {
    if (x >= m_width || y >= m_height) {
        throw std::invalid_argument("invalid cell coordinates");
    }

    return new Cell(m_cells[x][y]);
}

Cell** Field::getCells() const {
    Cell **copy;
    copy = new Cell*[m_width];
    for (int x = 0; x < m_width; x++) {
        copy[x] = new Cell[m_height];
        for (int y = 0; y < m_height; y++) {
            copy[x][y] = Cell(m_cells[x][y]);
        }
    }

    return copy;
}

bool Field::setDiscAt(unsigned int x, unsigned int y, Player *player) {
    if (x >= m_width || y >= m_height) {
        throw std::invalid_argument("invalid cell coordinates");
    }

    if (m_cells[x][y].isEmpty()) {
        m_cells[x][y].setPlayer(player);
        return true;
    } else {
        return false;
    }
}

bool Field::dropDiscAt(unsigned int x, Player *player) {
    if (x >= m_width) {
        throw std::invalid_argument("invalid column coordinate");
    }

    bool emptyCellFound = false;
    for (int i = 0; i < m_height; i++) {
        if (m_cells[x][i].isEmpty()) {
            emptyCellFound = true;
            setDiscAt(x, i, player);
            break;
        }
    }

    return emptyCellFound;
}
