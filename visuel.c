#include "visuel.h"


int coord_to_pixel_long(long double longitude){

	if(map.zoom==0)
		return ((2.39869958-longitude)/-0.000084500)+855;
	if(map.zoom==1)
		return ((2.39869958-longitude)/-0.000083000)+(855-map.pos_x+270);
}

int coord_to_pixel_lat(long double latitude){

	if(map.zoom==0)
		return ((47.0821639-latitude)/0.000058000)+156;
	if(map.zoom==1)
		return ((47.0821639-latitude)/0.000055919)+(156-map.pos_y+113);
	}

long double pixel_to_coord_long(float longitude)
{
	if(map.zoom==0)
		return (855-longitude)*-0.000083000+2.39869958;
	if(map.zoom==1)
		return ((855-map.pos_x+270)-longitude)*-0.000083000+2.39869958;	
}

long double pixel_to_coord_lat(float latitude)
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

	int lon=coord_to_pixel_long(pt.longitude);
	int lat=coord_to_pixel_lat(pt.latitude);
	cairo_arc(cr,lon/*-0.08*(lat-150)*/,lat, pt.taillept, 0, 2 * M_PI);

	cairo_fill(cr);
}

void do_cercle(point centre, int rayon){
	cairo_set_source_rgb(cr,1,1,0);
	cairo_set_line_width(cr,1);
	cairo_arc(cr,coord_to_pixel_long(centre.longitude), coord_to_pixel_lat(centre.latitude),rayon/6, 0, 2 * M_PI);
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
	//if(map.zoom==0){
		do_point(pt_tampon);
		if(anonyme_step==4){
			if(1){//popup("anonymiser ce cercle ?")){
				suppression_avec_backup(detection_circulaire(pt_tampon,sqrt(pow(x-coord_to_pixel_long(pt_tampon.longitude),2)+pow(y-coord_to_pixel_lat(pt_tampon.latitude),2))*6,logGlobalClean[id_en_cours]),&logGlobalClean[id_en_cours]);
				reset_anonymisation();
			}
			else{
				reset_anonymisation();
			}
		}
		if (anonyme_step==3){
			do_cercle(pt_tampon,sqrt(pow(x-coord_to_pixel_long(pt_tampon.longitude),2)+pow(y-coord_to_pixel_lat(pt_tampon.latitude),2))*6);
			anonyme_step=4;
			maj_map();
		}
	
	//}
}


void log_vers_carte(logs base)
{
	int i;
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
	cr=crg;
	do_map(); 				/*affiche la carte*/
	if(ind_dyn==-1)
	{
		if(route==1)
			do_route(logGlobalClean[id_en_cours].tailleTab);
		afficher_logs(0);		/*affiche le log*/
	}
	else
	{
		if (route==1)
			do_route(ind_dyn);
		afficher_logs(1);
		if(ind_dyn<=logGlobalClean[id_en_cours].tailleTab-vitesse_dyn)
		{
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
			do_cercle(tableau_centre_interet[i],tableau_centre_interet[i].taillept);
		}
	}	

	if (tmp_ano.taillept!=0)
	{
    	do_cercle(tmp_ano,tmp_ano.taillept);
    }
	anonymisation();
}

void afficher_logs(int dynamique)
{
	int i;
	for(i=0;i<log_aff.taille;i++)
	{
		if(i==0){cairo_set_source_rgb(cr,0,1,0);}
		if(i==1){cairo_set_source_rgb(cr,1,0,0);}
		if(i==2){cairo_set_source_rgb(cr,0,0,1);}
		if(i==3){cairo_set_source_rgb(cr,0,1,1);}


		if (dynamique)
			log_vers_carte_dyn(*log_aff.tableauLogs[i]);
		else
			log_vers_carte(*log_aff.tableauLogs[i]);
	}
}

void ajout_log_aff(logs* log)
{
	int i ;
	//logs** tmp=(logs**)malloc(sizeof(logs*)*log_aff.taille+1);

	//alloue tmp
	/*for(i=0;i<log_aff.taille;i++){
		tmp[i]=(logs*)malloc(sizeof(logs));
		*tmp[i]=allocation_tableau_point(log->tailleTab);
	}

	// copie ancien -> nouveau
	for(i=0;i<log_aff.taille;i++){
		tmp[i]=log_aff.tableauLogs[i];
	}*/

	//ajoute log au nouveau tab et applique le tmp
	//tmp[log_aff.taille]=log;
	//logs p=allocation_tableau_point(log->tailleTab);
	//log_aff.tableauLogs[log_aff.taille]=&p;
	log_aff.tableauLogs[log_aff.taille]=log;
	log_aff.taille++;
}

void reset_log_aff()
{
	//free(log_aff.tableauLogs);
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

void do_route(int ind)
{
	int i;
	cairo_set_source_rgb(cr,1,0.5,0.5);
	cairo_set_line_width(cr,1);
	for(i=0;i<ind;i++)  //parcourt et affiche tout les point des logs
	{
		if(logGlobalClean[id_en_cours].tableauPoint[i].route==1 && logGlobalClean[id_en_cours].tableauPoint[i].agglomerat == 0)
		{ 
			if(abs(coord_to_pixel_long(logGlobalClean[id_en_cours].tableauPoint[i].longitude)-coord_to_pixel_long(logGlobalClean[id_en_cours].tableauPoint[i+1].longitude))<50 && abs(coord_to_pixel_lat(logGlobalClean[id_en_cours].tableauPoint[i].latitude)-coord_to_pixel_lat(logGlobalClean[id_en_cours].tableauPoint[i+1].latitude))<50)
			{
				cairo_move_to(cr,coord_to_pixel_long(logGlobalClean[id_en_cours].tableauPoint[i].longitude),coord_to_pixel_lat(logGlobalClean[id_en_cours].tableauPoint[i].latitude));
				cairo_line_to(cr,coord_to_pixel_long(logGlobalClean[id_en_cours].tableauPoint[i+1].longitude),coord_to_pixel_lat(logGlobalClean[id_en_cours].tableauPoint[i+1].latitude));
			}
		}
		cairo_stroke(cr);
	}
	gtk_widget_hide(Button_road);
	gtk_widget_show(Button_noroad);
}


void do_route_maj(){
	route=1;
	do_route(logGlobalClean[id_en_cours].tailleTab);
	gtk_widget_show(Button_hidePoints);
	maj_map();
}


void undo_route(){
	route=0;
	routeHide=0;
	gtk_widget_hide(Button_noroad);
	gtk_widget_hide(Button_hidePoints);
	gtk_widget_hide(Button_showPoints);
	gtk_widget_show(Button_road);
	maj_map();
}

void hidePoints(){
	gtk_widget_hide(Button_hidePoints);
	gtk_widget_show(Button_showPoints);
	routeHide=1;
	maj_map();

}

void showPoints(){
	gtk_widget_show(Button_hidePoints);
	gtk_widget_hide(Button_showPoints);
	routeHide=0;
	maj_map();
}