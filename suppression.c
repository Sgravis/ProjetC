#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "structure_log.h"
#include "allocation.h"
#include "remplissage.h"
#include "suppression.h"


logs Detection_circulaire (point centre,int rayon)
{
    logs tableauCercleIntmp=AllocationTableauPoint(logGlobal.tailleTab);
    logs tableauCercleIn;
    int i;
    int incCercle=0;
    for(i=0;i<logGlobal.tailleTab;i++)
    {
        if (sqrt(pow(((logGlobal.tableauPoint[i].latitude-centre.latitude)*111*1000),2)+pow(((centre.longitude-logGlobal.tableauPoint[i].longitude)*76*1000),2))<rayon)
        {
            CopiePoints(&logGlobal.tableauPoint[i],&tableauCercleIntmp.tableauPoint[incCercle++]);
        }
    }
    tableauCercleIn=CopieTableau(tableauCercleIntmp,incCercle);
    return tableauCercleIn;
}

void suppression(logs tableauSupp)
{
    int i,j;
    int incTabClean=0;
    logs Logcleantmp=AllocationTableauPoint(logGlobalClean.tailleTab);
    for(i=0;i<logGlobalClean.tailleTab;i++)
    {
        for (j = 0; j < tableauSupp.tailleTab;j++)
        {
             if (&(tableauSupp.tableauPoint[j])!=&(logGlobalClean.tableauPoint[i]))
            {
                CopiePoints(&(logGlobalClean.tableauPoint[j]),&(Logcleantmp.tableauPoint[incTabClean++]));
            }
        }
    }
    logGlobalClean=CopieTableau(Logcleantmp,incTabClean);
    BackupFile(tableauSupp);
}



void detection_pt_interet()
{
    int i,j;
    int nb_pt_centre_interet=5;
    printf("\n nb point pour etre un point d'interet dans le cercle : %i \n",nb_pt_centre_interet);
    logs tab_cercle;
    logs tab_cercle2;
    int rayon=20;
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
