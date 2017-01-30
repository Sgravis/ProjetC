#include "visuel.h"


int coord_to_pixel_long(long double longitude){

	if(map.zoom==0)
		return ((2.39869958-longitude)/-0.000088242)+855;
	if(map.zoom==1)
		return ((2.39869958-longitude)/-0.000088242)+(855-map.pos_x+270);
}

int coord_to_pixel_lat(long double latitude){

	if(map.zoom==0)
		return ((47.0821639-latitude)/0.000055919)+156;
	if(map.zoom==1)
		return ((47.0821639-latitude)/0.000055919)+(156-map.pos_y+113);
	}

long double pixel_to_coord_long(int longitude)
{
	if(map.zoom==0)
		return (855-longitude)*-0.000088242+2.39869958;
	if(map.zoom==1)
		return ((855-map.pos_x+270)-longitude)*-0.000088242+2.39869958;	
}

long double pixel_to_coord_lat(int latitude)
{
	if(map.zoom==0)
		return (156-latitude)*0.000055919+47.0821639;
	if(map.zoom==1)
		return ((156-map.pos_y+113)-latitude)*0.000055919+47.0821639;
}


void init_map()
{
	map.pos_x=0;
	map.pos_y=0;
	map.zoom=0;
}


void do_point(point pt)
{	
	pt.taillept++;
	if (pt.taillept!=2)
		pt.taillept/=5;
	pt.taillept/=2;

	cairo_arc(cr,coord_to_pixel_long(pt.longitude),coord_to_pixel_lat(pt.latitude), pt.taillept, 0, 2 * M_PI);
	cairo_fill(cr);
}

void do_cercle(point centre, int rayon){
	cairo_set_source_rgb(cr,1,1,0);
	cairo_set_line_width(cr,1);
	cairo_arc(cr,coord_to_pixel_long(centre.longitude), coord_to_pixel_lat(centre.latitude),rayon, 0, 2 * M_PI);
	cairo_stroke(cr);
}

void reset_anonymisation()
{
	pt_tampon.longitude=-10;
	pt_tampon.latitude=-10;
	pt_tampon.taillept=1;
	x=0;
	y=0;
	anonyme_step=0;
	maj_map();
}


void anonymisation()
{
	//appartition des cercles d'anonymisation
	cairo_set_source_rgb(cr,1,1,0);
	if(map.zoom==0){
		do_point(pt_tampon);
		if(anonyme_step==4){
			if(1){//popup("anonymiser ce cercle ?")){
				suppression_avec_backup(detection_circulaire(pt_tampon,sqrt(pow(x-coord_to_pixel_long(pt_tampon.longitude),2)+pow(y-coord_to_pixel_lat(pt_tampon.latitude),2))*6,logGlobalClean),&logGlobalClean);
				reset_anonymisation();
			}
			else{
				reset_anonymisation();
			}
		}
		if (anonyme_step==3){
			cairo_set_line_width(cr,1);
			cairo_arc(cr,coord_to_pixel_long(pt_tampon.longitude),coord_to_pixel_lat(pt_tampon.latitude),sqrt(pow(x-coord_to_pixel_long(pt_tampon.longitude),2)+pow(y-coord_to_pixel_lat(pt_tampon.latitude),2)), 0, 2 * M_PI);
			cairo_stroke(cr);
			anonyme_step=4;
			maj_map();
		}
	
	}
}


void log_vers_carte(logs base)
{
	int i;
	cairo_set_source_rgb(cr,0,1,1);  //couleur des point
    cairo_set_line_width(cr,8);
	for(i=0;i<base.tailleTab;i++)  //parcourt et affiche tout les point des logs
	{  
		if(routeHide==0 || base.tableauPoint[i].route==0)
			do_point(base.tableauPoint[i]);
	}
}


void log_vers_carte_dyn(logs base)
{
	int i;
	cairo_set_source_rgb(cr,0,1,1);  //couleur des point
    cairo_set_line_width(cr,8);
	for(i=0;i<ind_dyn-1;i++)  //parcourt et affiche tout les point des logs
	{  
		if(routeHide==0 || base.tableauPoint[i].route==0)
			do_point(base.tableauPoint[i]);
	}
}


void do_map()
{

	int w, h;
	int TailleH,TailleL;
	//initialisation image
	cairo_set_source_rgb(cr,0,0,0);
	cairo_set_line_width(cr,0.5);

	//chargement de la carte
	if(image!=NULL)
		cairo_surface_destroy(image);

	image = cairo_image_surface_create_from_png ("Carte_Bourges_complete.png");
	w = cairo_image_surface_get_width (image);
	h = cairo_image_surface_get_height (image);

	// adaptation de la taille au zoom
	cairo_scale (cr,((map.zoom+1)*HFENETRE)/w,((map.zoom+1)*LFENETRE)/h);
	if (map.zoom==0){
		TailleH = HFENETRE;
		TailleL = LFENETRE;
		cairo_set_source_surface(cr, image,0,0);
	}
	if (map.zoom==1){
		TailleH = HFENETRE/3;
		TailleL = LFENETRE/3;
		// condition aux éxtrémité de la fenetre
		if(map.pos_x<=HFENETRE*0.17){map.pos_x=HFENETRE*0.17;}
		if(map.pos_y<=LFENETRE*0.17){map.pos_y=LFENETRE*0.17;}	
		if(map.pos_x>=HFENETRE*0.666666){map.pos_x=HFENETRE*0.6666666;}
		if(map.pos_y>=LFENETRE*0.666666){map.pos_y=LFENETRE*0.6666666;}
		cairo_set_source_surface (cr, image, -(map.pos_x-(TailleH/2)),-(map.pos_y-(TailleL/2)));
	}

	
	/*affichage de la carte*/
	cairo_paint (cr);
	cairo_stroke(cr);

}




void on_draw(GtkWidget *widget, cairo_t *crg,gpointer data)
{
	int i;
	logs log=*(logs*)data;
	cr=crg;
	do_map(); 				/*affiche la carte*/
	if(ind_dyn==-1){
		if(route==1)
			do_route();
		afficher_logs();		/*affiche le log*/
	}
	else{
		if (route==1)
			do_route_dyn(ind_dyn);
		log_vers_carte_dyn(log);
		if(ind_dyn<=log.tailleTab-vitesse_dyn){
			ind_dyn=ind_dyn+vitesse_dyn;
			maj_map();
		}
		else
		{
			ind_dyn=-1;
			maj_map();
		}
	}
	if(tableau_centre_interet[0].taillept!=0)
	{
		for(i=1;i<=tableau_centre_interet[0].taillept;i++)
		{
			do_cercle(tableau_centre_interet[i],tableau_centre_interet[i].taillept/6);
		}
	}	

	if (tmp_ano.taillept!=0){
    	do_cercle(tmp_ano,tmp_ano.taillept/6);
    }
	anonymisation();
}

void afficher_logs()
{
	int i;
	for(i=0;i<log_aff.taille;i++)
	{
		log_vers_carte(*log_aff.tableauLogs[0]);
	}
}

void ajout_log_aff(logs* log)
{
	int i ;
	log_aff.tableauLogs=(logs**)malloc(sizeof(logs*)*log_aff.taille);
	for(i=0;i<log_aff.taille;i++)
	{
		log_aff.tableauLogs[i]=(logs*)malloc(sizeof(logs*));
	}
	log_aff.tableauLogs[log_aff.taille]=log;
	log_aff.taille ++;
}

void reset_log_aff()
{
	int i;
	/*for(i=0;i<log_aff.taille;i++)
	{
		free(*log_aff.tableauLogs[i]);
	}
	free(log_aff.tableauLogs);*/
	log_aff.taille=0;
}



void maj_map()
{
	gtk_widget_queue_draw(darea);
}


void mode_dynamique (){
    GtkWidget *dialog_vit;
	GtkDialogFlags flags_vit = GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT;
	dialog_vit = gtk_dialog_new_with_buttons ("vitesse du dyn ?",GTK_WINDOW(window),flags_vit,("Très lent"),1,("lent"),15,("rapide"),40,NULL);
	vitesse_dyn = gtk_dialog_run(GTK_DIALOG(dialog_vit));
	gtk_widget_destroy (dialog_vit);
	ind_dyn=0;
    maj_map();
}


void do_route_dyn(int ind)
{
	int i;
	cairo_set_source_rgb(cr,1,0.5,0.5);
	cairo_set_line_width(cr,1);
	for(i=0;i<ind;i++)  //parcourt et affiche tout les point des logs
	{
		if(logGlobalClean.tableauPoint[i].route==1 && logGlobalClean.tableauPoint[i].agglomerat == 0)
		{
			if(abs(coord_to_pixel_long(logGlobalClean.tableauPoint[i].longitude)-coord_to_pixel_long(logGlobalClean.tableauPoint[i+1].longitude))<50 && abs(coord_to_pixel_lat(logGlobalClean.tableauPoint[i].latitude)-coord_to_pixel_lat(logGlobalClean.tableauPoint[i+1].latitude))<50)
			{
				cairo_move_to(cr,coord_to_pixel_long(logGlobalClean.tableauPoint[i].longitude),coord_to_pixel_lat(logGlobalClean.tableauPoint[i].latitude));
				cairo_line_to(cr,coord_to_pixel_long(logGlobalClean.tableauPoint[i+1].longitude),coord_to_pixel_lat(logGlobalClean.tableauPoint[i+1].latitude));
			}
		}
		cairo_stroke(cr);
	}
	gtk_widget_hide(Item_route);
	gtk_widget_show(Item_retirer_routes);
}


void do_route_maj(){
	route=1;
	do_route();
	gtk_widget_show(Item_cacher_pt_route);
	maj_map();
}

void do_route(){
	int i;
	cairo_set_source_rgb(cr,1,0.5,0.5);
	cairo_set_line_width(cr,1);
	for(i=1;i<logGlobalClean.tailleTab;i++)
	{
		if(logGlobalClean.tableauPoint[i].route==1 && logGlobalClean.tableauPoint[i].agglomerat == 0)
		{
			if(abs(coord_to_pixel_long(logGlobalClean.tableauPoint[i].longitude)-coord_to_pixel_long(logGlobalClean.tableauPoint[i+1].longitude))<55 && abs(coord_to_pixel_lat(logGlobalClean.tableauPoint[i].latitude)-coord_to_pixel_lat(logGlobalClean.tableauPoint[i+1].latitude))<55)
			{
				cairo_move_to(cr,coord_to_pixel_long(logGlobalClean.tableauPoint[i].longitude),coord_to_pixel_lat(logGlobalClean.tableauPoint[i].latitude));
				cairo_line_to(cr,coord_to_pixel_long(logGlobalClean.tableauPoint[i+1].longitude),coord_to_pixel_lat(logGlobalClean.tableauPoint[i+1].latitude));
			}
		}
		cairo_stroke(cr);
	}
	gtk_widget_hide(Item_route);
	gtk_widget_show(Item_retirer_routes);

}


void undo_route(){
	route=0;
	routeHide=0;
	gtk_widget_hide(Item_retirer_routes);
	gtk_widget_hide(Item_cacher_pt_route);
	gtk_widget_hide(Item_afficher_pt_route);
	gtk_widget_show(Item_route);
	maj_map();
}

void hidePoints(){
	gtk_widget_hide(Item_cacher_pt_route);
	gtk_widget_show(Item_afficher_pt_route);
	routeHide=1;
	maj_map();

}

void showPoints(){
	gtk_widget_show(Item_cacher_pt_route);
	gtk_widget_hide(Item_afficher_pt_route);
	routeHide=0;
	maj_map();
}


void menu_bar(GtkWidget* widget){
	/******************************************************************/

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

}