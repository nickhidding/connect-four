
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

    class GtkView : public IView {
    public:
        GtkView(const GtkView&) = default;
        GtkView(GtkView&&) = default;
        GtkView& operator=(const GtkView&) = default;
        GtkView& operator=(GtkView&&) = default;
        ~GtkView() = default;

        GtkView(Game *game, int argc, char **argv);

        void update();

        void showWindow(GtkApplication *app, gpointer user_data);
        void showMenu(GtkApplication *app, gpointer user_data);
        void removeMenu(GtkApplication *app, gpointer user_data);
        void startGame(int players);
        void showGame(GtkApplication *app, gpointer user_data);

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
    };
}

#endif
