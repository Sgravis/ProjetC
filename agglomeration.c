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
			}
		}
	}
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

