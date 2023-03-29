#include <gtk/gtk.h>
#include <stdlib.h>

// Structure qui stocke les informations de l'état du jeu
typedef struct
{
    int nombreMystere;
    int nombreEssais;
} EtatJeu;

// Fonction pour générer un nombre aléatoire entre 1 et 100
int genererNombreMystere()
{
    srand(time(NULL)); // Initialisation du générateur de nombres aléatoires
    return (rand() % 100) + 1;
}

// Fonction appelée lorsque l'utilisateur appuie sur le bouton "Valider"
void valider(GtkWidget *widget, gpointer data)
{
    EtatJeu *etat = (EtatJeu *)data;
    GtkWidget *input = GTK_WIDGET(g_object_get_data(G_OBJECT(widget), "input"));
    GtkWidget *resultat = GTK_WIDGET(g_object_get_data(G_OBJECT(widget), "resultat"));
    const char *saisie = gtk_entry_get_text(GTK_ENTRY(input));
    int valeurSaisie = atoi(saisie);
    char message[100];

    if (valeurSaisie < etat->nombreMystere)
    {
        sprintf(message, "Trop petit ! Il vous reste %d essais.", --etat->nombreEssais);
    }
    else if (valeurSaisie > etat->nombreMystere)
    {
        sprintf(message, "Trop grand ! Il vous reste %d essais.", --etat->nombreEssais);
    }
    else
    {
        sprintf(message, "Bravo, vous avez trouvé en %d essais !", 10 - etat->nombreEssais);
        gtk_widget_set_sensitive(input, FALSE);
        gtk_widget_set_sensitive(widget, FALSE);
    }

    gtk_label_set_text(GTK_LABEL(resultat), message);

    if (etat->nombreEssais == 0)
    {
        sprintf(message, "Perdu ! Le nombre mystère était %d.", etat->nombreMystere);
        gtk_label_set_text(GTK_LABEL(resultat), message);
        gtk_widget_set_sensitive(input, FALSE);
        gtk_widget_set_sensitive(widget, FALSE);
    }
}

// Fonction appelée lors de l'initialisation de l'interface graphique
void initialiser(GtkWidget *widget, gpointer data)
{
    EtatJeu *etat = (EtatJeu *)data;
    etat->nombreMystere = genererNombreMystere();
    etat->nombreEssais = 10;
}

int main(int argc, char *argv[])
{
    // Initialisation de GTK+
    gtk_init(&argc, &argv);
    // Création de la fenêtre principale
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Le juste prix");
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Création des widgets
    GtkWidget *vbox = gtk_box_new(TRUE, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    GtkWidget *label = gtk_label_new("Trouver le juste prix ! \n entre 1 et 100");
    gtk_box_pack_start(GTK_BOX(vbox), label, TRUE, TRUE, 0);

    GtkWidget *input = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(vbox), input, FALSE, FALSE, 0);

    GtkWidget *resultat = gtk_label_new("");
    gtk_box_pack_start(GTK_BOX(vbox), resultat, FALSE, FALSE, 0);

    GtkWidget *button = gtk_button_new_with_label("Valider");
    gtk_box_pack_start(GTK_BOX(vbox), button, FALSE, FALSE, 0);

    // Création de l'état du jeu
    EtatJeu etat;
    // connexion des signaux
    g_object_set_data(G_OBJECT(button), "input", input);
    g_object_set_data(G_OBJECT(button), "label", label);
    g_object_set_data(G_OBJECT(button), "resultat", resultat);
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(valider), &etat);
    g_signal_connect(G_OBJECT(window), "show", G_CALLBACK(initialiser), &etat);

    // Affichage de la fenêtre
    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}