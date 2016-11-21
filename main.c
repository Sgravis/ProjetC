#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <time.h>
#include "remplissage.h"
#include "allocation.h"
#include "suppression.h"
#include <math.h>
#include <string.h>

#include <math.h>
#define HFENETRE 1628.0
#define LFENETRE 680.0

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
    // logGlobalClean=CopieTableau(logGlobal,logGlobal.tailleTab);
   //  printf("lat %Lf long %Lf\n",logGlobalClean.tableauPoint[3].latitude,logGlobalClean.tableauPoint[3].longitude);
   //  detection_pt_interet();
   //  printf("taille : \n%i",logGlobalClean.tailleTab);

     return 0;






 }
