#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include "structure_log.h"
#include "allocation.h"
#include "remplissage.h"
#include "visuel.h"
#include "interaction.h"
#include "agglomeration.h"



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
            logGlobal.tableauPoint[nb_donnees].route=0;
            logGlobal.tableauPoint[nb_donnees].agglomerat=0;
            logGlobal.tableauPoint[nb_donnees].numero_rue=0;
            strcpy(logGlobal.tableauPoint[nb_donnees].adresse," ");

            nb_donnees++;



            }
        }
        printf("\nnb donnee:%i\n",nb_donnees);

        logGlobal.tailleTab=nb_donnees;

    }





void copie_points (point* point1, point* point2)
{

    *point2=*point1;

}

/*void copie_points_base_addr (pointaddr* point1, pointaddr* point2)
{

   *point2=*point1;

}*/

logs copie_tableau(logs tlog,int taille)
{
    logs tableauCopie=allocation_tableau_point(taille);
    int i;
    for (i=0;i<taille;i++)
    {
        copie_points(&tlog.tableauPoint[i],&tableauCopie.tableauPoint[i]);
    }
    return tableauCopie;
}

/*addr copie_tableau_addr(addr tab,int taille)
{
    addr tableauCopie;
    tableauCopie.tailleTableauAddr=taille;
    tableauCopie.tableauPointaddr=(pointaddr*)malloc(taille*sizeof(pointaddr));
    int i;
    for (i=0;i<taille;i++)
    {
        copie_points_base_addr(&tab.tableauPointaddr[i],&tableauCopie.tableauPointaddr[i]);
    }
    return tableauCopie;
}*/


void backup_file(logs tlog)
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
        fputs(";",fichier);
        fputs("\n",fichier);
    }
    fclose(fichier);
    nb_passages++;
}

void resurrection_point()
{
        FILE *fp;


        fp=fopen("BackupPoints.txt","r");
        if (!fp)
        {
            popupclose("pas de points à ressuciter");
            return;
        }
        int nb_lignes;
        nb_lignes=nombre_lignes(fp);
        nb_lignes--;
        int i;
        time_t date;
        char c[20];
        long double lat;
        long double longi;
        fseek(fp,0,SEEK_SET);
        logBack=allocation_tableau_point(nb_lignes);
        gtk_widget_hide(Button_Affichage_pt_supp);
        gtk_widget_show(Button_Remise_pt_normal);
        for(i=0;i<nb_lignes;i++)
        {
            fgets(c,6,fp);
            fscanf(fp,"%ld",&date);
            fgets(c,6,fp);
            fscanf(fp,"%Lf",&lat);
            fgets(c,7,fp);
            fscanf(fp,"%Lf",&longi);
            fgets(c,3,fp);
            logBack.tableauPoint[i].longitude=longi;
            logBack.tableauPoint[i].latitude=lat;
            logBack.tableauPoint[i].date=date;
            logBack.tableauPoint[i].taillept=1;
            logBack.tableauPoint[i].route=0;
            logBack.tableauPoint[i].agglomerat=0;
        }
        logBack.tailleTab=nb_lignes;
        //reset_log_aff();
        ajout_log_aff(&logBack);
        //g_signal_connect(G_OBJECT(darea),"draw",G_CALLBACK(on_draw),&logBack);
        maj_map();
}

void remise_pt_normal(){
    gtk_widget_show(Button_Affichage_pt_supp);
    gtk_widget_hide(Button_Remise_pt_normal);
    reset_log_aff();
    ajout_log_aff(&logGlobalClean);
    maj_map();

}

void recuperation_addr() /* au lieu initialiser ici la base adresse, faire une fonction d'initialisation*/
{
    FILE *fp;
    int numero;
    char c;
    char adresse[40];
    int i,j,nb_lignes,k=0;
    fp=fopen("AddrConvert.txt","r");
    nb_lignes=nombre_lignes(fp);
    fseek(fp,0,SEEK_SET);
    base_adresse.tailleTab=nb_lignes-1;
    base_adresse.tableauPoint=(point*)malloc(nb_lignes*sizeof(point)); /*utiliser la fonction deja etablie*/
    for(i=0;i<nb_lignes-1;i++)
    {
            c=fgetc(fp);
            while(c !=',')
            {
                c=fgetc(fp);
            }

            fscanf(fp,"%i",&(base_adresse.tableauPoint[i].numero_rue));
            c=fgetc(fp);
            c=fgetc(fp);
            while(c !=',')
            {
                adresse[k]=c;
                k++;
                c=fgetc(fp);
            }
            strcpy(base_adresse.tableauPoint[i].adresse,adresse);
                c=fgetc(fp);
                while(c !=',')
                {
                    c=fgetc(fp);
                }
        fscanf(fp,"%Lf",&(base_adresse.tableauPoint[i].longitude));
        c=fgetc(fp);
        fscanf(fp,"%Lf",&(base_adresse.tableauPoint[i].latitude));
        c=fgetc(fp);
        base_adresse.tableauPoint[i].date=0;
        for(j=0;j<=k;j++)
        {
            adresse[j]=' ';
        }
        k=0;

    }
}
void remise_a_zero()
{
    free(logGlobalClean.tableauPoint);
    logGlobalClean=copie_tableau(logGlobal,logGlobal.tailleTab);
    agglomeration(logGlobal);
    initialisation_route(logGlobalClean);
    if(remove("BackupPoints.txt")<0)
    {
        perror("");
    }
    reset_log_aff();
    ajout_log_aff(&logGlobalClean);
    maj_map();
}

void cacher_points_interets()
{
    tableau_centre_interet[0].taillept=0;
    gtk_widget_hide(Button_DesAffichage_Points_Interets);
    gtk_widget_show(Button_Affichage_Points_Interets);
    maj_map();
}


void affichage_points_interets()
{   
    gtk_widget_hide(Button_Affichage_Points_Interets);
    gtk_widget_show(Button_DesAffichage_Points_Interets);
    int i,j;
    int nb_pt_centre_interet=((logGlobalClean.tailleTab)/12);
    logs tmp=copie_tableau(logGlobalClean,logGlobalClean.tailleTab);
    logs tab_cercle;
    logs tab_cercle2;
    int rayon=100;
    int cpt=1;
    tableau_centre_interet[0].taillept=0;
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
            suppression_sans_backup(tab_cercle,&tmp);
            tableau_centre_interet[cpt]=tab_cercle.tableauPoint[0];
            tableau_centre_interet[cpt].taillept=rayon; 
            recherche_adresse_point(tab_cercle.tableauPoint[0],cpt);
            cpt++;  
            free(tab_cercle.tableauPoint);
            
        }

    }

            free(tmp.tableauPoint);
            tableau_centre_interet[0].taillept=cpt-1;
            maj_map();
    
}

void recherche_adresse_point(point p,int cpt)
{
    float rayon=1;
    logs adresses_trouves=detection_circulaire(p,rayon,base_adresse);
    while (adresses_trouves.tailleTab != 2 && adresses_trouves.tailleTab != 3)
    {
        if(adresses_trouves.tailleTab < 2)
        {
            rayon++;
        }
        else{
            rayon=rayon-0.1;
        }
        adresses_trouves=detection_circulaire(p,rayon,base_adresse);
    }

    tableau_centre_interet[cpt].numero_rue=adresses_trouves.tableauPoint[1].numero_rue;
    strcpy(tableau_centre_interet[cpt].adresse,adresses_trouves.tableauPoint[1].adresse);

}