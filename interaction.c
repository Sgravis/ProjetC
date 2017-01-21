#include "interaction.h"



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

/**
 * detection du double clique pour l'actualisation du zoom
 */
void on_click_map(GtkWidget* darea, GdkEventButton* event, void* data)
{ 
    if (event->type==GDK_2BUTTON_PRESS )
    {
    	if(map.zoom==0){
            map.pos_x=event->x;
    		map.pos_y=event->y;
    		map.zoom++;
    	}
    	else{init_map();}
        //reset_anonymisation();
        maj_map();
    }
    if(anonyme_step==2)
    {
        x=event->x;
        y=event->y;
        anonyme_step=3;
        maj_map();
    }

    if(anonyme_step==1)
    {
        printf("event->x = %f  event->y =%f\n",event->x,event->y);
        
        pt_tampon.longitude=pixel_to_coord_long(event->x);
        pt_tampon.latitude=pixel_to_coord_lat(event->y);
        pt_tampon.taillept=20;
        maj_map();
        anonyme_step=2;
    }
}

/**
 * Cree une fenetre qui pose une quesion a l'utilisateur, retourne 1 si il repond OUI, 0 sinon
 */
int popup(char* nom)
{
	int result;
	GtkWidget *dialog;
	GtkDialogFlags flags = GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT;
	dialog = gtk_dialog_new_with_buttons (nom,GTK_WINDOW(window),flags,("Oui"),1,("Non"),0,NULL);
	result = gtk_dialog_run(GTK_DIALOG(dialog));
	gtk_widget_destroy (dialog);
	return result;
}

void popupclose(char* nom)
{
    GtkWidget *dialog;
    GtkDialogFlags flags = GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT;
    dialog = gtk_dialog_new_with_buttons (nom,GTK_WINDOW(window),flags,("OK"),1,NULL);
    gtk_window_set_default_size(GTK_WINDOW(dialog),300,50);
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy (dialog);
}

/**
 * commence la procédure d'anonymisation
 */
void do_anonymous(GtkWidget* pbutton, GdkEventButton* event, void* data)
{
    reset_anonymisation();
    anonyme_step=1;
}

void on_key_press(GtkWidget *widget, GdkEventKey *event)
{
   ///printf("%i\n",event->keyval);
    switch (event->keyval)
    {
        case 65361:
            map.pos_x-=5;
            maj_map();
            break;
        case 65363:
            map.pos_x+=5;
            maj_map();
            break;
        case 65362:
            map.pos_y-=5;
            maj_map();
            break;
        case 65364:
            map.pos_y+=5;
            maj_map();
            break;
    }
    
}