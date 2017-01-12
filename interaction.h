#ifndef INTERACTION_H
#define INTERACTION_H


#include "structure_log.h"
#include "visuel.h"
#include <cairo.h>
#include <gtk/gtk.h>
#include <stdio.h>
#include <gdk/gdkkeysyms.h>


int anonyme_step;
int route;
point pt_tampon;
float x;
float y;
void on_click_map(GtkWidget* darea,GdkEventButton* event, void* data);
int popup(char* nom);
void popupclose(char* nom);
void do_anonymous(GtkWidget* pbutton, GdkEventButton* event, void* data);
void on_key_press(GtkWidget *widget, GdkEventKey *event);

#endif
