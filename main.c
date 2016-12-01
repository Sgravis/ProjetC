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
     int i;
     logs tlog;
     FILE *fp;
     int nb_lignes;
     fp=fopen("geoloc-logs.txt","r");
     nb_lignes=Nombre_lignes(fp);
     Init_tableau(nb_lignes);
     printf("\nnombre de lignes dans le fichier :%i \n",nb_lignes);
     recuperation_donnees(fp,nb_lignes);
     fclose(fp);
     //logGlobalClean=CopieTableau(logGlobal,logGlobal.tailleTab);
     //detection_pt_interet();
     printf("taille du tableau tlog : %d\n",logGlobalClean.tailleTab);


GtkWidget *window;    /*creation fenetre*/
GtkWidget *darea;     /*creation zone de dessin sur la fenetre*/

/*initialisation fenetre*/
gtk_init(&argc, &argv);
window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
darea = gtk_drawing_area_new();
gtk_container_add(GTK_CONTAINER(window), darea);
g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

/*dessinage carte et points*/
g_signal_connect(G_OBJECT(darea), "draw", G_CALLBACK(on_draw), NULL);

/*positionnement de la fenetre*/
gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
gtk_window_set_default_size(GTK_WINDOW(window), HFENETRE,LFENETRE);
gtk_window_set_title(GTK_WINDOW(window), "Bourges");
//gtk_window_set_resizable(GTK_WINDOW(window),FALSE); //un soucis ici


gtk_widget_show_all(window); //affichage de la fenetre


gtk_main();  // fonction de boucle de gtk


return 0;
 }