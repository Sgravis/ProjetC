#ifndef INTERACTION_H
#define INTERACTION_H

#include "structure_log.h"
#include "visuel.h"
#include <cairo.h>
#include <gtk/gtk.h>
#include <stdio.h>

void on_click_map(GtkWidget* darea,GdkEventButton* event, void* data);
int popup(char* nom);

#endif
