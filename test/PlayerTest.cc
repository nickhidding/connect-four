
#include <gtest/gtest.h>

#include "../src/Player.h"

using namespace connectfour;

TEST(PlayerTest, Constructor) {
    std::string name = "Name";
    bool ai = false;
    std::string color = "gold";

    Player player(name, ai, color);

    ASSERT_EQ(name, player.getName());
    ASSERT_EQ(ai, player.getAi());
    ASSERT_EQ(color, player.getColor());
}

TEST(PlayerTest, SetName) {
    Player player("Name", false, "gold");
    player.setName("New");
    ASSERT_EQ("New", player.getName());
}
