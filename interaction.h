#ifndef INTERACTION_H
#define INTERACTION_H


#include "structure_log.h"
#include "visuel.h"
#include <cairo.h>
#include <gtk/gtk.h>
#include <stdio.h>
#include <gdk/gdkkeysyms.h>
#include "agglomeration.h"



/*
*Element du menu
*/

GtkWidget *pMenuBar;
GtkWidget *pMenu;
GtkWidget *Item_route;
GtkWidget *Item_retirer_routes;
GtkWidget *Item_cacher_pt_route;
GtkWidget *Item_afficher_pt_route;
GtkWidget *Menu_route;
GtkWidget *Item_afficher_pt_interet;
GtkWidget *Item_cacher_pt_interet;
GtkWidget *Menu_pt_interet;
GtkWidget *Item_remise_a_zero;
GtkWidget *Item_retour_pt_normaux;
GtkWidget *Item_afficher_pt_suppr;
GtkWidget *Item_anonym_auto;
GtkWidget *Item_mode_dynam;
GtkWidget *Menu_gestion;
GtkWidget *Menu_Ouverture_Logs;
GtkWidget *Information;

GtkWidget *Menu_log1;
GtkWidget *Menu_log2;
GtkWidget *Menu_log3;
GtkWidget *Menu_logs;

int anonyme_step;
int info_pt_inte;
int route;
point pt_tampon;
float x;
float y;

void on_click_map(GtkWidget* darea,GdkEventButton* event, void* data);
int popup(char* nom);
void popupclose(char* nom);
void do_anonymous(GtkWidget* pbutton, GdkEventButton* event, void* data);
void on_key_press(GtkWidget *widget, GdkEventKey *event);
void ouverture_logs();
void choix_logs(GtkButton* boutton,gpointer data);
void adresse_pt_interet();
//void choix_logs1();
//void choix_logs2();
//void choix_logs3();

#endif
