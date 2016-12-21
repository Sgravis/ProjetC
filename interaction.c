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
        maj_map();
    }
    if(anonyme==2)
    {
        printf("je suis au second point\n");
        cairo_set_line_width(cr,8);
        cairo_set_source_rgb(cr,0,1,0);
        cairo_arc(cr,pt_tampon.longitude,pt_tampon.latitude, event->x-pt_tampon.longitude, 0, 2 * M_PI); 
        anonyme=0;
    }

    if(anonyme==1)
    {
        printf("je suis au premier point\n");
        pt_tampon.longitude=event->x;
        pt_tampon.latitude=event->y;
        pt_tampon.taillept=4;
        cairo_set_source_rgb(cr,0,1,0);
        do_point(cr,pt_tampon);
        maj_map();
        anonyme=2;
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
    printf("bouton clicke \n");
    anonyme=1;
}