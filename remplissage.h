#ifndef _REMPLISSAGE_H
#define _REMPLISSAGE_H

#include "structure_log.h"
#include "allocation.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void recuperation_donnees(FILE *fp, int nb_lignes);
void CopiePoints (point * point1,point * point2);
void BackupFile (logs tlog);
logs CopieTableau (logs tlog,int taille);






#endif
