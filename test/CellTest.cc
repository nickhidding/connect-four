
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../src/Cell.h"
#include "../src/Player.h"

class MockPlayer : public connectfour::Player {
public:
    MockPlayer() : Player("Name", false, "green") {};
};

TEST(CellTest, ConstructorEmptyCell) {
    connectfour::Cell cell;
    ASSERT_EQ(true, cell.isEmpty()); 
    ASSERT_EQ(nullptr, cell.getPlayer());
}

TEST(CellTest, Destructor) {
    connectfour::Cell *cell = new connectfour::Cell();
    MockPlayer *player = new MockPlayer();
    cell->setPlayer(player);
    delete cell;
    ASSERT_EQ("Name", player->getName());
}

TEST(CellTest, SetPlayer) {
    connectfour::Cell *cell = new connectfour::Cell();
    MockPlayer *player = new MockPlayer();
    cell->setPlayer(player);

    ASSERT_EQ(false, cell->isEmpty());
    ASSERT_EQ(player, cell->getPlayer());
    ASSERT_EQ(player->getName(), cell->getPlayer()->getName());
}

TEST(CellTest, CopyConstructor) {
    connectfour::Cell *cell = new connectfour::Cell();
    MockPlayer *player = new MockPlayer();
    cell->setPlayer(player);

    connectfour::Cell *copy = new connectfour::Cell(*cell);

    ASSERT_NE(cell, copy);
    ASSERT_EQ(player, cell->getPlayer());
    ASSERT_EQ(player, copy->getPlayer());
}

TEST(CellTest, Marked) {
    connectfour::Cell *cell = new connectfour::Cell();
    ASSERT_EQ(false, cell->isMarked());
    cell->setMarked(true);
    ASSERT_EQ(true, cell->isMarked());
    cell->setMarked(false);
    ASSERT_EQ(false, cell->isMarked());
}
