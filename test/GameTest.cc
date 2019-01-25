
#include "../src/Game.h"
#include "../src/Player.h"
#include <gtest/gtest.h>

TEST(GameTest, ConstructorSinglePlayer) {
    connectfour::Game game(1);
    std::vector<connectfour::Player> players = game.getPlayers();
    ASSERT_EQ(2, players.size());
    ASSERT_EQ(false, players.at(0).getAi());
    ASSERT_EQ(true, players.at(1).getAi());
}

TEST(GameTest, ConstructorTwoPlayers) {
    connectfour::Game game(2);
    std::vector<connectfour::Player> players = game.getPlayers();
    ASSERT_EQ(2, players.size());
    ASSERT_EQ(false, players.at(0).getAi());
    ASSERT_EQ(false, players.at(1).getAi());
}

TEST(GameTest, ConstructorInvalidPlayers) {
    ASSERT_THROW(connectfour::Game game(3), std::invalid_argument);
    ASSERT_THROW(connectfour::Game game(0), std::invalid_argument);
}
