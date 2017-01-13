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

typedef struct 
{
	logs** tableauLogs;
	int taille;
}tabLogs;

tabLogs log_aff;

long int ind_dyn;
int vitesse_dyn;
point tmp_ano;

GtkWidget* window;
GtkWidget* darea;
GtkWidget *pVBox;
GtkWidget *pHBox;
GtkWidget *pButton;
GtkWidget *reset;
GtkWidget* pt_int_bouton;
cairo_t* cr;
map_position map;

cairo_surface_t *image;

GtkWidget *Button_dyn;
GtkWidget *Button_anonyme;
GtkWidget *Button_stat;
GtkWidget *Button_road;
GtkWidget *Button_noroad;
GtkWidget *Button_pt_interet;
GtkWidget *Button_Remise_a_0;
GtkWidget *Button_Affichage_pt_supp;
GtkWidget *Button_Remise_pt_normal;

cairo_t* cr;
map_position map;

int coord_to_pixel_long(long double longitude);
int coord_to_pixel_lat(long double latitude);
long double pixel_to_coord_long(int longitude);
long double pixel_to_coord_lat(int latitude);
void do_cercle(point centre, int rayon);

void reset_anonymisation();
void init_map();
void do_point( point pt);
void do_map();
gboolean on_draw(GtkWidget *widget, cairo_t *cr,gpointer user_data);
gboolean on_draw_dyn(GtkWidget *widget, cairo_t *cr,gpointer user_data);
void afficher_logs();
void ajout_log_aff(logs* log);
void reset_log_aff();
void mode_statique ();
void mode_dynamique ();
void do_route_maj();
void do_route();
void undo_route();
void interet();
void maj_map();
void log_vers_carte(logs base);

#endif
