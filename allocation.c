#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include "structure_log.h"
#include "allocation.h"

 int nombre_lignes(FILE * fp)
 {
    fseek(fp,0,SEEK_SET);
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

void init_tableau_global(int taille)
 {
    logGlobal.tableauPoint= (point*)malloc(taille*sizeof(point));

 }

logs allocation_tableau_point(int taille)
{   
    logs tlog;
    tlog.tableauPoint=(point*)malloc(taille*sizeof(point));
    tlog.tailleTab=taille;
    return tlog;
}

/*void liberer(logs tlog)
{
    int i;
    for (i=0;i<tlog.tailleTab;i++)
    {
        free(&tlog.tableauPoint[i]);
    }
}*/
