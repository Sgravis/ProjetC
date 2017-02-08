#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
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



int main(int argc, char** argv)
{

    int result;
    int i;
    id_en_cours=0;
    route=0;
    ind_dyn=-1;
    routeHide=0;
    logs tlog;
    FILE *fp;
    system("/home/sam/Documents/INSA/3A/1erSemestre/geoloc/ProjetC/integration_log.sh");

    fp=fopen("geoloc-logs.txt","r");
    recuperation_donnees(fp);
    fclose(fp);


        
    init_logparid();
    init_log_clean_id();

    recuperation_addr(); 
    printf("nb_id %i\n",nb_id );
    for(id_en_cours=0;id_en_cours<nb_id;id_en_cours++){   
        printf("id_en_cours %i\n",id_en_cours );
        agglomeration();
        initialisation_route();
    }
    
    id_en_cours=0;


    reset_log_aff();
    //ajout_log_aff(&logGlobalClean[id_en_cours]);

    gtk_init_check(&argc, &argv);
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(window, "destroy",gtk_main_quit,NULL);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), HFENETRE,LFENETRE);
    gtk_window_set_title(GTK_WINDOW(window), "Bourges");
    gtk_window_set_icon_from_file (GTK_WINDOW(window), "icone.jpg",NULL);

        // init box
    pHBox = gtk_hbox_new(FALSE, 0);
    pVBox = gtk_vbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(window), pVBox);
    init_boutton();

    darea = gtk_drawing_area_new();
    gtk_container_add(GTK_CONTAINER(pVBox), darea);
    g_signal_connect(G_OBJECT(darea), "draw", G_CALLBACK(on_draw),NULL);
    gtk_widget_set_events (darea, GDK_BUTTON_PRESS_MASK | GDK_POINTER_MOTION_MASK | GDK_POINTER_MOTION_HINT_MASK);
    g_signal_connect(G_OBJECT(darea), "button_press_event", G_CALLBACK (on_click_map), NULL);
    init_map();


    //initialisation_route(logGlobalClean[id_en_cours]);
    
    gtk_widget_set_size_request(window, HFENETRE,LFENETRE);
    gtk_window_set_resizable(GTK_WINDOW(window),FALSE);
    gtk_widget_show_all(window); 

    gtk_widget_hide(Button_hidePoints);
    gtk_widget_hide(Button_showPoints);
    gtk_widget_hide(Button_noroad);
    gtk_widget_hide(Button_Remise_pt_normal);
    gtk_widget_hide(Button_DesAffichage_Points_Interets);
    
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(Button_log1),TRUE);


    gtk_main();
    fopen("zero","w");
    remove("zero");
    fopen("un","w");
    remove("un");
    fopen("deux","w");
    remove("deux");
    fopen("trois","w");
    remove("trois");
    return 0;
}

