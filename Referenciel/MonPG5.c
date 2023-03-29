#include <gtk/gtk.h>

// Constantes
#define ROWS 3
#define COLS 3

// Game state
enum Player
{
    PLAYER_NONE,
    PLAYER_X,
    PLAYER_O
};
enum GameState
{
    STATE_PLAYING,
    STATE_GAMEOVER
};

// Widgets
GtkWidget *grid; // Grid container for the game board

// Game board
enum Player board[ROWS][COLS];
enum Player current_player;
enum GameState game_state;

// gestion de l'affichage
void initialize_board()
{
    int i, j;
    for (i = 0; i < ROWS; i++)
    {
        for (j = 0; j < COLS; j++)
        {
            board[i][j] = PLAYER_NONE;
        }
    }
}

// gestion du tour de jeu
void switch_player()
{
    current_player = (current_player == PLAYER_X) ? PLAYER_O : PLAYER_X;
}

// gestion de la fin de partie
void verifFin()
{
    int i, j;
    enum Player winner;

    // verif ligne
    for (i = 0; i < ROWS; i++)
    {
        winner = board[i][0];
        if (winner == PLAYER_NONE)
        {
            continue;
        }
        for (j = 1; j < COLS; j++)
        {
            if (board[i][j] != winner)
            {
                break;
            }
        }
        if (j == COLS)
        {
            game_state = STATE_GAMEOVER;

            return;
        }
    }

    // verif colonne
    for (j = 0; j < COLS; j++)
    {
        winner = board[0][j];
        if (winner == PLAYER_NONE)
        {
            continue;
        }
        for (i = 1; i < ROWS; i++)
        {
            if (board[i][j] != winner)
            {
                break;
            }
        }
        if (i == ROWS)
        {
            game_state = STATE_GAMEOVER;
            return;
        }
    }

    // verif diagonale
    winner = board[0][0];
    if (winner != PLAYER_NONE && winner == board[1][1] && winner == board[2][2])
    {
        game_state = STATE_GAMEOVER;
        return;
    }

    winner = board[0][2];
    if (winner != PLAYER_NONE && winner == board[1][1] && winner == board[2][0])
    {
        game_state = STATE_GAMEOVER;
        return;
    }

    // verif match nul
    for (i = 0; i < ROWS; i++)
    {
        for (j = 0; j < COLS; j++)
        {
            if (board[i][j] == PLAYER_NONE)
            {

                return;
            }
        }
    }

    game_state = STATE_GAMEOVER;
}

// gestion du clic sur une cellule
void on_cell_clicked(GtkWidget *widget, gpointer data)
{
    if (game_state == STATE_PLAYING)
    {
        int row = GPOINTER_TO_INT(g_object_get_data(G_OBJECT(widget), "row"));
        int col = GPOINTER_TO_INT(g_object_get_data(G_OBJECT(widget), "col"));

        if (board[row][col] == PLAYER_NONE)
        {
            board[row][col] = current_player;

            const char *label = (current_player == PLAYER_X) ? "X" : "O";
            gtk_button_set_label(GTK_BUTTON(widget), label);

            switch_player();
            verifFin();
        }
    }
}

// Creer la grille
void creerGrille()
{
    int i, j;
    for (i = 0; i < ROWS; i++)
    {
        for (j = 0; j < COLS; j++)
        {
            GtkWidget *cell = gtk_button_new_with_label("");
            g_object_set_data(G_OBJECT(cell), "row", GINT_TO_POINTER(i));
            g_object_set_data(G_OBJECT(cell), "col", GINT_TO_POINTER(j));
            g_signal_connect(cell, "clicked", G_CALLBACK(on_cell_clicked), NULL);

            gtk_grid_attach(GTK_GRID(grid), cell, j, i, 1, 1);
        }
    }
}

int main(int argc, char *argv[])
{
    GtkWidget *window;
    // initialisation de gtk+
    gtk_init(&argc, &argv);

    // creation de la fenetre
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Morpion");
    gtk_window_set_default_size(GTK_WINDOW(window), 200, 150);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    g_signal_connect(window, "delete-event", G_CALLBACK(gtk_main_quit), NULL);

    // creation de la grille
    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);
    initialize_board();
    current_player = PLAYER_X;
    game_state = STATE_PLAYING;

    // connexion des signaux
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // affichage de la fenetre
    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}