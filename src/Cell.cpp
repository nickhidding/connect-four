
#include "Cell.h"

using namespace std;
using namespace connectfour;

Cell::Cell() {
    m_player = nullptr;
};

Cell::~Cell() {
    delete m_player;
};

bool Cell::isEmpty() const {
    return m_player == nullptr;
}

void Cell::setPlayer(Player *player) {
    m_player = player;
}

Player* Cell::getPlayer() {
    return m_player;
}
