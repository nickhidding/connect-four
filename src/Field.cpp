
#include "Field.h"

using namespace std;
using namespace connectfour;

Field::Field(unsigned int width,
             unsigned int height)
        :
        m_width(width),
        m_height(height) {
    if (width < 1 || height < 1) {
        throw std::invalid_argument("invalid field size");
    }

    for (unsigned int x = 0; x < width; x++) {
        m_cells.push_back(std::vector<Cell>());
        for (unsigned int y = 0; y < height; y++) {
            m_cells[x].push_back(Cell());
        }
    }
}

Field::~Field() {
    for (unsigned int x = 0; x < m_width; x++) {
        m_cells[x].clear();
    }
    m_cells.clear();
}

int Field::getWidth() const {
    return m_width;
}

int Field::getHeight() const {
    return m_height;
}

void Field::reset() {
    for (unsigned int x = 0; x < m_width; x++) {
        for (unsigned int y = 0; y < m_height; y++) {
            m_cells[x][y].setPlayer(nullptr);
            m_cells[x][y].setMarked(false);
        }
    }
}

bool Field::isFull() const {
    bool emptyCellFound = false;
    for (unsigned int x = 0; x < m_width; x++) {
        for (unsigned int y = 0; y < m_height; y++) {
            if (m_cells[x][y].isEmpty()) {
                emptyCellFound = true;
                break;
            }
        }
    }
    
    return !emptyCellFound;
}

Cell Field::cellAt(unsigned int x, unsigned int y) const {
    if (x >= m_width || y >= m_height) {
        throw std::invalid_argument("invalid cell coordinates");
    }

    return Cell(m_cells[x][y]);
}

std::vector<std::vector<Cell>> Field::getCells() const {
    std::vector<std::vector<Cell>> copy;
    for (unsigned int x = 0; x < m_width; x++) {
        copy.push_back(std::vector<Cell>());
        for (unsigned int y = 0; y < m_height; y++) {
            copy[x].push_back(Cell(m_cells[x][y]));
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
    for (unsigned int i = 0; i < m_height; i++) {
        if (m_cells[x][i].isEmpty()) {
            emptyCellFound = true;
            setDiscAt(x, i, player);
            break;
        }
    }

    return emptyCellFound;
}

Player* Field::checkForWin() {
    int connected = 0;
    Player *connected_player = nullptr;

    // Horizontal
    for (unsigned int y = 0; y < m_height; y++) {
        connected = 0;
        connected_player = m_cells[0][y].getPlayer();
        for (unsigned int x = 0; x < m_width; x++) {
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
    for (unsigned int x = 0; x < m_width; x++) {
        connected = 0;
        connected_player = m_cells[x][0].getPlayer();
        for (unsigned int y = 0; y < m_height; y++) {
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

    // Diagonal: bottom-left to top-right
    //  ______________________
    //  |  |  |  |  |  |  |  |
    //  |__|__|__|__|__|__|__|
    //  |  |  |  |  |  |  |  |
    //  |__|__|__|__|__|__|__|
    //  |  |  |  |  |  |  |  |
    //  |__|__|__|__|__|__|__|
    //  |  |  |  |  |  |  |  |
    //  |x_|__|__|__|__|__|__|
    //  |  |  |  |  |  |  |  |
    //  |x_|__|__|__|__|__|__|
    //  |  |  |  |  |  |  |  |
    //  |x_|x_|x_|x_|__|__|__|
    for (unsigned int x = 0; x < m_width - 3; x++) {
        connected = 0;
        connected_player = m_cells[x][0].getPlayer();
        for (unsigned int y = 0; y < m_height && x+y < m_width; y++) {
            if (m_cells[x+y][y].getPlayer() != nullptr && m_cells[x+y][y].getPlayer() == connected_player) {
                connected++;
            } else {
                connected = 1;
                connected_player = m_cells[x+y][y].getPlayer();
            }

            if (connected >= 4) {
                m_cells[x+y][y].setMarked(true);
                m_cells[x+y-1][y-1].setMarked(true);
                m_cells[x+y-2][y-2].setMarked(true);
                m_cells[x+y-3][y-3].setMarked(true);
                return connected_player;
            }
        }
    }

    for (unsigned int y = 0; y < m_height - 3; y++) {
        connected = 0;
        connected_player = m_cells[0][y].getPlayer();
        for (unsigned int x = 0; x < m_width && y+x < m_height; x++) {
            if (m_cells[x][y+x].getPlayer() != nullptr && m_cells[x][y+x].getPlayer() == connected_player) {
                connected++;
            } else {
                connected = 1;
                connected_player = m_cells[x][y+x].getPlayer();
            }

            if (connected >= 4) {
                m_cells[x][y+x].setMarked(true);
                m_cells[x-1][y+x-1].setMarked(true);
                m_cells[x-2][y+x-2].setMarked(true);
                m_cells[x-3][y+x-3].setMarked(true);
                return connected_player;
            }
        }
    }

    // Diagonal: top-left to bottom-right
    //  ______________________
    //  |  |  |  |  |  |  |  |
    //  |x_|x_|x_|x_|__|__|__|
    //  |  |  |  |  |  |  |  |
    //  |x_|__|__|__|__|__|__|
    //  |  |  |  |  |  |  |  |
    //  |x_|__|__|__|__|__|__|
    //  |  |  |  |  |  |  |  |
    //  |__|__|__|__|__|__|__|
    //  |  |  |  |  |  |  |  |
    //  |__|__|__|__|__|__|__|
    //  |  |  |  |  |  |  |  |
    //  |__|__|__|__|__|__|__|
    for (unsigned int x = 0; x < m_width - 3; x++) {
        connected = 0;
        connected_player = m_cells[x][m_height-1].getPlayer();
        for (int y = m_height-1, offset = 0; y >= 0 && x+offset < m_width; y--, offset++) {
            if (m_cells[x+offset][y].getPlayer() != nullptr && m_cells[x+offset][y].getPlayer() == connected_player) {
                connected++;
            } else {
                connected = 1;
                connected_player = m_cells[x+offset][y].getPlayer();
            }

            if (connected >= 4) {
                m_cells[x+offset][y].setMarked(true);
                m_cells[x+offset-1][y+1].setMarked(true);
                m_cells[x+offset-2][y+2].setMarked(true);
                m_cells[x+offset-3][y+3].setMarked(true);
                return connected_player;
            }
        }
    }

    for (int y = m_height-1; y >= 3; y--) {
        connected = 0;
        connected_player = m_cells[0][y].getPlayer();
        for (int x = 0; ((unsigned int) x) < m_width && y-x >= 0; x++) {
            if (m_cells[x][y-x].getPlayer() != nullptr && m_cells[x][y-x].getPlayer() == connected_player) {
                connected++;
            } else {
                connected = 1;
                connected_player = m_cells[x][y-x].getPlayer();
            }

            if (connected >= 4) {
                m_cells[x][y-x].setMarked(true);
                m_cells[x-1][y-x+1].setMarked(true);
                m_cells[x-2][y-x+2].setMarked(true);
                m_cells[x-3][y-x+3].setMarked(true);
                return connected_player;
            }
        }
    }

    return nullptr;
}
