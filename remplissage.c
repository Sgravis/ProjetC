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
            logGlobal.tableauPoint[nb_donnees].date=test_date;
            logGlobal.tableauPoint[nb_donnees].taillept=1;
            nb_donnees++;



            }
        }
        printf("\nnb donnee:%i\n",nb_donnees);

        logGlobal.tailleTab=nb_donnees;

    }





void CopiePoints (point* point1, point* point2)
{

    *point2=*point1;

}

logs CopieTableau(logs tlog,int taille)
{
    logs tableauCopie=AllocationTableauPoint(taille);
    int i;
    for (i=0;i<taille;i++)
    {
        CopiePoints(&tlog.tableauPoint[i],&tableauCopie.tableauPoint[i]);
    }
    return tableauCopie;
}



void BackupFile (logs tlog)
{

    static int nb_passages=0;
    FILE * fichier;
    int i;
    if(nb_passages==0)
    {
        fichier=fopen("BackupPoints.txt","w+");
    }
    else
    {
        fichier=fopen("BackupPoints.txt","a");
        fseek(fichier,0,SEEK_END);
    }
    for(i=0;i<tlog.tailleTab;i++)
    {
      
        fputs("date:",fichier);
        fprintf(fichier,"%ld",tlog.tableauPoint[i].date);
        fputs(",lat:",fichier);
        fprintf(fichier,"%Lf",tlog.tableauPoint[i].latitude);
        fputs(",long:",fichier);
        fprintf(fichier,"%Lf",tlog.tableauPoint[i].longitude);
        fputs("\n",fichier);
    }
    fclose(fichier);
    nb_passages++;
}

logs resurrection_point(char * nom)
{
        FILE *fp;
        fp=fopen(nom,"r");
        int nb_lignes;
        //nb_lignes--;
        nb_lignes=Nombre_lignes(fp);
        int i;
        time_t date;
        char c[20];
        long double lat;
        long double longi;
        fseek(fp,0,SEEK_SET);
        logs logBack = AllocationTableauPoint(nb_lignes);
        for(i=0;i<nb_lignes;i++)
        {
            fgets(c,6,fp);
            fscanf(fp,"%ld",&date);
            fgets(c,6,fp);
            fscanf(fp,"%Lf",&lat);
            fgets(c,7,fp);
            fscanf(fp,"%Lf",&longi);
            fgets(c,2,fp);
            logBack.tableauPoint[i].longitude=longi;
            logBack.tableauPoint[i].latitude=lat;
            logBack.tableauPoint[i].date=date;

            
        }
 

        logBack.tailleTab=nb_lignes;
        return logBack;

}

addr recuperation_addr()
{
    addr addrrecup;
    FILE *fp;
    char c;
    int i,j,nb_lignes;
    fp=fopen("AddrConvert.txt","r");
    
    nb_lignes=Nombre_lignes(fp);
    fseek(fp,0,SEEK_SET);
    addrrecup.tailleTableauAddr=nb_lignes;
    addrrecup.tableauPointaddr=(pointaddr*)malloc(nb_lignes*sizeof(pointaddr));
    for(i=0;i<nb_lignes;i++)
    {
        for(j=0;j<4;j++)
        {
            c=fgetc(fp);
            while(c !=',')
            {
                c=fgetc(fp);
            }
        }
        fscanf(fp,"%Lf",&(addrrecup.tableauPointaddr[i].latitude));
        c=fgetc(fp);
        fscanf(fp,"%Lf",&(addrrecup.tableauPointaddr[i].longitude));
        c=fgetc(fp);

    }
    return addrrecup;
}
