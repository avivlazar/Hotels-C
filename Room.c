#pragma once
#pragma once
#include <stdio.h>
#include <stdlib.h>  // for 'srand'
#include <stdarg.h>  // for variadic function
#include "Room.h"
#include "Bits_Functions.h"
#include "BooleanTypes.h"


/* Print room information by room pointer*/
void printRoom(Room_t* roomPointer)
{
	printf("\nNumber of beds in Rooms : %-2d", roomPointer->numOfBeds);
	int i = 0;
	for (i = 0; i < SIZE_ARRAY; i++)
	{
		if (getBitFromRight(roomPointer->roomChars, i) == 1)
		{
			printf("\n  ---  has %s", names[i]);
		}
		else
		{
			printf("\n  ---  hasn't %s", names[i]);
		}
	}
}


/* Get room information from the manager */
void createRoomByRandom(Room_t* roomPointer)
{
	int num = rand() % 128;
	//printf("\nnum : %d", num);
	roomPointer->roomChars = (unsigned char)num;  // random value to all booleans of this room (0 - 127)

												  // Example:
	roomPointer->numOfBeds = (rand() % 4) + 1;  // numOfBeds = (1 - 4)
												//printf("\nNum of beds: %d", roomPointer->numOfBeds);
}


/* check if the room has characteristic */
/* return 1 when the characteristic is there, else 0*/
int isRoomHasPro(Room_t* roomPointer, int roomBooleanType)
{
	return getBitFromRight(roomPointer->roomChars, roomBooleanType);
}


/* Print rooms' pointers that have the characteristic*/
/* The method return the number of rooms which have the characteristic*/
/* The method recieves unlimited number of pointers (for rooms)*/
/* The method returns the num of rooms that were sent*/
/* and the NULL pointer for last*/
int printRoomsWithPropertyByVariadicFunction(int roomBooleanType, ...)
{
	int counter = 0;
	va_list allRoomPointers;  // the list wich contains 'room pointers '
	Room_t* currentRoomPointer;

	va_start(allRoomPointers, roomBooleanType);  // start reading to list after 'roomBooleanType'

	currentRoomPointer = va_arg(allRoomPointers, Room_t*);  // get next Room* from list

	while (currentRoomPointer != NULL)
	{   // while there are rooms:
		if (isRoomHasPro(currentRoomPointer, roomBooleanType) == 1)
		{  // if the room has the  characteristic:
			counter++;
			printf("\nRoom n. %d", counter);
			printRoom(currentRoomPointer);  // print the room!!!
		}
		else;  // do nothing. The method doesn't show rooms which doesn't have 'roomBooleanType'
		currentRoomPointer = va_arg(allRoomPointers, Room_t*);  // get next Room* from list
	}
	return counter;
}



