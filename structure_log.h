#ifndef _STRUCTURE_LOG_H
#define _STRUCTURE_LOG_H

#include <time.h>

typedef struct {
int ID_user;
long double longitude;
long double latitude;
struct tm date;
}point;

typedef struct
{
	point * tableauPoint;
	int tailleTab;
}logs;

logs logGlobal;

char tableauID[100][15];

#endif
