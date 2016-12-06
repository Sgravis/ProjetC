#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include "structure_log.h"
#include "allocation.h"

 int Nombre_lignes(FILE * fp)
 {
    char c;
    int compteur_lignes=0;
    while((c=fgetc(fp))!=EOF)
    {
        if (c=='\n')
        {
            compteur_lignes++;
        }

    }
    return compteur_lignes+1;
 }

void Init_tableau(int taille)
 {
    logGlobal.tableauPoint= (point*)malloc(taille*sizeof(point));
 }

logs AllocationTableauPoint(int taille)
{   
    logs tlog;
    tlog.tableauPoint=(point*)malloc(taille*sizeof(point));
    tlog.tailleTab=taille;
    return tlog;
}

void Liberer(logs tlog)
{
    int i;
    for (i=0;i<tlog.tailleTab;i++)
    {
        free(&tlog.tableauPoint[i]);
    }
}
