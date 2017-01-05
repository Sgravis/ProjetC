#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include "remplissage.h"
#include "allocation.h"
#include "suppression.h"
#include "structure_log.h"
#include "agglomeration.h"

logs agglomeration(logs tlog)
{
	int i,j;
	logs tlog2=CopieTableau(tlog,tlog.tailleTab);
	for (i=0 ; i<tlog2.tailleTab ; i++) 
	{
		for (j = i+1 ; j < tlog2.tailleTab ; j++)
		{
			if ((tlog2.tableauPoint[i].latitude == tlog2.tableauPoint[j].latitude) && (tlog2.tableauPoint[i].longitude == tlog2.tableauPoint[j].longitude))
			{
				tlog2.tableauPoint[j].taillept++;
				tlog2.tableauPoint[i].agglomerat=1;
				tlog2.tableauPoint[j].agglomerat=1;
			}
		}
	}
	detection_agglomerat();
	afficher_tableau(logGlobalClean.tailleTab,logGlobalClean);
	return tlog2;
}

logs initialisation_route(logs tlog)
{
	int i;
	logs tlog2=CopieTableau(tlog,tlog.tailleTab);
	for (i=0 ; i < tlog2.tailleTab ; i++)
	{
		if (tlog2.tableauPoint[i].taillept == 1)
		{
			tlog2.tableauPoint[i].route=1;
		}
	}
	return tlog2;
}

void detection_agglomerat()
{
    int i,j;
    int nb_pt_centre_interet=((logGlobal.tailleTab)/10);
    logs tmp=CopieTableau(logGlobalClean,logGlobalClean.tailleTab);
    logs tab_cercle;
    logs tab_cercle2;
    int rayon=100;
    for(i=0;i<tmp.tailleTab;i++)
    {
        tab_cercle=Detection_circulaire(tmp.tableauPoint[i],rayon,tmp);
        if (tab_cercle.tailleTab >=nb_pt_centre_interet)
        {
            for(j=0;j<tab_cercle.tailleTab;j++)
            {
                tab_cercle2=Detection_circulaire(tab_cercle.tableauPoint[j],rayon,tmp);
                if (tab_cercle2.tailleTab>tab_cercle.tailleTab)
                {
                    free(tab_cercle.tableauPoint);
                    tab_cercle.tailleTab=tab_cercle2.tailleTab;
                    tab_cercle.tableauPoint=tab_cercle2.tableauPoint;
                    j=0;
                }

            }

           ajout_agglomerat(tab_cercle);


            free(tab_cercle.tableauPoint);
        }

    }
            free(tmp.tableauPoint);

}

void ajout_agglomerat(logs tableau_agglomerat)
{
	 int i,j;
    for(i=0;i<logGlobalClean.tailleTab;i++)
    {
        for (j=0;j<tableau_agglomerat.tailleTab;j++)
        {
           if(comparaison_point(logGlobalClean.tableauPoint[i],tableau_agglomerat.tableauPoint[j])==1)
           {
           		logGlobalClean.tableauPoint[i].agglomerat=1;
           }
        }

    }
}
