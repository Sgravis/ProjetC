#ifndef _agglomeration_h
#define _agglomeration_h

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include "remplissage.h"
#include "allocation.h"
#include "suppression.h"
#include "structure_log.h"
#include "agglomeration.h"

void agglomeration ();
void initialisation_route();
void detection_agglomerat();
void redefinition_grosseur_agglomerat(logs a_supr, float rayon, logs * tmp);
void ajout_agglomerat(logs tableau_agglomerat, float rayon, logs *tmp);

#endif
