#include "interaction.h"


/**
 * detection du double clique pour l'actualisation du zoom
 */
void on_click_map(GtkWidget* darea, GdkEventButton* event, void* data)
{ 
    if (event->type==GDK_2BUTTON_PRESS )
    {
    	if(map.zoom==0){
    		map.pos_x=event->x;
    		map.pos_y=event->y;
    		map.zoom++;
    	}
    	else{init_map();}
        reset_anonymisation();
        maj_map();
    }
    if(anonyme_step==2)
    {
        x=event->x;
        y=event->y;
        anonyme_step=3;
        maj_map();
    }

    if(anonyme_step==1)
    {
        pt_tampon.longitude=pixel_to_coord_long(event->x);
        pt_tampon.latitude=pixel_to_coord_lat(event->y);
        pt_tampon.taillept=5;
        maj_map();
        anonyme_step=2;
    }
}

/**
 * Cree une fenetre qui pose une quesion a l'utilisateur, retourne 1 si il repond OUI, 0 sinon
 */
int popup(char* nom)
{
	int result;
	GtkWidget *dialog;
	GtkDialogFlags flags = GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT;
	dialog = gtk_dialog_new_with_buttons (nom,GTK_WINDOW(window),flags,("Oui"),1,("Non"),0,NULL);
	result = gtk_dialog_run(GTK_DIALOG(dialog));
	gtk_widget_destroy (dialog);
	return result;
}

void do_anonymous(GtkWidget* pbutton, GdkEventButton* event, void* data)
{
    reset_anonymisation();
    anonyme_step=1;
}