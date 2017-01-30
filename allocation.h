#ifndef _ALLOCATION_H
#define _ALLOCATION_H

#include "structure_log.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

void init_tableau_global(int taille);
int nombre_lignes(FILE * fp);
int nombre_lignes_geoloc(FILE * fp);
logs allocation_tableau_point(int taille);
void liberer (logs tlog);
void init_logparid();
#endif
