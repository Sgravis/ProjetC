#ifndef _REMPLISSAGE_H
#define _REMPLISSAGE_H

#include "structure_log.h"
#include "allocation.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void recuperation_donnees(FILE * fp);
void init_log_clean_id ();
void copie_points(point *point1,point *point2);
void backup_file (logs tlog);
logs copie_tableau(logs tlog1, int taille);
void resurrection_point();
void remise_pt_normal();
void recuperation_addr();
void remise_a_zero();
void affichage_points_interets();
void recherche_adresse_point(point p,int cpt);
void cacher_points_interets();
int recherche_seuil(point p);
void ajout_log_file(char * name_file);

/*void copie_points_base_addr (pointaddr* point1, pointaddr* point2);*/
/*addr copie_tableau_addr(addr tab,int taille);*/



point tableau_centre_interet[100];



#endif

