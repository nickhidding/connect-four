
#include "GtkView.h"

using namespace std;
using namespace connectfour;

GtkView::GtkView(Game *game, int argc, char **argv) {
    // Attach to game updates
    m_game = game;
    m_game->attach(*this);

    // Show GTK window
    m_current_view = GtkViews::MENU;
    m_app = gtk_application_new ("nl.xyza.connectfour", G_APPLICATION_FLAGS_NONE);
    g_signal_connect (m_app, "activate", G_CALLBACK (+[](GtkApplication *app, gpointer user_data) {
        ((GtkView*)user_data)->showWindow();
        ((GtkView*)user_data)->showMenu();
    }), this);
    m_status = g_application_run (G_APPLICATION (m_app), argc, argv);
    g_object_unref(m_app);
}

void GtkView::showWindow() {
    // Create window
    window = gtk_application_window_new (m_app);
    gtk_window_set_default_size (GTK_WINDOW (window), 800, 800);

    // Create header
    header = gtk_header_bar_new ();
    gtk_header_bar_set_show_close_button (GTK_HEADER_BAR (header), TRUE);
    gtk_header_bar_set_title (GTK_HEADER_BAR (header), "Connect Four");
    gtk_header_bar_set_has_subtitle (GTK_HEADER_BAR (header), FALSE);
    gtk_window_set_titlebar (GTK_WINDOW (window), header);

    gtk_widget_show_all (window);
}

void GtkView::showMenu() {
    m_current_view = GtkViews::MENU;

    // Add button box
    button_box = gtk_button_box_new (GTK_ORIENTATION_HORIZONTAL);
    gtk_button_box_set_layout (GTK_BUTTON_BOX(button_box), GTK_BUTTONBOX_CENTER);
    gtk_box_set_spacing (GTK_BOX(button_box), 20);
    gtk_container_add (GTK_CONTAINER (window), button_box);

    // Add single player button
    button_single_player = gtk_button_new_with_label ("1 Player");
    g_signal_connect (button_single_player, "clicked", G_CALLBACK (+[](GtkWidget *widget, gpointer data) { 
        ((GtkView*)data)->m_game->start(1);
    }), this);
    gtk_container_add (GTK_CONTAINER (button_box), button_single_player);

    // Add two players button
    button_two_players = gtk_button_new_with_label ("2 Players");
    g_signal_connect (button_two_players, "clicked", G_CALLBACK (+[](GtkWidget *widget, gpointer data) {
        ((GtkView*)data)->m_game->start(2);
    }), this);
    gtk_container_add (GTK_CONTAINER (button_box), button_two_players);
    
    gtk_widget_show_all (window);
}

void GtkView::removeMenu() {
    gtk_widget_destroy(button_box);
}

void GtkView::showGame() {
    m_current_view = GtkViews::GAME;

    game_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(window), game_box);
    gtk_container_set_border_width(GTK_CONTAINER(game_box), 8);

    // Game information header
    game_information = gtk_frame_new("Information");
    gtk_box_pack_start(GTK_BOX(game_box), game_information, FALSE, FALSE, 0);

    game_frame_box = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 8);
    gtk_container_set_border_width (GTK_CONTAINER (game_frame_box), 8);
    gtk_container_add (GTK_CONTAINER (game_information), game_frame_box);

    game_menu_button = gtk_button_new_with_label("Menu");
    g_signal_connect(game_menu_button, "clicked", G_CALLBACK(+[](GtkWidget *widget, gpointer user_data) {
        ((GtkView*)user_data)->m_game->reset();
    }), this);
    gtk_box_pack_start(GTK_BOX(game_frame_box), game_menu_button, FALSE, FALSE, 0);

    game_frame_current_player = gtk_label_new ("Current player: ");
    gtk_box_pack_start (GTK_BOX (game_frame_box), game_frame_current_player, FALSE, FALSE, 0);

    // Create field
    game_grid = gtk_grid_new();

    for (int column = 0; column <= 7; column++) {
        GtkWidget *button;
        button = gtk_button_new_with_label(("select " + std::to_string(column)).c_str());
        gtk_grid_attach(GTK_GRID(game_grid), button, column, 0, 1, 1);
    }

    for (int column = 0; column <= 7; column++) {
        for (int row = 6; row >= 0; row--) {
            GtkWidget *button;
            button = gtk_button_new_with_label((std::to_string(column) + "," + std::to_string(row)).c_str());
            gtk_grid_attach(GTK_GRID(game_grid), button, column, row, 1, 1);
        }
    }

    gtk_box_pack_start(GTK_BOX(game_box), game_grid, FALSE, FALSE, 0);

    gtk_widget_show_all(window);
}

void GtkView::removeGame() {
    gtk_widget_destroy(game_box);
}

void GtkView::updateGame() {
    std::cout << "GtkView.cpp -> update field" << std::endl;

    // Display current player
    Player current_player = m_game->getCurrentPlayer();
    std::string current_player_text = "<span color=\"" + current_player.getColor() + "\">Current player: " + current_player.getName() + "</span>";
    gtk_label_set_markup(GTK_LABEL(game_frame_current_player), current_player_text.c_str());
}

void GtkView::update() {
    switch (m_game->getState())
    {
        case GameState::MENU:
            if (m_current_view != GtkViews::MENU) {
                removeGame();
                showMenu();
            }

            break;
        case GameState::STARTED:
            if (m_current_view != GtkViews::GAME) {
                removeMenu();
                showGame();
                updateGame();
            } else {
                updateGame();
            }
            
            break;
        default:
            break;
    }
}
