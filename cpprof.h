#ifndef CPPROF_H
#define CPPROF_H
#include <cairo.h>
#include <gtk/gtk.h>
#include <stdio.h>
#include "cpprof.h"
#include <math.h>
#define HFENETRE 1628.0
#define LFENETRE 680.0


gboolean on_draw(GtkWidget *widget, cairo_t *cr,gpointer user_data);
void on_click_map(GtkWidget* canvas, GdkEventButton* event, void* data);
void on_quit(GtkWidget *widget,gpointer user_data);

void init_map()
{
	map.map_pos_x=0;
	map.map_pos_y=0;
	map.map_zoom=0;
}

void do_point(cairo_t* cr, long double latitude, long double longitude)
{
	printf("long : %Lf, lat : %Lf\n",longitude,latitude);

	cairo_arc(cr,((2.39869958-longitude)/-0.000088242)+855,((212,47.0821639-latitude)/0.000055919)+156, 3, 0, 2 * M_PI);
	cairo_fill(cr);

	cairo_stroke(cr);    
}

void log_vers_carte(cairo_t* cr){

	int i;
	cairo_set_source_rgb(cr, 1, 0, 0);  /*couleur des point*/
    cairo_set_line_width(cr,1);
	for(i=0;i<logGlobal.tailleTab;i++)
	{  
		do_point(cr,logGlobal.tableauPoint[i].latitude,logGlobal.tableauPoint[i].longitude);
	}
}

void do_map(cairo_t *cr)
{

	int w, h;
	
	/*initialisation image*/
	cairo_surface_t *image;	
	cairo_set_source_rgb(cr, 0, 0, 0);
	cairo_set_line_width(cr, 0.5);

	/*chargement de la carte*/
	image = cairo_image_surface_create_from_png ("Carte_Bourges_complete.png");

	w = cairo_image_surface_get_width (image);
	h = cairo_image_surface_get_height (image);
	cairo_scale (cr,HFENETRE/w,LFENETRE/h);
	cairo_set_source_surface (cr, image, 0, 0);

	/*dessinage de la carte*/
	cairo_paint (cr);
	cairo_stroke(cr);
	

}
void on_quit(GtkWidget *widget,gpointer user_data)
{
	quit=1;
	gtk_main_quit();
}

void on_click_map(GtkWidget* darea, GdkEventButton* event, void* data)
{
    if (event->type==GDK_2BUTTON_PRESS )
    {
    	if(map.map_zoom==0){
    		printf("double clique sur %f;%f \n",event->x,event->y);
    		map.map_pos_x=event->x;
    		map.map_pos_y=event->y;
    		map.map_zoom=1;
    		gtk_main_quit();
    	}
    	else{init_map();}
    }
}

gboolean on_draw(GtkWidget *widget, cairo_t *cr,gpointer user_data)
{
	do_map(cr); /*affiche la carte*/
	log_vers_carte(cr);	/*affiche le log*/
	return FALSE;
}
#endif
