#pragma once
#ifndef  BOOLEAN_TYPES_H
#define  BOOLEAN_TYPES_H

#define SIZE_ARRAY 7
static const char* names[] = { "POOL" , "PORCH", "KETTLE", "WIFI", "OPEN_SOFA", "TV", "OCCUPIED" };


typedef const enum
{
	POOL = 0, PORCH, KETTLE, WIFI, OPEN_SOFA, TV, OCCUPIED
}ROOM_BOOLEAN_TYPES;

#endif // BOOLEAN_TYPES_H






