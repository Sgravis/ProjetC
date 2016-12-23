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
GtkWidget *pVBox;
GtkWidget *pHBox;
<<<<<<< HEAD
GtkWidget *Button_dyn;
GtkWidget *Button_anonyme;
GtkWidget *Button_stat;
=======
GtkWidget *pButton;
>>>>>>> c293f4ef524fd350835d2b0e18ca0318b52f10cb
cairo_t* cr;
map_position map;

void reset_anonymisation();
void init_map();
void do_point( point pt);
void do_map();
void log_vers_carte();
gboolean on_draw(GtkWidget *widget, cairo_t *cr,gpointer user_data);
<<<<<<< HEAD
gboolean on_draw_dyn(GtkWidget *widget, cairo_t *cr,gpointer user_data);
=======
>>>>>>> c293f4ef524fd350835d2b0e18ca0318b52f10cb
void maj_map();

#endif
