#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include "structure_log.h"
#include "allocation.h"
#include "remplissage.h"
#include "suppression.h"


logs Detection_circulaire (point centre,int rayon)
{
    logs tableauCercleIntmp=AllocationTableauPoint(logGlobalClean.tailleTab);
    logs tableauCercleIn;
    int i;
    int incCercle=0;
    for(i=0;i<logGlobalClean.tailleTab;i++)
    {
        if (sqrt(pow(((logGlobalClean.tableauPoint[i].latitude-centre.latitude)*111*1000),2)+pow(((centre.longitude-logGlobalClean.tableauPoint[i].longitude)*76*1000),2))<rayon)
        {
            CopiePoints(&logGlobalClean.tableauPoint[i],&tableauCercleIntmp.tableauPoint[incCercle++]);
        }
    }
    tableauCercleIn=CopieTableau(tableauCercleIntmp,incCercle);
    free(tableauCercleIntmp.tableauPoint);
    return tableauCercleIn;
}

void suppression(logs tableauSupp)
{
    int i,j,a;
    int incTabClean=0;
    logs Logcleantmp=AllocationTableauPoint(logGlobalClean.tailleTab);
    for(i=0;i<logGlobalClean.tailleTab;i++)
    {
        a=0;
        for (j=0; j < tableauSupp.tailleTab;j++)
        {
             if (comparaison_point(tableauSupp.tableauPoint[j],logGlobalClean.tableauPoint[i])==1)
            {
                a=1;
            }
            
        }
        if (a!=1)
        {
            CopiePoints(&(logGlobalClean.tableauPoint[i]),&(Logcleantmp.tableauPoint[incTabClean++]));

        }
    }
    free(logGlobalClean.tableauPoint);
    logGlobalClean=CopieTableau(Logcleantmp,incTabClean);
    BackupFile(tableauSupp);

}

int comparaison_point(point p1, point p2)
{

    if(p1.longitude!=p2.longitude)
    {
        return -1;
    }
    if(p1.latitude!=p2.latitude)
    {
        return -1;
    }
    if(p1.date!=p2.date)
    {
        return -1;
    }
    return 1;
}


void detection_pt_interet()
{
    int i,j;
    int nb_pt_centre_interet=50;
    logs tab_cercle;
    logs tab_cercle2;
    int rayon=40;
    for(i=0;i<logGlobalClean.tailleTab;i++)
    {
        tab_cercle=Detection_circulaire(logGlobalClean.tableauPoint[i],rayon);
        if (tab_cercle.tailleTab >=nb_pt_centre_interet)
        {
            for(j=0;j<tab_cercle.tailleTab;j++)
            {
                tab_cercle2=Detection_circulaire(tab_cercle.tableauPoint[j],rayon);
                if (tab_cercle2.tailleTab>tab_cercle.tailleTab)
                {
                    free(tab_cercle.tableauPoint);
                    tab_cercle.tailleTab=tab_cercle2.tailleTab;
                    tab_cercle.tableauPoint=tab_cercle2.tableauPoint;
                    j=0;
                }

            }
            suppression(tab_cercle);
            free(tab_cercle.tableauPoint);
        }

    }


}

void afficher_tableau(int taille, logs tab)
{
    int i;
    for(i=0;i<taille;i++)
    {
        printf("date:%ld,lat:%Lf,long:%Lf\n",tab.tableauPoint[i].date,tab.tableauPoint[i].latitude,tab.tableauPoint[i].longitude);
    }

}
void afficher_tableau2(int taille, addr tab)
{
    int i;
    for(i=0;i<15;i++)
    {
        printf("long:%Lf,lat:%Lf\n",tab.tableauPointaddr[i].latitude,tab.tableauPointaddr[i].longitude);
    }

}
