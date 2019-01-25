
#ifndef PLAYER_H_
#define PLAYER_H_

#include <string>

namespace connectfour {
    
    class Player {
    public:
        Player(const Player&) = default;
        Player(Player&&) = default;
        Player& operator=(const Player&) = default;
        Player& operator=(Player&&) = default;
        ~Player() = default;

        Player(std::string name,
               bool ai,
               std::string color);

        std::string getName() const;

        bool getAi() const;

        std::string getColor() const;
    private:
        std::string m_name;
        bool m_ai;
        std::string m_color;
    };
}

#endif
