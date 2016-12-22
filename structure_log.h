#ifndef _STRUCTURE_LOG_H
#define _STRUCTURE_LOG_H

#include <time.h>

typedef struct {
	int ID_user;
	long double longitude;
	long double latitude;
	time_t date;
	int taillept;
}point;

typedef struct
{
	point * tableauPoint;
	int tailleTab;
}logs;



logs logGlobal;
logs logGlobalClean;
logs logBack;
logs base_adresse;

char tableauID[100][15];

#endif
