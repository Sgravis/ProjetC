#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include "structure_log.h"
#include "allocation.h"
#include "remplissage.h"
#include "suppression.h"
#include "visuel.h"
#include "interaction.h"


logs detection_circulaire (point centre,float rayon, logs base)
{
    logs tableauCercleIntmp=allocation_tableau_point(base.tailleTab);
    logs tableauCercleIn;
    int i;
    int incCercle=1;
    copie_points(&centre,&tableauCercleIntmp.tableauPoint[0]);
    for(i=1;i<=base.tailleTab;i++)
    {   
        if (sqrt(pow(((base.tableauPoint[i].latitude-centre.latitude)*111*1000),2)+pow(((centre.longitude-base.tableauPoint[i].longitude)*76*1000),2))<rayon)
        {
            copie_points(&base.tableauPoint[i],&tableauCercleIntmp.tableauPoint[incCercle++]);
        }
    }
    tableauCercleIn=copie_tableau(tableauCercleIntmp,incCercle);
    free(tableauCercleIntmp.tableauPoint);
    return tableauCercleIn;
}

void suppression_avec_backup(logs tableauSupp, logs *base)
{
    int i,j,a;
    int incTabClean=0;
    logs Logcleantmp=allocation_tableau_point(base->tailleTab);
    for(i=0;i<base->tailleTab;i++)
    {
        a=0;
        for (j=0; j < tableauSupp.tailleTab;j++)
        {
             if (comparaison_point(tableauSupp.tableauPoint[j],base->tableauPoint[i])==1)
            {
                a=1;
            }
            
        }
        if (a!=1)
        {
            copie_points(&(base->tableauPoint[i]),&(Logcleantmp.tableauPoint[incTabClean++]));

        }
    }
    free(base->tableauPoint);
    *base=copie_tableau(Logcleantmp,incTabClean);
    backup_file(tableauSupp);

}
void suppression_sans_backup(logs tableauSupp, logs *base)
{
    int i,j,a;
    int incTabClean=0;
    logs Logcleantmp=allocation_tableau_point(base->tailleTab);
    for(i=0;i<base->tailleTab;i++)
    {
        a=0;
        for (j=0; j < tableauSupp.tailleTab;j++)
        {
             if (comparaison_point(tableauSupp.tableauPoint[j],base->tableauPoint[i])==1)
            {
                a=1;
            }
            
        }
        if (a!=1)
        {
            copie_points(&(base->tableauPoint[i]),&(Logcleantmp.tableauPoint[incTabClean++]));

        }
    }
    free(base->tableauPoint);
    *base=copie_tableau(Logcleantmp,incTabClean);

}
int comparaison_point(point p1, point p2)
{

    if(p1.longitude!=p2.longitude)
    {
        return -1;
    }
    if(p1.latitude!=p2.latitude)
    {
        return -1;
    }
    if(p1.date!=p2.date)
    {
        return -1;
    }
    return 1;
}


void detection_pt_interet()
{
    int i,j;
    int nb_pt_centre_interet=((logGlobal.tailleTab)/10);
    logs tmp=copie_tableau(logGlobalClean,logGlobalClean.tailleTab);
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

            redefinition_grosseur_cercle(tab_cercle,rayon,&tmp);
            free(tab_cercle.tableauPoint);
        }

    }
            free(tmp.tableauPoint);


}
void redefinition_grosseur_cercle(logs a_supr, float rayon, logs * tmp)
{
    int reponse;
    logs tab_pt_interet_ds_cercle=detection_circulaire(a_supr.tableauPoint[0],rayon,base_adresse);
    if(tab_pt_interet_ds_cercle.tailleTab<20)
    {
        do 
        {    
            rayon=rayon+25;
            tab_pt_interet_ds_cercle=detection_circulaire(a_supr.tableauPoint[0],rayon,base_adresse);
        }while(tab_pt_interet_ds_cercle.tailleTab<20);

    }
    a_supr=detection_circulaire(a_supr.tableauPoint[0],rayon,*tmp);

    tmp_ano=a_supr.tableauPoint[0];
    tmp_ano.taillept=rayon;

    reponse=popup("Anonymiser le cercle?");
    if(reponse==1)
    {
        suppression_avec_backup(a_supr,&logGlobalClean);
        suppression_sans_backup(a_supr,tmp);
    }
    else
    {
        suppression_sans_backup(a_supr,tmp);
    }
    tmp_ano.longitude=-1;
    tmp_ano.latitude=-1;
    tmp_ano.taillept=0;

   free(tab_pt_interet_ds_cercle.tableauPoint);
   maj_map();
}

void afficher_tableau(int taille, logs tab)
{
    int i;
    for(i=0;i<taille;i++)
    {
       printf("date:%ld,lat:%Lf,long:%Lf\n",tab.tableauPoint[i].date,tab.tableauPoint[i].latitude,tab.tableauPoint[i].longitude);
    }
}
/*void afficher_tableau2()
{
    int i;
    for(i=0;i<15;i++)
    {
        printf("long:%Lf,lat:%Lf\n",base_adresse.tableauPointaddr[i].latitude,base_adresse.tableauPointaddr[i].longitude);
    }

}
*/

/*logs suppression_route (logs tlog)
{
    logs tlogcleantmp=copie_tableau(tlog,tlog.tailleTab);
    int i;
    for (i=0 ; i<tlog2.tailleTab ; i++)
    {
        if ()
    }
}*/

