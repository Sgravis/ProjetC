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
#include "visuel.h"
#include "structure_log.h"
#include "interaction.h"
#include "agglomeration.h"
#define HFENETRE 1628.0
#define LFENETRE 680.0

int main(int argc, char** argv)
{

    int result;
    route=0;
    ind_dyn=-1;
    routeHide=0;
    logs tlog;
    FILE *fp;
    int nb_lignes;
    fp=fopen("geoloc-logs.txt","r");
    nb_lignes=nombre_lignes(fp);
    init_tableau_global(nb_lignes);
    recuperation_donnees(fp,nb_lignes);
    fclose(fp);
    recuperation_addr();


    logGlobalClean=copie_tableau(logGlobal,logGlobal.tailleTab);
    initialisation_route();
    agglomeration();
    //log_aff.taille=0;
   // ajout_log_aff(&logGlobalClean);
    recuperation_addr();
    //afficher_tableau(logGlobalClean.tailleTab,logGlobalClean);

    log_aff.taille=0;
    ajout_log_aff(&logGlobalClean);

    gtk_init_check(&argc, &argv);
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(window, "destroy",gtk_main_quit,NULL);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), HFENETRE,LFENETRE);
    gtk_window_set_title(GTK_WINDOW(window), "Bourges");


    pVBox = gtk_vbox_new(FALSE, 0);

    menu_bar(pVBox);

    gtk_container_add(GTK_CONTAINER(window), pVBox);

    darea = gtk_drawing_area_new();
    gtk_container_add(GTK_CONTAINER(pVBox), darea);
    g_signal_connect(G_OBJECT(darea), "draw", G_CALLBACK(on_draw),&logGlobalClean);
    gtk_widget_set_events (darea, GDK_BUTTON_PRESS_MASK | GDK_POINTER_MOTION_MASK | GDK_POINTER_MOTION_HINT_MASK);
    g_signal_connect(G_OBJECT(darea), "button_press_event", G_CALLBACK (on_click_map), NULL);
    init_map();

    gtk_widget_set_size_request(window, 1628, 680);
    gtk_window_set_resizable(GTK_WINDOW(window),FALSE);
    gtk_widget_show_all(window); //affichage de la fenetre

    gtk_widget_hide(Item_cacher_pt_route);
    gtk_widget_hide(Item_afficher_pt_route);
    gtk_widget_hide(Item_retirer_routes);
    gtk_widget_hide(Item_retour_pt_normaux);
    gtk_widget_hide(Item_cacher_pt_interet);

    gtk_main();  // fonction de boucle de gtk
  
    return 0;
}

