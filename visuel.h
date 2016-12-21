#ifndef VISUEL_H
#define VISUEL_H

#include <cairo.h>
#include <gtk/gtk.h>
#include <stdio.h>
#include <math.h>
#include "structure_log.h"
#define HFENETRE 1628.0
#define LFENETRE 680.0

typedef struct 
{
	float pos_x;
	float pos_y;
	int zoom;
}map_position;

GtkWidget* window;
GtkWidget* darea;
GtkWidget *pVBox;
GtkWidget *pHBox;
GtkWidget *pButton;
map_position map;

void init_map();
void do_point(cairo_t* cr, point pt);
void do_map(cairo_t *cr);
void log_vers_carte(cairo_t* cr);
gboolean on_draw(GtkWidget *widget, cairo_t *cr,gpointer user_data);
void maj_map();

#endif
