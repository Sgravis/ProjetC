#ifndef INTERACTION_H
#define INTERACTION_H

#include "structure_log.h"
#include "visuel.h"
#include <cairo.h>
#include <gtk/gtk.h>
#include <stdio.h>

int anonyme;

point pt_tampon;
void on_click_map(GtkWidget* darea,GdkEventButton* event, void* data);
int popup(char* nom);
void do_anonymous(GtkWidget* pbutton, GdkEventButton* event, void* data);

#endif
