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
*Bouton de la barre d'outils
*/
GtkWidget *Button_dyn;
GtkWidget *Button_anonyme;
GtkWidget *Button_stat;
GtkWidget *Button_road;
GtkWidget *Button_noroad;
GtkWidget *Button_hidePoints;
GtkWidget *Button_showPoints;
GtkWidget *Button_pt_interet;
GtkWidget *Button_Remise_a_0;
GtkWidget *Button_Affichage_pt_supp;
GtkWidget *Button_Remise_pt_normal;
GtkWidget *Button_Ouverture_Logs;
GtkWidget *Button_Quitter;


GtkWidget *Button_log2;
GtkWidget *Button_log1;
GtkWidget *Button_log3;
GtkWidget *Button_choix_logs1;
GtkWidget *Button_choix_logs2;
GtkWidget *Button_choix_logs3;

GtkWidget *Button_Affichage_Points_Interets;
GtkWidget *Button_DesAffichage_Points_Interets;


int anonyme_step;
int route;
point pt_tampon;
float x;
float y;

void init_boutton();
void on_click_map(GtkWidget* darea,GdkEventButton* event, void* data);
int popup(char* nom);
void popupclose(char* nom);
void do_anonymous(GtkWidget* pbutton, GdkEventButton* event, void* data);
void on_key_press(GtkWidget *widget, GdkEventKey *event);
void ouverture_logs();
void choix_logs();


#endif
