#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <time.h>
#include "remplissage.h"
#include "allocation.h"
#include "suppression.h"
#include <math.h>
#include <string.h>
#include <cairo.h>
#include <gtk/gtk.h>
#include <math.h>
#include "cpprof.h"
#include "structure_log.h"
#define HFENETRE 1628.0
#define LFENETRE 680.0


int main(int argc, char** argv)
{
    logs tlog;
    FILE *fp;
    int nb_lignes;
    printf("tour 1\n");
    fp=fopen("geoloc-logs.txt","r");
    nb_lignes=Nombre_lignes(fp);
    Init_tableau(nb_lignes);
    printf("\nnombre de lignes dans le fichier :%i \n",nb_lignes);
    recuperation_donnees(fp,nb_lignes);
    fclose(fp);
    while(quit!=1)
    {
    GtkWidget *window;    //creation fenetre
    GtkWidget *darea;     //creation zone de dessin sur la fenetre
 
    //initialisation fenetre

    gtk_init_check(&argc, &argv);
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);


    darea = gtk_drawing_area_new();
    gtk_container_add(GTK_CONTAINER(window), darea);

    g_signal_connect(window, "destroy", G_CALLBACK(on_quit), &quit);
    gtk_widget_set_events (darea, GDK_BUTTON_PRESS_MASK | GDK_POINTER_MOTION_MASK | GDK_POINTER_MOTION_HINT_MASK);
    g_signal_connect(G_OBJECT(darea), "button_press_event", G_CALLBACK (on_click_map), NULL);

    //dessin de la carte et points
    g_signal_connect(G_OBJECT(darea), "draw", G_CALLBACK(on_draw), NULL);
    
    //positionnement de la fenetre
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), HFENETRE,LFENETRE);

    gtk_window_set_title(GTK_WINDOW(window), "Bourges");

    //gtk_window_set_resizable(GTK_WINDOW(window),FALSE); //un soucis ici
    gtk_widget_show_all(window); //affichage de la fenetre
    gtk_main();  // fonction de boucle de gtk
    }

    return 0;
}
    