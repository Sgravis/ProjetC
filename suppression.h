#ifndef _SUPPRESSION_H
#define _SUPPRESSION_H

#include "structure_log.h"
#include "allocation.h"
#include "remplissage.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

logs detection_circulaire(point centre, float rayon, logs base);
void suppression_sans_backup(logs tableauSupp, logs *base);
void suppression_avec_backup(logs tableauSupp, logs *base);
void detection_pt_interet();
int comparaison_point(point p1, point p2);
void afficher_tableau(int taille, logs tab); /*ne devrait pas etre la*/
void redefinition_grosseur_cercle(logs tab, float rayon, logs * tmp);




#endif

