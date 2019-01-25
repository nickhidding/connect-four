
#include <iostream>

#include "Game.h"
#include "GtkView.h"

using namespace connectfour;

int main(int argc, char *argv[]) {
    std::cout << "Starting ConnectFour" << std::endl;

    Game game(2);
    GtkView view(argc, argv);

    std::cout << "Application stopped." << std::endl;
    return 0; // status;
}
