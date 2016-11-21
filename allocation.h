#ifndef _ALLOCATION_H
#define _ALLOCATION_H

#include "structure_log.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

void InitLogs();
void Init_tableau(int taille);
int Nombre_lignes(FILE * fp);
logs AllocationTableauPoint(int taille);
void Liberer (logs tlog);

#endif
