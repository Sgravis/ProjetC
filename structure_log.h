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

typedef struct{
	long double longitude;
	long double latitude;
}pointaddr;

typedef struct {
	pointaddr * tableauPointaddr;
	int tailleTableauAddr;
}addr;

logs logGlobal;
logs logGlobalClean;


char tableauID[100][15];

#endif
