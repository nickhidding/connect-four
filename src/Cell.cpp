
#include "Cell.h"

using namespace std;
using namespace connectfour;

Cell::Cell() {
    m_player = nullptr;
    m_marked = false;
}

Cell::~Cell() {}

bool Cell::isEmpty() const {
    return m_player == nullptr;
}

void Cell::setPlayer(Player *player) {
    m_player = player;
}

Player* Cell::getPlayer() const {
    return m_player;
}

void Cell::setMarked(bool mark) {
    m_marked = mark;
}

bool Cell::isMarked() const {
    return m_marked;
}
