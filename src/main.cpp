
#include <iostream>

#include "Game.h"
#include "GtkView.h"

using namespace connectfour;

int main(int argc, char *argv[]) {
    std::cout << "Starting ConnectFour" << std::endl;

    Game game;
    GtkView view(&game, argc, argv);

    std::cout << "Application stopped." << std::endl;
    return view.getExitStatus();
}
