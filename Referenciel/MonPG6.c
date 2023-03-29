#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>

int fibonacci(int n)
{
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

void on_button_clicked(GtkWidget *button, gpointer user_data)
{
    // obtenir le nombre d'éléments souhaité depuis l'entrée de l'utilisateur
    GtkWidget *entry = (GtkWidget *)user_data;
    const char *text = gtk_entry_get_text(GTK_ENTRY(entry));
    int n = atoi(text);

    // calculer les nombres de Fibonacci
    long long *fib = malloc(n * sizeof(long long));
    for (int i = 0; i < n; i++)
    {
        fib[i] = fibonacci(i);
    }

    // construire une chaîne de caractères contenant les nombres de Fibonacci calculés
    char output[100];
    snprintf(output, sizeof(output), "%lld", fib[0]);
    for (int i = 1; i < n; i++)
    {
        char tmp[20];
        snprintf(tmp, sizeof(tmp), ", %lld", fib[i]);
        strcat(output, tmp);
    }

    // mettre à jour le label avec la chaîne de caractères contenant les nombres de Fibonacci calculés
    GtkWidget *label = (GtkWidget *)g_object_get_data(G_OBJECT(button), "label");
    gtk_label_set_text(GTK_LABEL(label), output);

    // libérer la mémoire allouée pour le tableau fib
    free(fib);
}

int main(int argc, char *argv[])
{
    // initialiser GTK
    gtk_init(&argc, &argv);

    // créer une fenêtre et un conteneur vertical
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Fibonacci");
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

    // créer une étiquette pour la demande de l'utilisateur
    GtkWidget *label1 = gtk_label_new("Entrez le nombre de nombres de Fibonacci que vous souhaitez calculer:");
    gtk_box_pack_start(GTK_BOX(vbox), label1, TRUE, TRUE, 0);

    // créer une entrée pour que l'utilisateur entre le nombre de nombres de Fibonacci souhaité
    GtkWidget *entry = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(vbox), entry, TRUE, TRUE, 0);

    // créer un bouton pour lancer le calcul
    GtkWidget *button = gtk_button_new_with_label("Calculer");
    gtk_box_pack_start(GTK_BOX(vbox), button, TRUE, TRUE, 0);

    // créer une étiquette pour afficher les résultats du calcul
    GtkWidget *label2 = gtk_label_new("");
    gtk_box_pack_start(GTK_BOX(vbox), label2, TRUE, TRUE, 0);

    // lier l'étiquette de sortie au bouton pour pouvoir la mettre à jour plus tard
    g_object_set_data(G_OBJECT(button), "label", label2);

    // connecter le signal de clic du bouton à la fonction on_button_clicked
    g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), entry);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // afficher la fenêtre
    gtk_widget_show_all(window);

    gtk_main();

    return EXIT_SUCCESS;
}