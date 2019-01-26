
#include "GtkView.h"

using namespace std;
using namespace connectfour;

static void activate(GtkApplication *app, gpointer user_data) {
    ((GtkView*)user_data)->showWindow(app, user_data);
    ((GtkView*)user_data)->showMenu(app, user_data);
}

GtkView::GtkView(Game *game, int argc, char **argv) {
    // Attach to game updates
    m_game = game;
    m_game->attach(*this);

    // Show GTK window
    m_current_view = GtkViews::MENU;
    m_app = gtk_application_new ("nl.xyza.connectfour", G_APPLICATION_FLAGS_NONE);
    g_signal_connect (m_app, "activate", G_CALLBACK (activate), this);
    m_status = g_application_run (G_APPLICATION (m_app), argc, argv);
    g_object_unref(m_app);
}

static void startSinglePlayerButtonClicked(GtkWidget *widget, gpointer data) {
    ((GtkView*)data)->startGame(1);
}

static void startTwoPlayersButtonClicked(GtkWidget *widget, gpointer data) {
    ((GtkView*)data)->startGame(2);
}

void GtkView::showWindow(GtkApplication *app, gpointer user_data) {
    // Create window
    window = gtk_application_window_new (app);
    gtk_window_set_default_size (GTK_WINDOW (window), 800, 800);

    // Create header
    header = gtk_header_bar_new ();
    gtk_header_bar_set_show_close_button (GTK_HEADER_BAR (header), TRUE);
    gtk_header_bar_set_title (GTK_HEADER_BAR (header), "Connect Four");
    gtk_header_bar_set_has_subtitle (GTK_HEADER_BAR (header), FALSE);
    gtk_window_set_titlebar (GTK_WINDOW (window), header);

    // Show components
    gtk_widget_show_all (window);
}

void GtkView::showMenu(GtkApplication *app, gpointer user_data) {
    // Add button box
    button_box = gtk_button_box_new (GTK_ORIENTATION_HORIZONTAL);
    gtk_button_box_set_layout (GTK_BUTTON_BOX(button_box), GTK_BUTTONBOX_CENTER);
    gtk_box_set_spacing (GTK_BOX(button_box), 40);
    gtk_container_add (GTK_CONTAINER (window), button_box);

    // Add single player button
    button_single_player = gtk_button_new_with_label ("1 Player");
    g_signal_connect (button_single_player, "clicked", G_CALLBACK (startSinglePlayerButtonClicked), this);
    gtk_container_add (GTK_CONTAINER (button_box), button_single_player);

    // Add two players button
    button_two_players = gtk_button_new_with_label ("2 Players");
    g_signal_connect (button_two_players, "clicked", G_CALLBACK (startTwoPlayersButtonClicked), this);
    gtk_container_add (GTK_CONTAINER (button_box), button_two_players);
    
    gtk_widget_show_all (window);
}

void GtkView::removeMenu(GtkApplication *app, gpointer user_data) {
    gtk_container_foreach (GTK_CONTAINER (button_box), (GtkCallback) gtk_widget_destroy, NULL);
    gtk_container_remove (GTK_CONTAINER(window), button_box);
}

void GtkView::startGame(int players) {
    std::cout << "GtkView.cpp -> startGame(players=" << players << ")" << std::endl;
    m_game->start(players);
}

void GtkView::showGame(GtkApplication *app, gpointer user_data) {
    // Remove menu
    removeMenu(app, user_data);

    // Show Game Grid


}

void GtkView::update() {
    switch (m_game->getState())
    {
        case GameState::MENU:
            if (m_current_view != GtkViews::MENU) {
                showMenu(m_app, NULL);
                std::cout << "GtkView.cpp -> MENU" << std::endl;
            }

            break;
        case GameState::STARTED:
            if (m_current_view != GtkViews::GAME) {
                std::cout << "GtkView.cpp -> STARTED" << std::endl;
                showGame(m_app, NULL);
            }
            
            break;
        default:
            break;
    }
}
