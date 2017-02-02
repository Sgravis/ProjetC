#ifndef _STRUCTURE_LOG_H
#define _STRUCTURE_LOG_H

#include <time.h>

typedef struct {
	int id_user;
	long double longitude;
	long double latitude;
	time_t date;
	int taillept;
	int route;
	int agglomerat;
	char adresse[40];
	int numero_rue;
}point;

typedef struct
{
	point * tableauPoint;
	int tailleTab;
}logs;


int id_en_cours;
int nb_id;
int * tableid;
logs logGlobal;
logs *logGlobalClean;
logs logBack;
logs base_adresse;

//char tableau_id[100][15];

#endif
