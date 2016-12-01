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

typedef struct 
{
	float map_pos_x;
	float map_pos_y;
	int map_zoom;	
}map_position;

int quit;

map_position map;
logs logGlobal;
logs logGlobalClean;


char tableauID[100][15];

#endif
