#include <cairo.h>
#include <gtk/gtk.h>
#include <stdio.h>
#include <math.h>
#define HFENETRE 1628.0
#define LFENETRE 680.0


static void do_drawing(cairo_t *);
static void do_point(cairo_t*);
static gboolean on_draw_event(GtkWidget *widget, cairo_t *cr,
gpointer user_data)
{
	do_drawing(cr); /*affiche la carte*/
	do_point(cr);	/*affiche les points*/
	return FALSE;
}

static void do_point(cairo_t* cr)
{
	int i;
	
        cairo_set_source_rgb(cr, 1, 0, 0);  /*couleur des point*/
        cairo_set_line_width(cr,1);	  

	for(i=0,i<TAILLETAB,i++)  //idee pour afficher tout les 
				    //point, depend de la struct
	{
		cairo_arc(cr,((2.39869958-tab[i][0])/-0.000088242)+855,((212,47.0821639-tab[i][1])/0.000055919)+156, 10, 0, 2 * M_PI)
		cairo_fill(cr);
		sleep(0.001);  	    //pour afficher le "trajet
	}
	
	/*cairo_arc(cr,501,495,3,0,2*M_PI);	 //(501,495)=position de l'aéroport
	cairo_fill(cr);				  
	
	cairo_arc(cr, 855,156,3,0,2*M_PI);	//(855,156)=position de la cathédrale
	cairo_fill(cr);				

	cairo_set_source_rgb(cr,0,1,0);
	printf("diff : %f\n",47.0821639-47.0808212);
	printf("a ajouter : %f\n",(47.0821639-47.0808212)/0.000055919);

	cairo_arc(cr,((2.39869958-2.4174019)/-0.000088242)+855,((212,47.0821639-47.0808212)/0.000055919)+156,3,0,2*M_PI);      
        cairo_fill(cr);
*/
	cairo_stroke(cr);    
}


static void do_drawing(cairo_t *cr)
{

	int w, h;
	
	/*initialisation image*/
	cairo_surface_t *image;
	cairo_set_source_rgb(cr, 0, 0, 0);
	cairo_set_line_width(cr, 0.5);

	/*chargement de la carte*/
	image = cairo_image_surface_create_from_png ("Carte_Bourges3.png");
	w = cairo_image_surface_get_width (image);
	h = cairo_image_surface_get_height (image);
	cairo_scale (cr,HFENETRE/w,LFENETRE/h);
	cairo_set_source_surface (cr, image, 0, 0);

	/*dessinage de la carte*/
	cairo_paint (cr);
	cairo_stroke(cr);

}

int main(int argc, char *argv[])
{
GtkWidget *window;    /*creation fenetre*/
GtkWidget *darea;     /*creation zone de dessin sur la fenetre*/

/*initialisation fenetre*/
gtk_init(&argc, &argv);
window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
darea = gtk_drawing_area_new();
gtk_container_add(GTK_CONTAINER(window), darea);
g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

/*dessinage carte et points*/
g_signal_connect(G_OBJECT(darea), "draw", G_CALLBACK(on_draw_event), NULL);

/*positionnement de la fenetre*/
gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
gtk_window_set_default_size(GTK_WINDOW(window), HFENETRE,LFENETRE);
gtk_window_set_title(GTK_WINDOW(window), "Bourges");
//gtk_window_set_resizable(GTK_WINDOW(window),FALSE); //un soucis ici


gtk_widget_show_all(window); //affichage de la fenetre

gtk_main();  // fonction de boucle de gtk

return 0;
}
