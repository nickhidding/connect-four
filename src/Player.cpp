
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
