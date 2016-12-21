#include "visuel.h"



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
void do_point(cairo_t* cr, point pt)
{
	if(map.zoom==0)
		cairo_arc(cr,((2.39869958-pt.longitude)/-0.000088242)+855,((212,47.0821639-pt.latitude)/0.000055919)+156, 2, 0, 2 * M_PI);
	if(map.zoom==1)
		cairo_arc(cr,((2.39869958-pt.longitude)/-0.000088242)+(855-map.pos_x+405),((212,47.0821639-pt.latitude)/0.000055919)+(156-map.pos_y+170),1,0,2*M_PI);
	cairo_fill(cr);
}


/**
 * Affiche tout les log globaux sur la carte
 */
void log_vers_carte(cairo_t* cr)
{
	int i;
	cairo_set_source_rgb(cr,1,0,0);  //couleur des point
    cairo_set_line_width(cr,8);
	for(i=0;i<logGlobalClean.tailleTab;i++)  //parcourt et affiche tout les point des logs
	{  
		do_point(cr,logGlobalClean.tableauPoint[i]);
	}
}

/**
 * Affiche l'image en fonction du zoom defini
 */
void do_map(cairo_t *cr)
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
gboolean on_draw(GtkWidget *widget, cairo_t *cr,gpointer user_data)
{
	do_map(cr); /*affiche la carte*/
	log_vers_carte(cr);	/*affiche le log*/
	return FALSE;
}

/**
 * Met la carte a jour en fonction des parametre actuels
 */
void maj_map()
{
	gtk_widget_queue_draw (darea);
}

/**
*creation de boutons
*/

