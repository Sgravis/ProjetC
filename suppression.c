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


logs Detection_circulaire (point centre,int rayon, logs base)
{
    logs tableauCercleIntmp=AllocationTableauPoint(base.tailleTab);
    logs tableauCercleIn;
    int i;
    int incCercle=1;
    CopiePoints(&centre,&tableauCercleIntmp.tableauPoint[0]);
    for(i=1;i<=base.tailleTab;i++)
    {   
        if (sqrt(pow(((base.tableauPoint[i].latitude-centre.latitude)*111*1000),2)+pow(((centre.longitude-base.tableauPoint[i].longitude)*76*1000),2))<rayon)
        {
            CopiePoints(&base.tableauPoint[i],&tableauCercleIntmp.tableauPoint[incCercle++]);
        }
    }
    tableauCercleIn=CopieTableau(tableauCercleIntmp,incCercle);
    free(tableauCercleIntmp.tableauPoint);
    return tableauCercleIn;
}
logs Detection_circulaire_base_adresse (point centre,int rayon)
{
    logs tableauCercleIntmp=AllocationTableauPoint(base_adresse.tailleTab);
    logs tableauCercleIn;
    int i;
    int incCercle=0;
    for(i=0;i<base_adresse.tailleTab;i++)
    {
        if (sqrt(pow(((base_adresse.tableauPoint[i].latitude-centre.latitude)*111*1000),2)+pow(((centre.longitude-base_adresse.tableauPoint[i].longitude)*76*1000),2))<rayon)
        {
            CopiePoints(&base_adresse.tableauPoint[i],&tableauCercleIntmp.tableauPoint[incCercle++]);
        }
    }
    tableauCercleIn=CopieTableau(tableauCercleIntmp,incCercle);
    free(tableauCercleIntmp.tableauPoint);
    return tableauCercleIn;
}


void suppression(logs tableauSupp, logs *base)
{
    int i,j,a;
    int incTabClean=0;
    logs Logcleantmp=AllocationTableauPoint(base->tailleTab);
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
            CopiePoints(&(base->tableauPoint[i]),&(Logcleantmp.tableauPoint[incTabClean++]));

        }
    }
    free(base->tableauPoint);
    *base=CopieTableau(Logcleantmp,incTabClean);
    BackupFile(tableauSupp);

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
    logs tmp=CopieTableau(logGlobalClean,logGlobalClean.tailleTab);
    logs tab_cercle;
    logs tab_cercle2;
    int rayon=70;
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
           // suppression(tab_cercle);

            redefinition_grosseur_cercle(tab_cercle,rayon,&tmp);


            free(tab_cercle.tableauPoint);
        }

    }
            free(tmp.tableauPoint);


}
void redefinition_grosseur_cercle(logs a_supr, int rayon, logs * tmp)
{
    int reponse;
    logs tab_pt_interet_ds_cercle=Detection_circulaire_base_adresse(a_supr.tableauPoint[0],rayon);/*enlever car global*/
    if(tab_pt_interet_ds_cercle.tailleTab<20)
    {
        do 
        {    
            rayon=rayon+25;
            tab_pt_interet_ds_cercle=Detection_circulaire_base_adresse(a_supr.tableauPoint[0],rayon);/* enlever car global*/
        }while(tab_pt_interet_ds_cercle.tailleTab<20);

    }
    a_supr=Detection_circulaire(a_supr.tableauPoint[0],rayon,*tmp);
    cairo_set_source_rgb(cr,1,1,0);
    cairo_set_line_width(cr,1);
    cairo_arc(cr,coord_to_pixel_long(a_supr.tableauPoint[0].longitude), coord_to_pixel_lat(a_supr.tableauPoint[0].latitude),rayon, 0, 2 * M_PI);
    cairo_stroke(cr);
    sleep(1);
    reponse=popup("Anonymiser le cercle?");
    if(reponse==1)
    {
        suppression(a_supr,&logGlobalClean);
        suppression(a_supr,tmp);
    }
    else
    {
        suppression(a_supr,tmp);
    }

   free(tab_pt_interet_ds_cercle.tableauPoint);
   maj_map();
}

void afficher_tableau(int taille, logs tab)
{
    int i;
    for(i=0;i<taille;i++)
    {
        //printf("date:%ld,lat:%Lf,long:%Lf\n",tab.tableauPoint[i].date,tab.tableauPoint[i].latitude,tab.tableauPoint[i].longitude);
        //printf("%d\n",tab.tableauPoint[i].route );
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
    logs tlogcleantmp=CopieTableau(tlog,tlog.tailleTab);
    int i;
    for (i=0 ; i<tlog2.tailleTab ; i++)
    {
        if ()
    }
}*/

