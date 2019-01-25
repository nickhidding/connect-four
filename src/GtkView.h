
#ifndef GTKVIEW_H_
#define GTKVIEW_H_

#include <iostream>
#include <gtk/gtk.h>

#include "Game.h"
#include "IView.h"

namespace connectfour {

    class GtkView : public IView {
    public:
        GtkView(const GtkView&) = default;
        GtkView(GtkView&&) = default;
        GtkView& operator=(const GtkView&) = default;
        GtkView& operator=(GtkView&&) = default;
        ~GtkView() = default;

        GtkView(Game *game, int argc, char **argv);

        void update();

    private:
        GtkApplication *m_app;
        Game *m_game;
        int m_status;
    };
}

#endif
