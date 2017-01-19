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
    Button_road = gtk_button_new_with_label("route");
    g_signal_connect(G_OBJECT(Button_road), "clicked",G_CALLBACK(do_route_maj),NULL);
    Button_noroad = gtk_button_new_with_label("retirer route");
    g_signal_connect(G_OBJECT(Button_noroad), "clicked",G_CALLBACK(undo_route),NULL);
    Button_hidePoints = gtk_button_new_with_label("cacher les points des routes");
    g_signal_connect(G_OBJECT(Button_hidePoints), "clicked",G_CALLBACK(hidePoints),NULL);
    Button_showPoints = gtk_button_new_with_label("afficher les points des routes");
    g_signal_connect(G_OBJECT(Button_showPoints), "clicked",G_CALLBACK(showPoints),NULL);
    Button_pt_interet = gtk_button_new_with_label("enlever point d'interet");
    g_signal_connect(G_OBJECT(Button_pt_interet), "clicked",G_CALLBACK(detection_pt_interet),NULL);
    Button_Remise_a_0 = gtk_button_new_with_label("Remise a zero");
    g_signal_connect(G_OBJECT(Button_Remise_a_0), "clicked",G_CALLBACK(remise_a_zero),NULL);
    Button_Affichage_pt_supp = gtk_button_new_with_label("Affichage pts supp");
    g_signal_connect(G_OBJECT(Button_Affichage_pt_supp), "clicked",G_CALLBACK(resurrection_point),NULL);
    Button_Remise_pt_normal = gtk_button_new_with_label("Remise point normal");
    g_signal_connect(G_OBJECT(Button_Remise_pt_normal), "clicked",G_CALLBACK(remise_pt_normal),NULL);
    Button_Affichage_Points_Interets = gtk_button_new_with_label("Affichage points d'interets");
    g_signal_connect(G_OBJECT(Button_Affichage_Points_Interets), "clicked",G_CALLBACK(affichage_points_interets),NULL);
    Button_DesAffichage_Points_Interets = gtk_button_new_with_label("Cacher points d'interets");
    g_signal_connect(G_OBJECT(Button_DesAffichage_Points_Interets), "clicked",G_CALLBACK(cacher_points_interets),NULL);

    //gtk_widget_no_show_all(Button_noroad,true);

    g_signal_connect (G_OBJECT (window), "key_press_event",G_CALLBACK (on_key_press), NULL);

    gtk_box_pack_start(GTK_BOX(pHBox), Button_anonyme, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(pHBox), Button_dyn, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(pHBox), Button_road, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(pHBox), Button_noroad, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(pHBox), Button_hidePoints, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(pHBox), Button_showPoints, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(pHBox), Button_pt_interet, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(pHBox), Button_Remise_a_0, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(pHBox), Button_Affichage_pt_supp, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(pHBox), Button_Remise_pt_normal, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(pHBox), Button_Affichage_Points_Interets, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(pHBox), Button_DesAffichage_Points_Interets, FALSE, FALSE, 0);


    gtk_box_pack_start(GTK_BOX(pVBox), pHBox, FALSE, FALSE, 0); 
}

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
    reset_log_aff();
    ajout_log_aff(&logGlobalClean);

    gtk_init_check(&argc, &argv);
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(window, "destroy",gtk_main_quit,NULL);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), HFENETRE,LFENETRE);
    gtk_window_set_title(GTK_WINDOW(window), "Bourges");
    //gtk_widget_set_state_flags (window,GTK_APP_PAINTABLE,TRUE);

        // init box
    pHBox = gtk_hbox_new(FALSE, 0);
    pVBox = gtk_vbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(window), pVBox);
    init_boutton();

    darea = gtk_drawing_area_new();
    gtk_container_add(GTK_CONTAINER(pVBox), darea);
    g_signal_connect(G_OBJECT(darea), "draw", G_CALLBACK(on_draw),&logGlobalClean);
    gtk_widget_set_events (darea, GDK_BUTTON_PRESS_MASK | GDK_POINTER_MOTION_MASK | GDK_POINTER_MOTION_HINT_MASK);
    g_signal_connect(G_OBJECT(darea), "button_press_event", G_CALLBACK (on_click_map), NULL);
    init_map();


    //initialisation_route(logGlobalClean);
    
    //logGlobalClean=initialisation_route(logGlobalClean);
    gtk_widget_set_size_request(window, 1628, 680);
    gtk_window_set_resizable(GTK_WINDOW(window),FALSE);
    gtk_widget_show_all(window); //affichage de la fenetre
    gtk_widget_hide(Button_hidePoints);
    gtk_widget_hide(Button_showPoints);
    gtk_widget_hide(Button_noroad);
    gtk_widget_hide(Button_Remise_pt_normal);
    gtk_widget_hide(Button_DesAffichage_Points_Interets);


    gtk_main();  // fonction de boucle de gtk
  
    return 0;
}

