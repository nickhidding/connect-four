
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

void Field::reset() {
    for (int x = 0; x < m_width; x++) {
        for (int y = 0; y < m_height; y++) {
            m_cells[x][y].setPlayer(nullptr);
            m_cells[x][y].setMarked(false);
        }
    }
}

bool Field::isFull() const {
    bool emptyCellFound = false;
    for (int x = 0; x < m_width; x++) {
        for (int y = 0; y < m_height; y++) {
            if (m_cells[x][y].isEmpty()) {
                emptyCellFound = true;
                break;
            }
        }
    }
    
    return !emptyCellFound;
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

Player* Field::checkForWin() const {
    int connected = 0;
    Player *connected_player = nullptr;

    // Horizontal
    for (int y = 0; y < m_height; y++) {
        connected = 0;
        connected_player = m_cells[0][y].getPlayer();
        for (int x = 0; x < m_width; x++) {
            if (m_cells[x][y].getPlayer() != nullptr && m_cells[x][y].getPlayer() == connected_player) {
                connected++;
            } else {
                connected = 1;
                connected_player = m_cells[x][y].getPlayer();
            }

            if (connected >= 4) {
                m_cells[x][y].setMarked(true);
                m_cells[x-1][y].setMarked(true);
                m_cells[x-2][y].setMarked(true);
                m_cells[x-3][y].setMarked(true);
                return connected_player;
            }
        }
    }

    // Vertical
    for (int x = 0; x < m_width; x++) {
        connected = 0;
        connected_player = m_cells[x][0].getPlayer();
        for (int y = 0; y < m_height; y++) {
            if (m_cells[x][y].getPlayer() != nullptr && m_cells[x][y].getPlayer() == connected_player) {
                connected++;
            } else {
                connected = 1;
                connected_player = m_cells[x][y].getPlayer();
            }

            if (connected >= 4) {
                m_cells[x][y].setMarked(true);
                m_cells[x][y-1].setMarked(true);
                m_cells[x][y-2].setMarked(true);
                m_cells[x][y-3].setMarked(true);
                return connected_player;
            }
        }
    }

    /*
        ______________________
        |  |  |  |  |  |  |  |
        |__|__|__|__|__|__|__|
        |  |  |  |  |  |  |  |
        |__|__|__|__|__|__|__|
        |  |  |  |  |  |  |  |
        |__|__|__|__|__|__|__|
        |  |  |  |  |  |  |  |
        |x_|__|__|__|__|__|__|
        |  |  |  |  |  |  |  |
        |x_|__|__|__|__|__|__|
        |  |  |  |  |  |  |  |
        |x_|x_|x_|x_|__|__|__|

    */

    // Diagonal: bottom-left to top-right
    // for (int x = 0; x < m_width - 3; x++) {
    //     connected = 0;
    //     connected_player = m_cells[x][0].getPlayer();
    //     for (int y = 0; y < m_height && x+y < m_width; y++) {
    //         if (m_cells[x+y][y].getPlayer() != nullptr && m_cells[x+y][y].getPlayer() == connected_player) {
    //             connected++;
    //         } else {
    //             connected = 1;
    //             connected_player = m_cells[x+y][y].getPlayer();
    //         }

    //         if (connected >= 4) {
    //             m_cells[x][y].setMarked(true);
    //             // m_cells[x][y-1].setMarked(true);
    //             // m_cells[x][y-2].setMarked(true);
    //             // m_cells[x][y-3].setMarked(true);
    //             return connected_player;
    //         }
    //     }
    // }

    // Diagonal: top-left to bottom-right




    return nullptr;
}
