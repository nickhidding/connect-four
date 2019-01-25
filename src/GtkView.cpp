
#include "GtkView.h"

using namespace std;
using namespace connectfour;

static void print_hello (GtkWidget *widget, gpointer data) {
    g_print ("Hello World\n");
}

static void activate (GtkApplication *app, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *button;
    GtkWidget *button_box;

    window = gtk_application_window_new (app);
    gtk_window_set_title (GTK_WINDOW (window), "Connect Four");
    gtk_window_set_default_size (GTK_WINDOW (window), 800, 800);

    button_box = gtk_button_box_new (GTK_ORIENTATION_HORIZONTAL);
    gtk_container_add (GTK_CONTAINER (window), button_box);

    button = gtk_button_new_with_label ("Hello World");
    g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);
    g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), window);
    gtk_container_add (GTK_CONTAINER (button_box), button);

    gtk_widget_show_all (window);
}

GtkView::GtkView(Game *game, int argc, char **argv) {
    // Attach to game updates
    m_game = game;
    m_game->attach(*this);

    // Show GTK window
    m_app = gtk_application_new ("nl.xyza.connectfour", G_APPLICATION_FLAGS_NONE);
    g_signal_connect (m_app, "activate", G_CALLBACK (activate), NULL);
    m_status = g_application_run (G_APPLICATION (m_app), argc, argv);
    g_object_unref(m_app);
}

void GtkView::update() {
    std::cout << "GtkView.cpp -> update()" << std::endl;
}
