#include "visuel.h"


int coord_to_pixel_lat(long double latitude)
{
	if(map.zoom==0)
		return ((47.0821639-latitude)/0.000055919)+156;
	if(map.zoom==1)
		return ((47.0821639-latitude)/0.000055919)+(156-map.pos_y+170);
}


int coord_to_pixel_long(long double longitude)
{
	if(map.zoom==0)
		return ((2.39869958-longitude)/-0.000088242)+855;
	if(map.zoom==1)
		return ((2.39869958-longitude)/-0.000088242)+(855-map.pos_x+405);
}

long double pixel_to_coord_lat(int latitude)
{
	if(map.zoom==0)
		return 47.0821639+(156-latitude)*0.000055919;
	if(map.zoom==1)
		return 47.0821639+((156-map.pos_y+170)-latitude)*0.000055919;
}

long double pixel_to_coord_long(int longitude)
{
	if(map.zoom==0)
		return 2.39869958+(855-longitude)*-0.000088242;
	if(map.zoom==1)
		return 2.39869958+((855-map.pos_x+405)-longitude)*-0.000088242;;
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
	cairo_arc(cr,coord_to_pixel_long(pt.longitude),coord_to_pixel_lat(pt.latitude),2,0,2*M_PI);
	cairo_fill(cr);
}

void reset_anonymisation()
{
	pt_tampon.longitude=-10;
	pt_tampon.latitude=-10;
	pt_tampon.taillept=0;
	x=0;
	y=0;
	anonyme_step=0;
	maj_map();
}
void anonymisation()
{
	//appartition des cercles d'anonymisation
	cairo_set_source_rgb(cr,1,1,0);
	int result;
	printf("long : %Lf lat : %Lf\n",pt_tampon.longitude,pt_tampon.latitude);
	do_point(pt_tampon);
	if(map.zoom==0){
		//cairo_arc(cr,pt_tampon.longitude,pt_tampon.latitude,6,0,2*M_PI);
		//cairo_fill(cr);
		if(anonyme_step==4){
			if( 1){//popup("anonymiser ce cercle ?")){	
				suppression(Detection_circulaire(pt_tampon,((int)sqrt((x-coord_to_pixel_long(pt_tampon.longitude))*(x-coord_to_pixel_long(pt_tampon.longitude))+(y-coord_to_pixel_lat(pt_tampon.latitude))*(y-coord_to_pixel_lat(pt_tampon.latitude)))*7),logGlobalClean),&logGlobalClean);
				reset_anonymisation();
			}
			else{
				reset_anonymisation();
			}
		}
		if (anonyme_step==3){
			cairo_set_line_width(cr,1);
			cairo_arc(cr,coord_to_pixel_long(pt_tampon.longitude),coord_to_pixel_lat(pt_tampon.latitude),sqrt((x-coord_to_pixel_long(pt_tampon.longitude))*(x-coord_to_pixel_long(pt_tampon.longitude))+(y-coord_to_pixel_lat(pt_tampon.latitude))*(y-coord_to_pixel_lat(pt_tampon.latitude))), 0, 2 * M_PI);
			cairo_stroke(cr);
			anonyme_step=4;
			maj_map();
		}
	
	}
	/*if(map.zoom==1){
		cairo_arc(cr,-(map.pos_x-(HFENETRE/4))+pt_tampon.longitude,-(map.pos_y-(LFENETRE/4))+pt_tampon.latitude,6,0,2*M_PI);
		cairo_fill(cr);
		if(anonyme_step==4){
			if( popup("anonymiser ce cercle ?")){
				printf("rayon : %f\n",sqrt((x-pt_tampon.longitude)*(x-pt_tampon.longitude)+(y-pt_tampon.latitude)*(y-pt_tampon.latitude)));
				//la fonction marche pas, je pense que le rayon est pas dans la bonne unite
				suppression(Detection_circulaire(pt_tampon,(int)sqrt((x-pt_tampon.longitude)*(x-pt_tampon.longitude)+(y-pt_tampon.latitude)*(y-pt_tampon.latitude))));
				reset_anonymisation();
			}
			else{
				reset_anonymisation();
			}
		}
		if (anonyme_step==3){
			cairo_set_line_width(cr,1);
			cairo_arc(cr,pt_tampon.longitude,pt_tampon.latitude,sqrt((x-pt_tampon.longitude)*(x-pt_tampon.longitude)+(y-pt_tampon.latitude)*(y-pt_tampon.latitude)), 0, 2 * M_PI);
			cairo_stroke(cr);
			anonyme_step=4;
			maj_map();
		}
	}*/
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
	do_map(); 			/*affiche la carte*/
	log_vers_carte();		/*affiche le log*/
	anonymisation();

	return FALSE;
}

/**
 * Met la carte a jour en fonction des parametre actuels
 */
void maj_map()
{
	gtk_widget_queue_draw (darea);
}
