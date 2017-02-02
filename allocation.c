#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include "structure_log.h"
#include "allocation.h"
#include "suppression.h"

 int nombre_lignes_geoloc(FILE * fp)
 {
    fseek(fp,0,SEEK_SET);
    char c;
    int cpt=0;
    int nblignes;
    while((c=fgetc(fp))!='%')
    {
        cpt++;
    }
    c=fgetc(fp);
    if (c == '\n')
    {
        fscanf(fp,"%d",&nblignes);
    }
    return nblignes;
 }

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
    tlog.tableauPoint=(point*)calloc(taille,sizeof(point));
    tlog.tailleTab=taille;
    return tlog;
}

void init_logparid()
{
    int i;
    logGlobalClean=(logs *)calloc(nb_id,sizeof(logs));
    for (i = 0 ; i<nb_id ; i++)
    {
        logGlobalClean[i]=allocation_tableau_point(tableid[i]);

    }
}

/*void liberer(logs tlog)
{
    int i;
    for (i=0;i<tlog.tailleTab;i++)
    {
        free(&tlog.tableauPoint[i]);
    }
}*/
