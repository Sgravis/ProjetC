#include <cairo.h>
#include <gtk/gtk.h>
#include <stdio.h>
#define M_PI 3.14

static void do_drawing(cairo_t *cr)
{

        // HACK JFL: image draw test
        int              w, h;
        cairo_surface_t *image;

        cairo_set_source_rgb(cr, 0, 0, 0);
        cairo_set_line_width(cr, 0.5);



        image = cairo_image_surface_create_from_png ("carte_bourges2.png");
        w = cairo_image_surface_get_width (image);
        h = cairo_image_surface_get_height (image);
        cairo_scale (cr, 256.0/w, 256.0/h);


        cairo_set_source_surface (cr, image, 0, 0);
        cairo_paint (cr);

        // For drawing lines when glob has evolved
        int i, j;
        /*for (i = 0; i <= glob.count - 1; i++ ) {
                for (j = 0; j <= glob.count - 1; j++ ) {
                        cairo_move_to(cr, glob.coordx[i], glob.coordy[i]);
                        cairo_line_to(cr, glob.coordx[j], glob.coordy[j]);
                }
        }*/

        cairo_stroke(cr);
}



int main(){
cairo_t* cr;
double xc = 128.0;
double yc = 128.0;
double radius = 100.0;
double angle1 = 45.0  * (M_PI/180.0);  /* angles are specified */
double angle2 = 180.0 * (M_PI/180.0);  /* in radians           */

cairo_set_line_width (cr, 10.0);
cairo_arc (cr, xc, yc, radius, angle1, angle2);
cairo_stroke (cr);

/* draw helping lines */
cairo_set_source_rgba (cr, 1, 0.2, 0.2, 0.6);
cairo_set_line_width (cr, 6.0);

cairo_arc (cr, xc, yc, 10.0, 0, 2*M_PI);
cairo_fill (cr);

cairo_arc (cr, xc, yc, radius, angle1, angle1);
cairo_line_to (cr, xc, yc);
cairo_arc (cr, xc, yc, radius, angle2, angle2);
cairo_line_to (cr, xc, yc);
do_drawing(cr);
cairo_stroke (cr);
}
