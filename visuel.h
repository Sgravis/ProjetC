#ifndef CPPROF_H
#define CPPROF_H

#include <cairo.h>
#include <gtk/gtk.h>
#include <stdio.h>
#include <math.h>
#include "structure_log.h"
#define HFENETRE 1628.0
#define LFENETRE 680.0

typedef struct 
{
	float map_pos_x;
	float map_pos_y;
	int map_zoom;
}map_position;

int quit;

GtkWidget* window;
GtkWidget* darea;

map_position map;

gboolean on_draw(GtkWidget *widget, cairo_t *cr,gpointer user_data);
void on_click_map(GtkWidget* darea,GdkEventButton* event, void* data);
void on_quit(GtkWidget *widget,gpointer user_data);

#endif
