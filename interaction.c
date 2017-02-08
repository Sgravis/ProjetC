#include "interaction.h"

void init_boutton(){


    Button_log1 = gtk_toggle_button_new_with_label("log 1");
    g_signal_connect(G_OBJECT(Button_log1), "clicked",G_CALLBACK(choix_logs),NULL);
    gtk_box_pack_start(GTK_BOX (pHBox), Button_log1, FALSE, FALSE, 0);
 
    Button_log2 = gtk_toggle_button_new_with_label("Log 2");
    g_signal_connect(G_OBJECT(Button_log2), "clicked",G_CALLBACK(choix_logs),NULL);
    gtk_box_pack_start(GTK_BOX (pHBox), Button_log2, FALSE, FALSE, 0);

    Button_log3 = gtk_toggle_button_new_with_label("Log 3");
    g_signal_connect(G_OBJECT(Button_log3), "clicked",G_CALLBACK(choix_logs),NULL);
    gtk_box_pack_start(GTK_BOX (pHBox), Button_log3, FALSE, FALSE, 0);


    g_signal_connect (G_OBJECT (window), "key_press_event",G_CALLBACK (on_key_press), NULL);

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
       
        pt_tampon.longitude=pixel_to_coord_long(event->x);
        pt_tampon.latitude=pixel_to_coord_lat(event->y);

        pt_tampon.taillept=20;
        maj_map();
        anonyme_step=2;
    }
    if(info_pt_inte==1)
    {   
        pt_x=event->x;
        pt_y=event->y;

        int i=0;
        int rue = NULL;
        char string[40] = "Aucun point d'interets trouvés";
        char string2[40]= "tempon";
        while (i<tableau_centre_interet[0].taillept+1){

                if (pt_x<coord_to_pixel_long(tableau_centre_interet[i].longitude)+(100/6) && pt_x>coord_to_pixel_long(tableau_centre_interet[i].longitude)-(100/6) && pt_y>coord_to_pixel_lat(tableau_centre_interet[i].latitude)-(100/6) && pt_y<coord_to_pixel_lat(tableau_centre_interet[i].latitude)+(100/6))
                {
        
                    rue = tableau_centre_interet[i].numero_rue ;
                    sprintf(string,"%d ",rue);
                    strcat(string,tableau_centre_interet[i].adresse);
                    sprintf(string2,"%d ",tableau_centre_interet[i].agglomerat);
                    strcat(string,"\n Le seuil est de : ");
                    strcat(string,string2);

                    break;
                }
                i++;
            }


        popup2(string);
        info_pt_inte=0;
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

void popup2(char* nom)
{
    GtkWidget *pDialog;
    gchar *sDialogText;
    sDialogText = g_strdup_printf(nom);
    pDialog = gtk_message_dialog_new(NULL,GTK_DIALOG_MODAL,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,sDialogText);
    gtk_dialog_run(GTK_DIALOG(pDialog));
    gtk_widget_destroy(pDialog);
    g_free(sDialogText);
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

void ouverture_logs()
{
    GtkWidget *nav;
    int res;
    GSList* list_logs;

    nav = gtk_file_chooser_dialog_new ("Ouvrir logs",GTK_WINDOW(window),GTK_FILE_CHOOSER_ACTION_OPEN,"Cancel",GTK_RESPONSE_CANCEL,"Open",GTK_RESPONSE_ACCEPT,NULL);
    GtkFileChooser *chooser = GTK_FILE_CHOOSER (nav);
    //gtk_file_filter_add_pattern(filtre, );
    //gtk_file_chooser_add_filter (chooser,filtre);
    gtk_file_chooser_set_select_multiple (chooser,TRUE);


    res = gtk_dialog_run (GTK_DIALOG (nav));
    if (res == GTK_RESPONSE_ACCEPT)
    {
        char *filename;
        list_logs = gtk_file_chooser_get_filenames (chooser);
        while (list_logs != NULL){
            printf("location du fichier : %s\n",(char*)list_logs->data);
            list_logs=list_logs->next;
        }
        g_slist_free(list_logs);
    }
    gtk_widget_destroy (nav);
}

void choix_logs()
{
    reset_log_aff();
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(Button_log1))){
        id_en_cours=0;
        ajout_log_aff(&logGlobalClean[0]);
    }
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(Button_log2))){
        id_en_cours=1;
        ajout_log_aff(&logGlobalClean[1]);
    }
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(Button_log3))){
        id_en_cours=2;
        ajout_log_aff(&logGlobalClean[2]);
    }
    maj_map();
}

void menu_bar(GtkWidget* widget){
    /******************************************************************/

        int nb_log;

    pMenuBar = gtk_menu_bar_new();
    /*Construction du menu route*/
    pMenu = gtk_menu_new();

    Item_route = gtk_menu_item_new_with_label("Routes");
    gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), Item_route);
    g_signal_connect(G_OBJECT(Item_route), "activate", G_CALLBACK(do_route_maj),NULL);

    Item_retirer_routes = gtk_menu_item_new_with_label("Retirer route");
    gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), Item_retirer_routes);
    g_signal_connect(G_OBJECT(Item_retirer_routes), "activate", G_CALLBACK(undo_route),NULL);

    Item_cacher_pt_route = gtk_menu_item_new_with_label("Cacher les points des routes");
    gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), Item_cacher_pt_route);
    g_signal_connect(G_OBJECT(Item_cacher_pt_route), "activate", G_CALLBACK(hidePoints),NULL);

    Item_afficher_pt_route = gtk_menu_item_new_with_label("Afficher les points des routes");
    gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), Item_afficher_pt_route);
    g_signal_connect(G_OBJECT(Item_afficher_pt_route), "activate", G_CALLBACK(showPoints),NULL);

    Menu_route = gtk_menu_item_new_with_label("Routes");

    gtk_menu_item_set_submenu(GTK_MENU_ITEM(Menu_route), pMenu);
    gtk_menu_shell_append(GTK_MENU_SHELL(pMenuBar), Menu_route);

    /*Construction menu point d'intêret*/
    pMenu = gtk_menu_new();

    Item_afficher_pt_interet = gtk_menu_item_new_with_label("Affichage points d'interets");
    gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), Item_afficher_pt_interet);
    g_signal_connect(G_OBJECT(Item_afficher_pt_interet), "activate", G_CALLBACK(affichage_points_interets),NULL);

    Item_cacher_pt_interet = gtk_menu_item_new_with_label("Cacher points d'interets");
    gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), Item_cacher_pt_interet);
    g_signal_connect(G_OBJECT(Item_cacher_pt_interet), "activate", G_CALLBACK(cacher_points_interets),NULL);

    Information = gtk_menu_item_new_with_label("Information point d'interets");
    gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), Information);
    g_signal_connect(G_OBJECT(Information), "activate", G_CALLBACK(adresse_pt_interet),NULL);

    Menu_pt_interet = gtk_menu_item_new_with_label("Points d'interets");

    gtk_menu_item_set_submenu(GTK_MENU_ITEM(Menu_pt_interet), pMenu);
    gtk_menu_shell_append(GTK_MENU_SHELL(pMenuBar), Menu_pt_interet);

    /*Construction menu gestion*/
    pMenu = gtk_menu_new();

    Item_remise_a_zero = gtk_menu_item_new_with_label("Remise a zero");
    gtk_menu_shell_append(GTK_MENU_SHELL(pMenu),Item_remise_a_zero);
    g_signal_connect(G_OBJECT(Item_remise_a_zero), "activate", G_CALLBACK(remise_a_zero),NULL);

    Item_retour_pt_normaux = gtk_menu_item_new_with_label("Retour points normaux");
    gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), Item_retour_pt_normaux);
    g_signal_connect(G_OBJECT(Item_retour_pt_normaux), "activate", G_CALLBACK(remise_pt_normal),NULL);

    Item_afficher_pt_suppr = gtk_menu_item_new_with_label("Afficher points supprimé");
    gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), Item_afficher_pt_suppr);
    g_signal_connect(G_OBJECT(Item_afficher_pt_suppr), "activate", G_CALLBACK(resurrection_point),NULL);

    Item_anonym_manu = gtk_menu_item_new_with_label("Anonymisation manuel");
    gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), Item_anonym_manu);
    g_signal_connect(G_OBJECT(Item_anonym_manu), "activate", G_CALLBACK(do_anonymous),NULL);

    Item_anonym_auto = gtk_menu_item_new_with_label("Anonymisation auto");
    gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), Item_anonym_auto);
    g_signal_connect(G_OBJECT(Item_anonym_auto), "activate", G_CALLBACK(detection_pt_interet),NULL);

    Item_mode_dynam = gtk_menu_item_new_with_label("Mode dynamique");
    gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), Item_mode_dynam);
    g_signal_connect(G_OBJECT(Item_mode_dynam), "activate", G_CALLBACK(mode_dynamique),NULL);

    Menu_gestion = gtk_menu_item_new_with_label("Gestion");

    gtk_menu_item_set_submenu(GTK_MENU_ITEM(Menu_gestion), pMenu);
    gtk_menu_shell_append(GTK_MENU_SHELL(pMenuBar), Menu_gestion);


    /*Ajout a la fenetre*/

    gtk_box_pack_start(GTK_BOX(widget), pMenuBar, FALSE, FALSE, 0);

    g_signal_connect (G_OBJECT (window), "key_press_event",G_CALLBACK (on_key_press), NULL);

}

void adresse_pt_interet(){
    info_pt_inte=1;
}
