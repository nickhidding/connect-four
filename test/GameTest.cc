
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../src/Game.h"
#include "../src/Player.h"
#include "../src/IView.h"

using ::testing::AtLeast;

TEST(GameTest, StartSinglePlayer) {
    connectfour::Game game;
    game.start(1);
    std::vector<connectfour::Player> players = game.getPlayers();
    ASSERT_EQ(2, players.size());
    ASSERT_EQ(false, players.at(0).getAi());
    ASSERT_EQ(true, players.at(1).getAi());
}

TEST(GameTest, ConstructorTwoPlayers) {
    connectfour::Game game;
    game.start(2);
    std::vector<connectfour::Player> players = game.getPlayers();
    ASSERT_EQ(2, players.size());
    ASSERT_EQ(false, players.at(0).getAi());
    ASSERT_EQ(false, players.at(1).getAi());
}

TEST(GameTest, ConstructorInvalidPlayers) {
    connectfour::Game game;
    ASSERT_THROW(game.start(3), std::invalid_argument);
    ASSERT_THROW(game.start(0), std::invalid_argument);
}

class MockView : public connectfour::IView {
public:
    MOCK_METHOD0(update, void());
};

TEST(GameTest, AttachView) {
    connectfour::Game game;
    MockView view1;
    MockView view2;

    game.attach(view1);
    game.attach(view2);

    ASSERT_EQ(2, game.getObservers().size());
    ASSERT_EQ(view1, *game.getObservers().at(0));
    ASSERT_EQ(view2, *game.getObservers().at(1));
}

TEST(GameTest, DetachExistingView) {
    connectfour::Game game;
    MockView view1;
    MockView view2;
    game.attach(view1);
    game.attach(view2);

    game.detach(view1);

    ASSERT_EQ(1, game.getObservers().size());
    ASSERT_EQ(view2, *game.getObservers().at(0));
}

TEST(GameTest, DetachUnattachedView) {
    connectfour::Game game;
    MockView view1;
    MockView view2;
    game.attach(view2);

    game.detach(view1);

    ASSERT_EQ(1, game.getObservers().size());
    ASSERT_EQ(view2, *game.getObservers().at(0));
}

TEST(GameTest, NotifyViews) {
    connectfour::Game game;
    MockView view1;
    MockView view2;
    EXPECT_CALL(view1, update()).Times(1);
    EXPECT_CALL(view2, update()).Times(1);

    game.attach(view1);
    game.attach(view2);
    game.notify();
}
