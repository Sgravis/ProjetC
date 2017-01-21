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

void agglomeration()
{
	int i,j,k,cpt=0;
	logs detectmp;
	for (i=0 ; i<logGlobalClean[id_en_cours].tailleTab ; i++) 
	{
		for (j = i+1 ; j < logGlobalClean[id_en_cours].tailleTab ; j++)
		{
			if ((logGlobalClean[id_en_cours].tableauPoint[i].latitude == logGlobalClean[id_en_cours].tableauPoint[j].latitude) && (logGlobalClean[id_en_cours].tableauPoint[i].longitude == logGlobalClean[id_en_cours].tableauPoint[j].longitude))
			{
				logGlobalClean[id_en_cours].tableauPoint[j].taillept++;
			}
		}
		if (logGlobalClean[id_en_cours].tableauPoint[i].taillept > 1) {
			detectmp=detection_circulaire(logGlobalClean[id_en_cours].tableauPoint[i],1,logGlobalClean[id_en_cours]);
			cpt=0;
			for ( k=0 ; k<detectmp.tailleTab ; k++)
			{
				++cpt;
			}
			logGlobalClean[id_en_cours].tableauPoint[i].taillept+=cpt;
		}
	}
	detection_agglomerat();
}

void initialisation_route()
{
	int i;
	for (i=0 ; i < logGlobalClean[id_en_cours].tailleTab ; i++)
	{
		if (logGlobalClean[id_en_cours].tableauPoint[i].taillept == 1)
		{
			logGlobalClean[id_en_cours].tableauPoint[i].route=1;
		}
	}
}

void detection_agglomerat()
{
    int i,j;
    int nb_pt_centre_interet=((logGlobal.tailleTab)/12);
    logs tmp=copie_tableau(logGlobalClean[id_en_cours],logGlobalClean[id_en_cours].tailleTab);
    logs tab_cercle;
    logs tab_cercle2;
    float rayon=100;
    for(i=0;i<tmp.tailleTab;i++)
    {
        tab_cercle=detection_circulaire(tmp.tableauPoint[i],rayon,tmp);
        if (tab_cercle.tailleTab >=nb_pt_centre_interet)
        {
            for(j=0;j<tab_cercle.tailleTab;j++)
            {
                tab_cercle2=detection_circulaire(tab_cercle.tableauPoint[j],rayon,tmp);
                if (tab_cercle2.tailleTab>tab_cercle.tailleTab)
                {
                    free(tab_cercle.tableauPoint);
                    tab_cercle.tailleTab=tab_cercle2.tailleTab;
                    tab_cercle.tableauPoint=tab_cercle2.tableauPoint;
                    j=0;
                }

            }
           ajout_agglomerat(tab_cercle,rayon,&tmp);

            free(tab_cercle.tableauPoint);
        }

    }
            free(tmp.tableauPoint);

}

void ajout_agglomerat(logs tableau_agglomerat, float rayon, logs *tmp)
{
	int i,j;
    logs tab_agglo_redimension=detection_circulaire(tableau_agglomerat.tableauPoint[0],rayon,base_adresse);
    if(tab_agglo_redimension.tailleTab<20)
    {
        do 
        {    
            rayon=rayon+25;
            tab_agglo_redimension=detection_circulaire(tableau_agglomerat.tableauPoint[0],rayon,base_adresse);
        }while(tab_agglo_redimension.tailleTab<20);

    }
    tableau_agglomerat=detection_circulaire(tableau_agglomerat.tableauPoint[0],rayon,*tmp);
    for(i=0;i<logGlobalClean[id_en_cours].tailleTab;i++)
    {
        for (j=0;j<tableau_agglomerat.tailleTab;j++)
        {
           if(comparaison_point(logGlobalClean[id_en_cours].tableauPoint[i],tableau_agglomerat.tableauPoint[j])==1)
           {
           		logGlobalClean[id_en_cours].tableauPoint[i].agglomerat=1;
           		logGlobalClean[id_en_cours].tableauPoint[i].route=0;
           }
        }

    }
    suppression_sans_backup(tableau_agglomerat,tmp);
    free(tab_agglo_redimension.tableauPoint);

}
