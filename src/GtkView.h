
#ifndef GTKVIEW_H_
#define GTKVIEW_H_

#include <iostream>
#include <gtk/gtk.h>

#include "Game.h"
#include "IView.h"
#include "GameState.h"

namespace connectfour {

    enum class GtkViews {
        MENU,
        GAME
    };

    class DropDiscEventData {
    public:
        IView *view;
        int column;
        DropDiscEventData(IView *v, int c) : view(v), column(c) {};
    };

    class GtkView : public IView {
    public:
        GtkView(const GtkView&) = default;
        GtkView(GtkView&&) = default;
        GtkView& operator=(const GtkView&) = default;
        GtkView& operator=(GtkView&&) = default;
        ~GtkView() = default;
        int getExitStatus() const {
            return m_status;
        };

        GtkView(Game *game, int argc, char **argv);

        void update(); // Receive updates from Game

        void showWindow();

        // Menu
        void showMenu();
        void removeMenu();

        // Field
        void showGame();
        void removeGame();
        void updateGame();

    private:
        GtkApplication *m_app;
        Game *m_game;
        int m_status;

        GtkViews m_current_view;

        // GTK components
        GtkWidget *window;
        GtkWidget *header;

        // GTK menu components
        GtkWidget *button_single_player;
        GtkWidget *button_two_players;
        GtkWidget *button_box;

        // GTK game components
        GtkWidget *game_box;
        GtkWidget *game_information;
        GtkWidget *game_frame_box;
        GtkWidget *game_frame_current_player;
        GtkWidget *game_menu_button;
        GtkWidget *game_grid;
    };
}

#endif
