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

void init_boutton(){
    Button_dyn = gtk_button_new_with_label("Mode dynamique");
    g_signal_connect(G_OBJECT(Button_dyn), "clicked",G_CALLBACK(mode_dynamique),NULL);
    Button_anonyme = gtk_button_new_with_label("anonymisation");
    g_signal_connect(G_OBJECT(Button_anonyme), "clicked", G_CALLBACK(do_anonymous), NULL);
    Button_stat = gtk_button_new_with_label("Mode statique");
    g_signal_connect(G_OBJECT(Button_stat), "clicked",G_CALLBACK(mode_statique),NULL);
    Button_road = gtk_button_new_with_label("route");
    g_signal_connect(G_OBJECT(Button_road), "clicked",G_CALLBACK(do_route_maj),NULL);
    Button_noroad = gtk_button_new_with_label("retirer route");
    g_signal_connect(G_OBJECT(Button_noroad), "clicked",G_CALLBACK(undo_route),NULL);
    Button_pt_interet = gtk_button_new_with_label("enlever point d'interet");
    g_signal_connect(G_OBJECT(Button_pt_interet), "clicked",G_CALLBACK(detection_pt_interet),NULL);
    Button_Remise_a_0 = gtk_button_new_with_label("Remise a zero");
    g_signal_connect(G_OBJECT(Button_Remise_a_0), "clicked",G_CALLBACK(remise_a_zero),NULL);
    Button_Affichage_pt_supp = gtk_button_new_with_label("Affichage pts supp");
    g_signal_connect(G_OBJECT(Button_Affichage_pt_supp), "clicked",G_CALLBACK(resurrection_point),NULL);
    Button_Remise_pt_normal = gtk_button_new_with_label("Remise point normal");
    g_signal_connect(G_OBJECT(Button_Remise_pt_normal), "clicked",G_CALLBACK(remise_pt_normal),NULL);

    g_signal_connect (G_OBJECT (window), "key_press_event",G_CALLBACK (on_key_press), NULL);

    gtk_box_pack_start(GTK_BOX(pVBox), Button_anonyme, TRUE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(pVBox), Button_dyn, TRUE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(pVBox), Button_stat, TRUE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(pVBox), Button_road, TRUE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(pVBox), Button_noroad, TRUE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(pVBox), Button_pt_interet, TRUE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(pVBox), Button_Remise_a_0, TRUE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(pVBox), Button_Affichage_pt_supp, TRUE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(pVBox), Button_Remise_pt_normal, TRUE, FALSE, 0);

    gtk_box_pack_start(GTK_BOX(pHBox), pVBox, FALSE, FALSE, 0); 
}

int main(int argc, char** argv)
{
    int result;
    route=0;
    ind_dyn=-1;
    logs tlog;
    FILE *fp;
    int nb_lignes;
    gpointer* data;
    data=&logGlobalClean;
    fp=fopen("geoloc-logs.txt","r");
    nb_lignes=nombre_lignes(fp);
    init_tableau_global(nb_lignes);
    recuperation_donnees(fp,nb_lignes);
    fclose(fp);
    recuperation_addr();
    //afficher_tableau(base_adresse.tailleTab,base_adresse);
    afficher_tableau(logGlobalClean.tailleTab,logGlobalClean);
    initialisation_route(logGlobalClean);
    agglomeration(logGlobal);
    logGlobalClean=copie_tableau(logGlobal,logGlobal.tailleTab);
    log_aff.taille=0;
    ajout_log_aff(&logGlobalClean);
    gtk_init_check(&argc, &argv);
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(window, "destroy",gtk_main_quit,NULL);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), HFENETRE,LFENETRE);
    gtk_window_set_title(GTK_WINDOW(window), "Bourges");
    gtk_window_set_resizable(GTK_WINDOW(window),TRUE);

        // init box
    pHBox = gtk_hbox_new(FALSE, 0);
    pVBox = gtk_vbox_new(TRUE, 0);
    gtk_container_add(GTK_CONTAINER(window), pHBox);


    darea = gtk_drawing_area_new();
    gtk_container_add(GTK_CONTAINER(pHBox), darea);
    g_signal_connect(G_OBJECT(darea), "draw", G_CALLBACK(on_draw),&logGlobalClean);
    gtk_widget_set_events (darea, GDK_BUTTON_PRESS_MASK | GDK_POINTER_MOTION_MASK | GDK_POINTER_MOTION_HINT_MASK);
    g_signal_connect(G_OBJECT(darea), "button_press_event", G_CALLBACK (on_click_map), NULL);
    init_map();


    //initialisation_route(logGlobalClean);
    
    //logGlobalClean=initialisation_route(logGlobalClean);

    init_boutton();

    gtk_widget_show_all(window); //affichage de la fenetre
    gtk_widget_hide(Button_stat);
    gtk_widget_hide(Button_noroad);
    gtk_widget_hide(Button_Remise_pt_normal);
    affichage_points_interets();
    gtk_main();  // fonction de boucle de gtk
  
    return 0;
}

