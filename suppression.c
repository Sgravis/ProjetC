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


void Detection_pt_interet()
{
    int i,j;
    int nb_pt_centre_interet=logGlobal.tailleTab%10;
    printf("\n nb point pour etre un point d'interet dans le cercle : %i \n",nb_pt_centre_interet);
    logs tab_cercle;
    logs tab_cercle2;
    int rayon=20;
    for(i=0;i<logGlobal.tailleTab;i++)
    {
        tab_cercle=Detection_circulaire(logGlobal.tableauPoint[i],rayon);
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
            Supression_Circulaire(tab_cercle);
            free(tab_cercle.tableauPoint);
        }

    }




}
void Suppression_circulaire (logs tableauSupp)
{
    int i,j;
    int incTabClean=0;
    for(i=0;i<tableauSupp.tailleTab;i++)
    {
        for (j = 0; j < logGlobal.tailleTab;j++)
        {
             if (&(tableauSupp.tableauPoint[i])!=&(logGlobal.tableauPoint[j]))
            {
                CopiePoints(&logGlobal.tableauPoint[j],&logGlobalClean.tableauPoint[incTabClean++]);
            }
        }
    }
    BackupFile(tableauSupp);
}