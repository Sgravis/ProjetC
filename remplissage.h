#ifndef _REMPLISSAGE_H
#define _REMPLISSAGE_H

#include "structure_log.h"
#include "allocation.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void recuperation_donnees(FILE *fp, int nb_lignes);
void CopiePoints (point *point1,point *point2);
void BackupFile (logs tlog);
logs CopieTableau(logs tlog1, int taille);
void resurrection_point(char * nom);
void recuperation_addr();
/*void CopiePoints_base_addr (pointaddr* point1, pointaddr* point2);*/
/*addr CopieTableau_addr(addr tab,int taille);*/







#endif

