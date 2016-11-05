#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <time.h>
#include "remplissage.h"
#include "allocation.h"
#include "suppression.h"
#include <math.h>
#include <string.h>

int main()
{
 	logs tlog;
     FILE *fp;
     int nb_lignes;
     fp=fopen("geoloc-logs.txt","r");
     nb_lignes=Nombre_lignes(fp);
     Init_tableau(nb_lignes);
     printf("\nnombre de lignes :%i \n",nb_lignes);
     recuperation_donnees(fp,nb_lignes);
     fclose(fp);
     tlog=Detection_circulaire(logGlobal.tableauPoint[1],100);
     printf("%d\n",tlog.tailleTab);
     return 0;
 }
