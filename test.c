#include <cairo.h>
#include <gtk/gtk.h>
#include <stdio.h>
#include<stdlib.h>
#define M_PI 3.14
void OnDestroy(GtkWidget *pWidget, gpointer pData);
static gboolean on_draw_event(GtkWidget *widget, cairo_t *cr,gpointer user_data);
void dessin_cercle(cairo_t *cr);
//static gboolean draw_event(GtkWidget *pwindow,cairo_t *cr,gpointer user_data);
//gboolean draw_callback (GtkWidget *widget, cairo_t *cr, gpointer data);
static void do_drawing(cairo_t *cr);

int main(int argc, char** argv)
{
	/* Déclaration du widget */
	GtkWidget *pWindow;
	GtkWidget *pVBox;
	GtkWidget *pImage;
	GtkWidget *darea;
	
	gtk_init(&argc,&argv);
	/* Création de la fenêtre */
	pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	/* Définition de la position */
	gtk_window_set_position(GTK_WINDOW(pWindow), GTK_WIN_POS_CENTER);
	/* Définition de la taille de la fenêtre */
	gtk_window_set_default_size(GTK_WINDOW(pWindow), 550, 382);
	/* Titre de la fenêtre */
	gtk_window_set_title(GTK_WINDOW(pWindow), "carte bourges !");
	/* Connexion du signal "destroy" */
	g_signal_connect(G_OBJECT(pWindow), "destroy", G_CALLBACK(OnDestroy), NULL);
	/* Blocage de la taille de la fenetre*/    
	gtk_window_set_resizable(GTK_WINDOW(pWindow),FALSE);   

	darea=gtk_drawing_area_new();
	g_signal_connect (G_OBJECT(darea),"draw",G_CALLBACK(on_draw_event),NULL);
	/* initialisation de la boite*/
	pVBox=gtk_box_new(FALSE,0);
	/* mise de la fenetre dans la boite */
	gtk_container_add(GTK_CONTAINER(pWindow), pVBox);
//	gtk_container_add(GTK_CONTAINER(darea),pVBox);

	/* chargement de la carte */
	pImage=gtk_image_new_from_file("./Carte_de_France.jpg");

	/* mise de l'image dans la boite */
	gtk_box_pack_start(GTK_BOX(pVBox), pImage, FALSE, TRUE, 5);
	



	/* Affichage de la fenetre */
	gtk_widget_show_all(pWindow);

//g_signal_connect(G_OBJECT(darea), "draw", G_CALLBACK(draw_event),NULL);
	/* Démarrage de la boucle événementielle */
	gtk_main();

	return EXIT_SUCCESS; 
}

/*static gboolean draw_event(GtkWidget *pwindow,cairo_t *cr,gpointer user_dastatic gboolean on_draw_event(GtkWidget *widget, cairo_t *cr,
gpointer user_data)
{
do_drawing(cr);

return FALSE;
}ta)
{
	cr*=gdk_cairo_create(GDK_WINDOW(pwindow));
	dessin_cercle(*cr);
	troke(cr);eturn FALSEo
}*/

static gboolean on_draw_event(GtkWidget *widget, cairo_t *cr,gpointer user_data)
{
	printf("debut callback\n");
	do_drawing(cr);
	printf("fin callback\n");
	return FALSE;
}

static void do_drawing(cairo_t *cr)
{

       /* double xc = 1280;
        double yc = 1280;
        double radius = 100.0;
        double angle1 = 45.0  * (M_PI/180.0);  /* angles are specified */
        /*double angle2 = 180.0 * (M_PI/180.0);  /* in radians           */
	/*int w, h;
	cairo_surface_t *image;
	cairo_set_line_width (cr, 10.0);
	cairo_arc (cr, xc, yc, radius, angle1, angle2);

	cairo_set_source_rgb(cr, 0, 0, 0);
	cairo_set_line_width(cr, 0.5);

	cairo_set_source_surface (cr, image, 0, 0);
	cairo_paint (cr);
	cairo_stroke(cr);
	printf("dodrawing se termine\n");
*/
    int w, h;
    cairo_surface_t *image;

    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_set_line_width(cr, 0.5);

    image = cairo_image_surface_create_from_png ("./Carte_de_France.jpg");
    w = cairo_image_surface_get_width (image);
    h = cairo_image_surface_get_height (image);
    cairo_scale (cr, 256.0/w, 256.0/h);

    cairo_set_source_surface (cr, image, 0, 0);
    cairo_paint (cr);
    cairo_stroke(cr);
}

void OnDestroy(GtkWidget *pWidget, gpointer pData)
{
	/* Arrêt de la boucle événementielle */
	gtk_main_quit();
}
