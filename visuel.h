#ifndef VISUEL_H
#define VISUEL_H

#include "suppression.h"
#include <cairo.h>
#include <gtk/gtk.h>
#include <stdio.h>
#include <math.h>
#include "structure_log.h"
#include "interaction.h"
#define HFENETRE 1628.0
#define LFENETRE 680.0

typedef struct 
{
	float pos_x;
	float pos_y;
	int zoom;
}map_position;

long int ind_dyn;

GtkWidget* window;
GtkWidget* darea;
GtkWidget* darea2;
GtkWidget *pVBox;
GtkWidget *pHBox;
GtkWidget *Button_dyn;
GtkWidget *Button_anonyme;
GtkWidget *Button_stat;
cairo_t* cr;
map_position map;
cairo_surface_t *image;

void reset_anonymisation();
void init_map();
void do_point( point pt);
void do_map();
void log_vers_carte();
gboolean on_draw(GtkWidget *widget, cairo_t *cr,gpointer user_data);
gboolean on_draw_dyn(GtkWidget *widget, cairo_t *cr,gpointer user_data);
void maj_map();
void mode_dynamique();
void mode_statique ();


#endif
