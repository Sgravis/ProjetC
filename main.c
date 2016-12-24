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
     /*printf("Affichage tableau global: \n\n\n");
     afficher_tableau(logGlobal.tailleTab,logGlobal);
     printf("Affichage tableau clean: \n\n\n");
     afficher_tableau(logGlobalClean.tailleTab,logGlobalClean);*/
     /*printf("Affichage tableau clean apres detection pt interet\n\n\n");
     afficher_tableau(logGlobalClean.tailleTab,logGlobalClean);*/


     
     //resurrection_point("BackupPoints.txt");
     /*printf("Affichage tableau de resurection des points: \n\n\n");
     afficher_tableau(logBack.tailleTab,logBack);*/
     /*printf("Affichage tableau adresse (que un bout): \n\n\n");*/ 
     recuperation_addr();
     //afficher_tableau(base_adresse.tailleTab,base_adresse);
     //afficher_tableau2();


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

        //init boutons
    pButton = gtk_button_new_with_label("anonymisation");
    g_signal_connect(G_OBJECT(pButton), "clicked", G_CALLBACK(do_anonymous), NULL);
       
    gtk_box_pack_start(GTK_BOX(pVBox), pButton, TRUE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(pHBox), pVBox, FALSE, FALSE, 0);
    
    //Voila la fonction pour faire une popup, passe la question en param, retourne 1 si il dit oui, 0 sinon
    //result =popup("anonymisation ?");

    
    gtk_widget_show_all(window); //affichage de la fenetre
    detection_pt_interet();

    gtk_main();  // fonction de boucle de gtk
  
    return 0;
}
