
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
