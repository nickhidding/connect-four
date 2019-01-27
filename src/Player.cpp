
#include "Player.h"

using namespace std;
using namespace connectfour;

Player::Player(std::string name,
               bool ai,
               std::string color)
        :
        m_name(name),
        m_ai(ai),
        m_color(color) {};

std::string Player::getName() const {
    return m_name;
};

void Player::setName(std::string name) {
    m_name = name;
};

bool Player::getAi() const {
    return m_ai;
};

std::string Player::getColor() const {
    return m_color;
};
