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
	logs tabagglo=AllocationTableauPoint(logGlobal.tailleTab); //Allocation tableau taille maximale possible
	logs tabaggloclean;
	int inctabagglo=0;
	point tampon; //Allocation point tampon pour comparaison
	for (i=0 ; i<tlog2.tailleTab ; i++) 
	{
		if (tlog2.tableauPoint[i].taillept != -1)
		{
			CopiePoints(&(tlog2.tableauPoint[i]),&tampon);
			for (j = i+1 ; j < tlog2.tailleTab ; j++)
			{
				if ((tampon.latitude == tlog2.tableauPoint[j].latitude) && (tampon.longitude == tlog2.tableauPoint[j].longitude))
				{
					tampon.taillept++;
					tlog2.tableauPoint[j].taillept=-1;
				}

			}
		CopiePoints(&tampon,&(tabagglo.tableauPoint[inctabagglo++]));
		}
		
	}
	tabaggloclean=CopieTableau(tabagglo,inctabagglo);
	return tabaggloclean;
}