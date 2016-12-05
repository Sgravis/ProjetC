#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include "structure_log.h"
#include "allocation.h"
#include "remplissage.h"

void recuperation_donnees(FILE *fp, int nb_lignes)
    {
        int i;
        int nb_donnees=0;
        int erreur=0;
        char c;
        char date[6]="date:";
        char lat[6]=",lat:";
        char longi[7]=",long:";
        char d[20];
        char l[20];
        char lo[20];
        time_t test_date;
        struct tm temps;
        long double test_lat;
        long double test_long;
        fseek(fp,0,SEEK_SET);
        for(i=0;i<nb_lignes;i++)
        {
            erreur=0;
            fgets(d,6,fp);
            if (strcmp(d,date)!=0)
            {

                c=fgetc(fp);
                while(c != '\n' && c != EOF)
                {
                    c=fgetc(fp);
                }
                erreur=1;
            }
            if(erreur !=1)
            {

            fscanf(fp,"%ld",&test_date);
            fgets(l,6,fp);
            if (strcmp(l,lat)!=0)
            {

                c=fgetc(fp);
                while(c != '\n'&& c != EOF)
                {
                    c=fgetc(fp);
                }
                erreur=1;
            }
            }
            if (erreur !=1)
            {

            fscanf(fp,"%Lf",&test_lat);
            fgets(lo,7,fp);
            if (strcmp(lo,longi)!=0)
            {
                c=fgetc(fp);
                while(c != '\n' && c != EOF )
                {
                    c=fgetc(fp);
                }
                erreur=1;
            }
            }
            if(erreur !=1)
            {

            fscanf(fp,"%Lf",&test_long);
            c=fgetc(fp);
            if (c != ';')
            {
                c=fgetc(fp);
                while(c != '\n' && c != EOF )
                {
                    c=fgetc(fp);
                }

                erreur=1;

            }
            }
            if(erreur != 1)
            {

            c=fgetc(fp);
            if (c != '\n' && c != EOF )
            {
                c=fgetc(fp);
                while(c != '\n'&& c != EOF )
                {
                    c=fgetc(fp);
                }
                erreur=1;
            }
            }
            if (erreur!=1)
            {
            logGlobal.tableauPoint[nb_donnees].longitude=test_long;
            logGlobal.tableauPoint[nb_donnees].latitude=test_lat;
            temps=*localtime(&test_date);
            logGlobal.tableauPoint[nb_donnees].date=temps;
            nb_donnees++;



            }
        }
        printf("\nnb donnee:%i\n",nb_donnees);

        logGlobal.tailleTab=nb_donnees;

    }




void CopiePoints (point * point1,point * point2)
{
    *point2=*point1;
}

logs CopieTableau (logs tlog,int taille)
{
    logs tableauCopie=AllocationTableauPoint(taille);
    int i;
    tableauCopie.tailleTab=taille;
    for (i=0;i<taille;i++)
    {
        CopiePoints(&tlog.tableauPoint[i],&tableauCopie.tableauPoint[i]);
    }
    return tableauCopie;
}



void BackupFile (logs tlog)
{
    FILE * fichier;
    int i;
    fichier=fopen("BackupPoints.txt","w+");
    fseek(fichier,0,SEEK_END);
    for(i=0;i<tlog.tailleTab;i++)
    {
        fputs("date:",fichier);
        fprintf(fichier,"%time_t",mktime(&tlog.tableauPoint[i].date));
        fputs(",lat:",fichier);
        fprintf(fichier,"%Lf",tlog.tableauPoint[i].latitude);
        fputs(",long:",fichier);
        fprintf(fichier,"%Lf",tlog.tableauPoint[i].longitude);
        fputs("\n",fichier);
    }
    fclose(fichier);

}
