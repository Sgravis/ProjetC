#include "visuel.h"

/**
* transforme les coordonees en fonction des données necessaires
*/
int coord_to_pixel_long(long double longitude){

	if(map.zoom==0)
		return ((2.39869958-longitude)/-0.000088242)+855;
	if(map.zoom==1)
		return ((2.39869958-longitude)/-0.000088242)+(855-map.pos_x+405);
}

int coord_to_pixel_lat(long double latitude){

	if(map.zoom==0)
		return ((47.0821639-latitude)/0.000055919)+156;
	if(map.zoom==1)
		return ((47.0821639-latitude)/0.000055919)+(156-map.pos_y+170);
	}

long double pixel_to_coord_long(int longitude)
{
	if(map.zoom==0)
		return (855-longitude)*-0.000088242+2.39869958;
	if(map.zoom==1)
		return ((855-map.pos_x+405)-longitude)*-0.000088242+2.39869958;	
}

long double pixel_to_coord_lat(int latitude)
{
	if(map.zoom==0)
		return (156-latitude)*0.000055919+47.0821639;
	if(map.zoom==1)
		return ((156-map.pos_y+170)-latitude)*0.000055919+47.0821639;
}

/**
* Remet la carte dans son etat initial (complète)
*/
void init_map()
{
	map.pos_x=0;
	map.pos_y=0;
	map.zoom=0;
}


/**
 * Affiche un point sur la carte
 */
void do_point(point pt)
{	
	pt.taillept++;
	if (pt.taillept!=2)
		pt.taillept/=3;

	cairo_arc(cr,coord_to_pixel_long(pt.longitude),coord_to_pixel_lat(pt.latitude), pt.taillept, 0, 2 * M_PI);
	cairo_fill(cr);
}

/**
*	affiche un cercle sur la carte, en fonction de son centre et de son rayon
*/
void do_cercle(point centre, int rayon)
{
	cairo_set_source_rgb(cr,1,1,0);
	cairo_set_line_width(cr,1);
	cairo_arc(cr,coord_to_pixel_long(centre.longitude), coord_to_pixel_lat(centre.latitude),rayon, 0, 2 * M_PI);
	cairo_stroke(cr);
}

/**
* clos la procédure d'anonymisation
*/
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

/**
* procédure d'anonymisation (étape 3 et 4)
*/
void anonymisation()
{
	//appartition des cercles d'anonymisation
	cairo_set_source_rgb(cr,1,1,0);
	if(map.zoom==0){
		do_point(pt_tampon);
		if(anonyme_step==4){
			if(1){//} popup("anonymiser ce cercle ?")){
				suppression(Detection_circulaire(pt_tampon,sqrt(pow(x-coord_to_pixel_long(pt_tampon.longitude),2)+pow(y-coord_to_pixel_lat(pt_tampon.latitude),2))*6,logGlobalClean),&logGlobalClean);
				//suppression(Detection_circulaire(pt_tampon,400,logGlobalClean),&logGlobalClean);
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

/**
 * Affiche tout les log globaux sur la carte
 */
void log_vers_carte()
{
	int i;
	cairo_set_source_rgb(cr,1,0,0);  //couleur des point
    cairo_set_line_width(cr,8);
	for(i=0;i<logGlobalClean.tailleTab;i++)  //parcourt et affiche tout les point des logs
	{  
		do_point(logGlobalClean.tableauPoint[i]);
	}
}

/**
 * Affiche tout les log globaux sur la carte de manière dynamique
 */
void log_vers_carte_dyn()
{
	int i;
	cairo_set_source_rgb(cr,0,1,0);  //couleur des point
    cairo_set_line_width(cr,8);
	for(i=0;i<ind_dyn;i++)  //parcourt et affiche tout les point des logs
	{  
		do_point(logGlobalClean.tableauPoint[i]);
	}
}

/**
 * Affiche l'image en fonction du zoom defini
 */
void do_map()
{

	int w, h;
	int TailleH,TailleL;
	
	//initialisation image
	cairo_surface_t *image;	
	cairo_set_source_rgb(cr,0,0,0);
	cairo_set_line_width(cr,0.5);

	//chargement de la carte
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
		TailleH = HFENETRE/2;
		TailleL = LFENETRE/2;
		// condition aux éxtrémité de la fenetre
		if(map.pos_x<=HFENETRE*0.25){map.pos_x=HFENETRE*0.25;}
		if(map.pos_y<=LFENETRE*0.25){map.pos_y=LFENETRE*0.25;}	
		if(map.pos_x>=HFENETRE*0.75){map.pos_x=HFENETRE*0.75;}
		if(map.pos_y>=LFENETRE*0.75){map.pos_y=LFENETRE*0.75;}
		cairo_set_source_surface (cr, image, -(map.pos_x-(TailleH/2)),-(map.pos_y-(TailleL/2)));
	}

	
	/*affichage de la carte*/
	cairo_paint (cr);
	cairo_stroke(cr);

}



/**
 * affiche la carte et les point du log
 */
gboolean on_draw(GtkWidget *widget, cairo_t *crg,gpointer user_data)
{
	cr=crg;
	do_map(); 				/*affiche la carte*/
	if(ind_dyn==-1)
		log_vers_carte();		/*affiche le log*/
	else{
		log_vers_carte_dyn();
		if(ind_dyn<=logGlobalClean.tailleTab-vitesse_dyn){
			ind_dyn=ind_dyn+vitesse_dyn;
			maj_map();
		}
	}
	if(route==1)
		do_route();
	anonymisation();
	return FALSE;
}

/**
 * Met la carte a jour en fonction des parametre actuels
 */
void maj_map()
{
	gtk_widget_queue_draw(darea);
}


/**
 * affiche les log dynamiquement et échange les boutons
 */
void mode_dynamique (){
    gtk_widget_hide(Button_dyn);
    gtk_widget_show(Button_stat);
    undo_route();
    GtkWidget *dialog_vit;
	GtkDialogFlags flags_vit = GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT;
	dialog_vit = gtk_dialog_new_with_buttons ("vitesse du dyn ?",GTK_WINDOW(window),flags_vit,("Très lent"),1,("lent"),2,("rapide"),5,NULL);
	vitesse_dyn = 10*gtk_dialog_run(GTK_DIALOG(dialog_vit));
	gtk_widget_destroy (dialog_vit);
	   ind_dyn=0;
    maj_map();
}

/**
 * affiche les log statiquement et échange les boutons
 */
void mode_statique (){
    g_signal_connect(G_OBJECT(darea),"draw", G_CALLBACK(on_draw), NULL);
    gtk_widget_hide(Button_stat);
    gtk_widget_show(Button_dyn);
    ind_dyn=-1;
    maj_map();
}

/**
 * affiche les routes et échange les boutons
 */
void do_route(){
	int i;
	route=1;
	cairo_set_source_rgb(cr,0,0.5,0.5);
	cairo_set_line_width(cr,1);
	for(i=1;i<logGlobalClean.tailleTab;i++)
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
	route=1;
	gtk_widget_hide(Button_road);
	gtk_widget_show(Button_noroad);
maj_map();
}

/**
 * cache les routes et échange les boutons
 */
void undo_route(){
	route=0;
	gtk_widget_hide(Button_noroad);
	gtk_widget_show(Button_road);
}
