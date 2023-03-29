#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <gtk/gtk.h>
#include <math.h>

void on_number_clicked(GtkButton *button, gpointer user_data);
void on_equals_clicked(GtkButton *button, gpointer user_data);
void on_clear_clicked(GtkButton *button, gpointer user_data);
void on_operator_clicked(GtkButton *button, gpointer user_data);

void calculate();
GtkWidget *button0, *button1, *button2, *button3, *button4, *button5, *button6, *button7, *button8, *button9, *buttonplus, *buttonmoins, *buttonfois, *buttondiv, *buttonegal, *buttonclear;
GtkWidget *resultat;
double current_val = 0;
double new_val = 0;
char current_op = '+';

int main(int argc, char **argv)
{

    GtkWidget *window;
    GtkBuilder *builder;
    // Initialisation de GTK+
    gtk_init(NULL, NULL);
    // Création de la fenêtre
    builder = gtk_builder_new_from_file("./glade/calculatrice.glade");
    window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_title(GTK_WINDOW(window), "Calculatrice");

    // Récupération des widgets
    button0 = GTK_WIDGET(gtk_builder_get_object(builder, "button0"));
    button1 = GTK_WIDGET(gtk_builder_get_object(builder, "button1"));
    button2 = GTK_WIDGET(gtk_builder_get_object(builder, "button2"));
    button3 = GTK_WIDGET(gtk_builder_get_object(builder, "button3"));
    button4 = GTK_WIDGET(gtk_builder_get_object(builder, "button4"));
    button5 = GTK_WIDGET(gtk_builder_get_object(builder, "button5"));
    button6 = GTK_WIDGET(gtk_builder_get_object(builder, "button6"));
    button7 = GTK_WIDGET(gtk_builder_get_object(builder, "button7"));
    button8 = GTK_WIDGET(gtk_builder_get_object(builder, "button8"));
    button9 = GTK_WIDGET(gtk_builder_get_object(builder, "button9"));
    buttonplus = GTK_WIDGET(gtk_builder_get_object(builder, "buttonplus"));
    buttonmoins = GTK_WIDGET(gtk_builder_get_object(builder, "buttonmoins"));
    buttonfois = GTK_WIDGET(gtk_builder_get_object(builder, "buttonfois"));
    buttondiv = GTK_WIDGET(gtk_builder_get_object(builder, "buttondiv"));
    buttonegal = GTK_WIDGET(gtk_builder_get_object(builder, "buttonegal"));
    buttonclear = GTK_WIDGET(gtk_builder_get_object(builder, "buttonclear"));
    resultat = GTK_WIDGET(gtk_builder_get_object(builder, "resultat"));

    // Connexion des signaux
    g_signal_connect(button0, "clicked", G_CALLBACK(on_number_clicked), NULL);
    g_signal_connect(button1, "clicked", G_CALLBACK(on_number_clicked), NULL);
    g_signal_connect(button2, "clicked", G_CALLBACK(on_number_clicked), NULL);
    g_signal_connect(button3, "clicked", G_CALLBACK(on_number_clicked), NULL);
    g_signal_connect(button4, "clicked", G_CALLBACK(on_number_clicked), NULL);
    g_signal_connect(button5, "clicked", G_CALLBACK(on_number_clicked), NULL);
    g_signal_connect(button6, "clicked", G_CALLBACK(on_number_clicked), NULL);
    g_signal_connect(button7, "clicked", G_CALLBACK(on_number_clicked), NULL);
    g_signal_connect(button8, "clicked", G_CALLBACK(on_number_clicked), NULL);
    g_signal_connect(button9, "clicked", G_CALLBACK(on_number_clicked), NULL);
    g_signal_connect(buttonplus, "clicked", G_CALLBACK(on_operator_clicked), NULL);
    g_signal_connect(buttonmoins, "clicked", G_CALLBACK(on_operator_clicked), NULL);
    g_signal_connect(buttonfois, "clicked", G_CALLBACK(on_operator_clicked), NULL);
    g_signal_connect(buttondiv, "clicked", G_CALLBACK(on_operator_clicked), NULL);
    g_signal_connect(buttonegal, "clicked", G_CALLBACK(on_equals_clicked), NULL);
    g_signal_connect(buttonclear, "clicked", G_CALLBACK(on_clear_clicked), NULL);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Affichage de la fenêtre
    gtk_builder_connect_signals(builder, NULL);
    g_object_unref(builder);
    gtk_widget_show(window);
    gtk_main();

    return EXIT_SUCCESS;
}
// changement d'operateur
void calculate()
{
    switch (current_op)
    {
    case '+':
        current_val += new_val;
        break;
    case '-':
        current_val -= new_val;
        break;
    case 'x':
        current_val *= new_val;
        break;
    case '/':
        current_val /= new_val;
        break;
    default:
        break;
    }
}
// appuie du bouton 1 2 3 4 5 6 7 8 9 0
void on_number_clicked(GtkButton *button, gpointer user_data)
{
    const gchar *text = gtk_button_get_label(button);
    char buffer[50];
    snprintf(buffer, 50, "%.0f%s", new_val, text);
    new_val = atof(buffer);
    printf("current_val = %f, new_val = %f\n", current_val, new_val);
    gtk_label_set_text(GTK_LABEL(resultat), buffer);
}
// appuie du bouton + - x /
void on_operator_clicked(GtkButton *button, gpointer user_data)
{
    calculate();
    const gchar *text = gtk_button_get_label(button);
    printf("current_val = %f, new_val = %f\n", current_val, new_val);
    gtk_label_set_text(GTK_LABEL(resultat), text);
    current_op = text[0];
    new_val = 0;
}
// appuie du bouton =
void on_equals_clicked(GtkButton *button, gpointer user_data)
{
    calculate();
    char buffer[50];
    snprintf(buffer, 50, "%.2f", current_val);
    printf("current_val = %f, new_val = %f\n", current_val, new_val);
    gtk_label_set_text(GTK_LABEL(resultat), buffer);
    new_val = 0;
}
// appuie du bouton C
void on_clear_clicked(GtkButton *button, gpointer user_data)
{
    current_val = 0;
    new_val = 0;
    gtk_label_set_text(GTK_LABEL(resultat), "");
}