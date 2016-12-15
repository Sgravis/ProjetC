#ifndef _SUPPRESSION_H
#define _SUPPRESSION_H

#include "structure_log.h"
#include "allocation.h"
#include "remplissage.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

logs Detection_circulaire(point centre, int rayon);
void suppression(logs tableauSupp);
void detection_pt_interet();
int comparaison_point(point p1, point p2);
void afficher_tableau(int taille, logs tab);
void afficher_tableau2(int taille, addr tab);




#endif
