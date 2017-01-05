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
    //time_t i;
    int result;
    route=0;
    ind_dyn=-1;
    logs tlog;
    FILE *fp;
    int nb_lignes;
    fp=fopen("geoloc-logs.txt","r");
    nb_lignes=Nombre_lignes(fp);
    Init_tableau_global(nb_lignes);
    recuperation_donnees(fp,nb_lignes);
    fclose(fp);
    logGlobalClean=CopieTableau(logGlobal,logGlobal.tailleTab);
	logGlobalClean=agglomeration(logGlobal);
    logGlobalClean=initialisation_route(logGlobalClean);
    //afficher_tableau(logGlobalClean.tailleTab,logGlobalClean);

    recuperation_addr();


    gtk_init_check(&argc, &argv);
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(window, "destroy",gtk_main_quit,NULL);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), HFENETRE,LFENETRE);
    gtk_window_set_title(GTK_WINDOW(window), "Bourges");

        // init box
    pHBox = gtk_hbox_new(FALSE, 0);
    pVBox = gtk_vbox_new(TRUE, 0);
    gtk_container_add(GTK_CONTAINER(window), pHBox);


    darea = gtk_drawing_area_new();
    gtk_container_add(GTK_CONTAINER(pHBox), darea);
    g_signal_connect(G_OBJECT(darea), "draw", G_CALLBACK(on_draw), NULL);
    gtk_widget_set_events (darea, GDK_BUTTON_PRESS_MASK | GDK_POINTER_MOTION_MASK | GDK_POINTER_MOTION_HINT_MASK);
    g_signal_connect(G_OBJECT(darea), "button_press_event", G_CALLBACK (on_click_map), NULL);
    init_map();

    logGlobalClean=initialisation_route(logGlobalClean);
        //init boutons
    Button_dyn = gtk_button_new_with_label("Mode dynamique");
    g_signal_connect(G_OBJECT(Button_dyn), "clicked",G_CALLBACK(mode_dynamique),NULL);
    Button_anonyme = gtk_button_new_with_label("anonymisation");
    g_signal_connect(G_OBJECT(Button_anonyme), "clicked", G_CALLBACK(do_anonymous), NULL);
    Button_stat = gtk_button_new_with_label("Mode statique");
    g_signal_connect(G_OBJECT(Button_stat), "clicked",G_CALLBACK(mode_statique),NULL);
    Button_road = gtk_button_new_with_label("route");
    g_signal_connect(G_OBJECT(Button_road), "clicked",G_CALLBACK(do_route),NULL);
    Button_noroad = gtk_button_new_with_label("retirer route");
    g_signal_connect(G_OBJECT(Button_noroad), "clicked",G_CALLBACK(undo_route),NULL);
    Button_pt_interet = gtk_button_new_with_label("enlever point d'interet");
    g_signal_connect(G_OBJECT(Button_pt_interet), "clicked",G_CALLBACK(detection_pt_interet),NULL);


    gtk_box_pack_start(GTK_BOX(pVBox), Button_anonyme, TRUE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(pVBox), Button_dyn, TRUE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(pVBox), Button_stat, TRUE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(pVBox), Button_road, TRUE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(pVBox), Button_noroad, TRUE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(pVBox), Button_pt_interet, TRUE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(pHBox), pVBox, FALSE, FALSE, 0); 

    gtk_widget_show_all(window); //affichage de la fenetre
    gtk_widget_hide(Button_stat);
    gtk_widget_hide(Button_noroad);
    gtk_main();  // fonction de boucle de gtk
  
    return 0;
}

