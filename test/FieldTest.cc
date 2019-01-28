
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../src/Cell.h"
#include "../src/Field.h"
#include "../src/Player.h"

using namespace connectfour;

class MockCell : public Cell {
public:
    MOCK_METHOD0(isEmpty, bool());
    MOCK_METHOD1(setPlayer, void(Player *player));
};

class MockPlayer : public connectfour::Player {
public:
    MockPlayer() : Player("Name", false, "green") {};
};

TEST(FieldTest, ConstructorInvalidSize) {
    ASSERT_THROW(new Field(0, 0), std::invalid_argument);
    ASSERT_THROW(new Field(1, 0), std::invalid_argument);
    ASSERT_THROW(new Field(0, 1), std::invalid_argument);
    ASSERT_NO_THROW(new Field(1, 1));
}

TEST(FieldTest, ConstructorCellsCreated) {
    Field *field = new Field(2, 4);
    ASSERT_EQ(2, field->getWidth());
    ASSERT_EQ(4, field->getHeight());

    Cell *cell = field->cellAt(1, 3);
    ASSERT_EQ(true, cell->isEmpty());
}

TEST(FieldTest, CellAtValidCoords) {
    Field *field = new Field(2, 4);
    Cell *cell = field->cellAt(1, 3);
    ASSERT_EQ(true, cell->isEmpty());
    cell = field->cellAt(0, 0);
    ASSERT_EQ(true, cell->isEmpty());
}

TEST(FieldTest, CellAtInvalidCoords) {
    Field *field = new Field(2, 4);
    ASSERT_THROW(field->cellAt(-1, -1), std::invalid_argument);
    ASSERT_THROW(field->cellAt(2, 4), std::invalid_argument);
    ASSERT_THROW(field->cellAt(1, 4), std::invalid_argument);
    ASSERT_THROW(field->cellAt(2, 3), std::invalid_argument);
    ASSERT_THROW(field->cellAt(3, 1), std::invalid_argument);
}

TEST(FieldTest, SetDiscAt) {
    Field *field = new Field(2, 4);
    MockPlayer *player = new MockPlayer();
    
    Cell *cell = field->cellAt(0, 0);
    ASSERT_EQ(true, cell->isEmpty());
    
    field->setDiscAt(0, 0, player);
    ASSERT_EQ(true, cell->isEmpty());

    cell = field->cellAt(0, 0);
    ASSERT_EQ(false, cell->isEmpty());
}

TEST(FieldTest, SetDiscAtInvalidCoords) {
    Field *field = new Field(2, 4);
    MockPlayer *player = new MockPlayer();
    ASSERT_THROW(field->setDiscAt(-1, -1, player), std::invalid_argument);
    ASSERT_THROW(field->setDiscAt(2, 4, player), std::invalid_argument);
    ASSERT_THROW(field->setDiscAt(1, 4, player), std::invalid_argument);
    ASSERT_THROW(field->setDiscAt(2, 3, player), std::invalid_argument);
    ASSERT_THROW(field->setDiscAt(3, 1, player), std::invalid_argument);
}

TEST(FieldTest, GetCells) {
    Field *field = new Field(2, 4);
    MockPlayer *player = new MockPlayer();
    field->setDiscAt(0, 0, player);
    std::vector<std::vector<Cell>> cells = field->getCells();
    ASSERT_EQ(false, cells[0][0].isEmpty());
    ASSERT_EQ(true, cells[1][3].isEmpty());
    ASSERT_EQ(2, cells.size());
    ASSERT_EQ(4, cells[0].size());
}

TEST(FieldTest, ResetField) {
    Field *field = new Field(2, 4);
    MockPlayer *player = new MockPlayer();
    field->setDiscAt(0, 0, player);
    std::vector<std::vector<Cell>> cells = field->getCells();
    ASSERT_EQ(false, cells[0][0].isEmpty());

    field->reset();

    cells = field->getCells();
    ASSERT_EQ(true, cells[0][0].isEmpty());
}

TEST(FieldTest, IsFull) {
    Field *field = new Field(2, 2);
    MockPlayer *player = new MockPlayer();
    field->setDiscAt(0, 0, player);
    ASSERT_EQ(false, field->isFull());
    field->setDiscAt(0, 1, player);
    field->setDiscAt(1, 0, player);
    field->setDiscAt(1, 1, player);
    ASSERT_EQ(true, field->isFull());
}

TEST(FieldTest, DropDiscAt) {
    Field *field = new Field(2, 2);
    MockPlayer *player = new MockPlayer();
    field->dropDiscAt(0, player);
    std::vector<std::vector<Cell>> cells = field->getCells();
    ASSERT_EQ(false, cells[0][0].isEmpty());
    ASSERT_EQ(true, cells[0][1].isEmpty());
}

TEST(FieldTest, CheckWinHorizontal) {
    Field *field = new Field(4, 4);
    MockPlayer *player = new MockPlayer();
    ASSERT_EQ(nullptr, field->checkForWin());
    field->setDiscAt(0, 1, player);
    field->setDiscAt(1, 1, player);
    field->setDiscAt(2, 1, player);
    field->setDiscAt(3, 1, player);
    ASSERT_EQ(player, field->checkForWin());
}

TEST(FieldTest, CheckWinVertical) {
    Field *field = new Field(4, 4);
    MockPlayer *player = new MockPlayer();
    ASSERT_EQ(nullptr, field->checkForWin());
    field->setDiscAt(1, 0, player);
    field->setDiscAt(1, 1, player);
    field->setDiscAt(1, 2, player);
    field->setDiscAt(1, 3, player);
    ASSERT_EQ(player, field->checkForWin());
}

TEST(FieldTest, CheckWinDiagonalBottomLeftToTopRight) {
    Field *field = new Field(6, 6);
    MockPlayer *player = new MockPlayer();
    ASSERT_EQ(nullptr, field->checkForWin());
    field->setDiscAt(1, 0, player);
    field->setDiscAt(2, 1, player);
    field->setDiscAt(3, 2, player);
    field->setDiscAt(4, 3, player);
    ASSERT_EQ(player, field->checkForWin());
    delete field;

    field = new Field(6, 6);
    player = new MockPlayer();
    ASSERT_EQ(nullptr, field->checkForWin());
    field->setDiscAt(0, 1, player);
    field->setDiscAt(1, 2, player);
    field->setDiscAt(2, 3, player);
    field->setDiscAt(3, 4, player);
    ASSERT_EQ(player, field->checkForWin());
}

TEST(FieldTest, CheckWinDiagonalTopLeftToBottomRight) {
    Field *field = new Field(6, 6);
    MockPlayer *player = new MockPlayer();
    ASSERT_EQ(nullptr, field->checkForWin());
    field->setDiscAt(4, 0, player);
    field->setDiscAt(3, 1, player);
    field->setDiscAt(2, 2, player);
    field->setDiscAt(1, 3, player);
    ASSERT_EQ(player, field->checkForWin());
    delete field;

    field = new Field(6, 6);
    player = new MockPlayer();
    ASSERT_EQ(nullptr, field->checkForWin());
    field->setDiscAt(5, 1, player);
    field->setDiscAt(4, 2, player);
    field->setDiscAt(3, 3, player);
    field->setDiscAt(2, 4, player);
    ASSERT_EQ(player, field->checkForWin());
}

TEST(FieldTest, CheckWinCellsMarked) {
    Field *field = new Field(4, 4);
    MockPlayer *player = new MockPlayer();
    field->setDiscAt(0, 1, player);
    field->setDiscAt(1, 1, player);
    field->setDiscAt(2, 1, player);
    field->setDiscAt(3, 1, player);
    field->checkForWin();

    ASSERT_TRUE(field->cellAt(0, 1)->isMarked());
    ASSERT_TRUE(field->cellAt(1, 1)->isMarked());
    ASSERT_TRUE(field->cellAt(2, 1)->isMarked());
    ASSERT_TRUE(field->cellAt(3, 1)->isMarked());
}
