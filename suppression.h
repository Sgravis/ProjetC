#ifndef _SUPPRESSION_H
#define _SUPPRESSION_H

#include "structure_log.h"
#include "allocation.h"
#include "remplissage.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

logs Detection_circulaire(point centre, int rayon);
void detection_pt_interet();
void Suppression_circulaire(logs tableauSupp);



#endif
