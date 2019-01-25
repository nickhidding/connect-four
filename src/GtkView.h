
#ifndef GTKVIEW_H_
#define GTKVIEW_H_

#include <iostream>
#include <gtk/gtk.h>

#include "IView.h"

namespace connectfour {

    class GtkView {
    public:
        GtkView(const GtkView&) = default;
        GtkView(GtkView&&) = default;
        GtkView& operator=(const GtkView&) = default;
        GtkView& operator=(GtkView&&) = default;
        ~GtkView() = default;

        GtkView(int argc, char **argv);

        void update();

    private:
        GtkApplication *app;
        int status;
    };
}

#endif
