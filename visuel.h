#ifndef VISUEL_H
#define VISUEL_H

#include "suppression.h"
#include <cairo.h>
#include <gtk/gtk.h>
#include <stdio.h>
#include <math.h>
#include "structure_log.h"
#include "interaction.h"
#include "allocation.h"
#define HFENETRE 1628
#define LFENETRE 680

/*
*position de la map en fonction du zoom
*/

typedef struct 
{
	float pos_x;
	float pos_y;
	int zoom;
}map_position;
map_position map;

typedef struct 
{
	logs* tableauLogs[10];
	int taille;
}tabLogs;

tabLogs log_aff;

/*
*Element de gestion de la fenetre
*/
GtkWidget* window;
GtkWidget* darea;
GtkWidget* pVBox;
GtkWidget* pHBox;
GtkWidget* pButton;
GtkWidget* reset;
GtkWidget* pt_int_bouton;
cairo_t* cr;
cairo_surface_t* image;
map_position map;


/*
* indicateur bouton caché point
*/
int routeHide;
/*
*niveau de progression et vitesse du dynamique
*/
long int ind_dyn;
int vitesse_dyn;

/*
*centre du point à anonymiser
*/
point tmp_ano;


/*
*Fonction de transition entre les echelles de GTK et de Cairo
*/
int coord_to_pixel_long(long double longitude);
int coord_to_pixel_lat(long double latitude);
long double pixel_to_coord_long(float longitude);
long double pixel_to_coord_lat(float latitude);

/*
*affiche un element sur la carte
*/
void do_point( point pt);
void do_cercle(point centre, int rayon);

/*
*gère la procédure d'anonymisation par centre et rayon
*/
void anonymisation();
void reset_anonymisation();

/*
*Recentre la carte
*/
void init_map();

/*
*affiche la carte en fontion de la position
*/
void do_map();

/*
*procédure d'affichage
*/
void on_draw(GtkWidget *widget, cairo_t *cr,gpointer user_data);

/*
*affiche un log sur la carte
*/
void afficher_logs(int dynamique);

/*
* modifie la liste des logs à afficher
*/
void ajout_log_aff(logs* log);
void reset_log_aff();

/*
* réaffiche la carte de manière dynamique
*/
void mode_dynamique ();

/*
* ajoute ou enlève les route sur a carte
*/
void do_route_maj();
void do_route(int ind);
void hidePoints();
void showPoints();
void undo_route();

/*
* met a jour la carte en fonction des dernière modifications
*/
void maj_map();

/*
*affiche un log sur la carte de manière dynamique ou non
*/
void log_vers_carte(logs base);
void log_vers_carte_dyn(logs base);

#endif
