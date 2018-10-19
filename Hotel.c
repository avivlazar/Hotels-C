#include "Hotel.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "BooleanTypes.h"
#include "EncodeAndDecode.h"
#pragma warning(disable: 4996)


/* read hotel from user */
void readHotelFromUser(Hotel_t* hotel)
{


	// Read floors
	printf("\nPlease enter number of floors: ");
	scanf("%d", &(hotel->floors));
	while (hotel->floors < MIN_NUM_OF_FLOORS)
	{
		printf("\nPlease enter a number above %d: ", MIN_NUM_OF_FLOORS - 1);
		scanf("%d", &(hotel->floors));
	}

	// Read number of rooms each floor
	printf("\nPlease enter number of rooms each floor: ");
	scanf("%d", &(hotel->roomsEachFloor));
	while (hotel->roomsEachFloor < MIN_NUM_OF_ROOMS_EACH_FLOOR || hotel->roomsEachFloor > MAX_NUM_OF_ROOMS_EACH_FLOOR)
	{
		printf("\nPlease enter a number btween %d and %d : ", MIN_NUM_OF_ROOMS_EACH_FLOOR, MAX_NUM_OF_ROOMS_EACH_FLOOR);
		scanf("%d", &(hotel->roomsEachFloor));
	}


	// set memory allocation for each floor
	hotel->roomsMatrix = (Room_t**)malloc(hotel->floors * sizeof(Room_t*));

	int i, j;  // helpful parameters

	for (i = 0; i < hotel->floors; i++)
	{   // set memory allocation for all rooms in a 'i' floor
		hotel->roomsMatrix[i] = (Room_t*)malloc(hotel->roomsEachFloor * sizeof(Room_t));
	}

	// read information from user about each room
	for (i = 0; i < hotel->floors; i++)
	{
		for (j = 0; j < hotel->roomsEachFloor; j++)
		{
			createRoomByRandom((hotel->roomsMatrix)[i] + j);  // room number 'j' in floor number 'i' (pointer)
		}
	}
}


void printHotel(Hotel_t* hotel)
{
	int i, j;  // helpful parameters
	for (i = 0; i < hotel->floors; i++)
	{
		printf("\n\n\nFloor %d", i + 1);
		for (j = 0; j < hotel->roomsEachFloor; j++)
		{
			printf("\n\nRoom %d", j + 1);
			printRoom((hotel->roomsMatrix)[i] + j);  // room number 'j' in floor number 'i'
		}
	}
}


/* Print all rooms in hotel which have the characteristic */
void printAllRoomsInHotelWithProAndNotOccuppied(Hotel_t* hotel, int roomBooleanType)
{
	int i, j;
	Room_t* currentRoom;
	for (i = 0; i < hotel->floors; i++)
	{
		for (j = 0; j < hotel->roomsEachFloor; j++)
		{
			currentRoom = hotel->roomsMatrix[i] + j;
			if (isRoomHasPro(currentRoom, roomBooleanType) && !isRoomHasPro(currentRoom, OCCUPIED))
			{
				printf("\nFloor n. %d room n. %d", i + 1, j + 1);
			}
		}
	}
}



/* Read from 'file' the hole information in 'hotel' by decoding it with 'x'*/

/* Assumptions:  */
/* 1) 'file' is exist, and is binary file*/
/* 2) 'hotel' was already allocated, */
/* 3) 'x' is between 0 to 7. */
int readHotel(Hotel_t* hotel, FILE* file, int x)
{
	// read and decode num of floors
	fread(&(hotel->floors), sizeof(int), 1, file);
	decodeStruct(&(hotel->floors), sizeof(int), x);

	// read and decode num of rooms each floor
	fread(&(hotel->roomsEachFloor), sizeof(int), 1, file);
	decodeStruct(&(hotel->roomsEachFloor), sizeof(int), x);

	// creating allocated memory the floors
	hotel->roomsMatrix = (Room_t**)malloc(sizeof(Room_t*) * hotel->floors);

	int i;
	// creating allocated memory rooms each floor (loop 1)
	for (i = 0; i < hotel->floors; i++)
	{
		hotel->roomsMatrix[i] = (Room_t*)malloc(sizeof(Room_t) * hotel->roomsEachFloor);
	}

	// read from file and encoding each floor (loop 2)
	Room_t* floorPointer;
	for (i = 0; i < hotel->floors; i++)
	{   // ex: floors = 4;
		// read floor 'i' when: every floor has 'hotel->roomsEachFloor' rooms, and each room has 'sizeof(Room_t)' bytes.
		floorPointer = hotel->roomsMatrix[i];
		fread(floorPointer, sizeof(Room_t), hotel->roomsEachFloor, file);

		// decode whole floor number 'i'
		decodeStruct(floorPointer, (sizeof(Room_t) * hotel->roomsEachFloor), x);
	}

	return 1;
}





/* Write to 'file' the hole information in 'hotel' by encoding it with 'x'*/
/*the method allocates new hotel ('copy') for not ruin the origin hotel value, and free it.*/
/* Assumptions:  */
/* 1) 'file' is exist,*/
/* 2) 'hotel' was already allocated, */
/* 3) 'x' is between 0 to 7. */
void writeHotel(Hotel_t* hotel, FILE* file, int x)
{
	Hotel_t* copy = (Hotel_t*)malloc(sizeof(Hotel_t));
	hotelcpy(copy, hotel);


	// encode and write num of floors
	encodeStruct(&(copy->floors), sizeof(int), x);
	fwrite(&(copy->floors), sizeof(int), 1, file);

	// encode and write num of rooms each floor
	encodeStruct(&(copy->roomsEachFloor), sizeof(int), x);
	fwrite(&(copy->roomsEachFloor), sizeof(int), 1, file);

	int i;
	for (i = 0; i < hotel->floors; i++)
	{
		// Encode whole floor number 'i'
		Room_t* floorPointer = copy->roomsMatrix[i];
		encodeStruct(floorPointer, (sizeof(Room_t) * hotel->roomsEachFloor), x);

		// write floor 'i' when: every floor has 'hotel->roomsEachFloor' rooms, and each room has 'sizeof(Room_t)' bytes.
		fwrite(floorPointer, sizeof(Room_t), hotel->roomsEachFloor, file);
	}// end of writing to file

	 // free copy:
	copy->floors = hotel->floors;
	copy->roomsEachFloor = hotel->roomsEachFloor;
	freeHotel(copy);
}



/* like memcpy but specific for hotel*/
Hotel_t* hotelcpy(Hotel_t* dest, const Hotel_t* source)
{
	dest->floors = source->floors;
	dest->roomsEachFloor = source->roomsEachFloor;

	// set matrix (floors)
	dest->roomsMatrix = (Room_t**)malloc(sizeof(Room_t*) * source->floors);

	int i, numOfBytesForFloor = sizeof(Room_t) * source->roomsEachFloor;
	for (i = 0; i < source->floors; i++)
	{
		dest->roomsMatrix[i] = (Room_t*)malloc(numOfBytesForFloor);
		memcpy(dest->roomsMatrix[i], source->roomsMatrix[i], numOfBytesForFloor);
	}
	return dest;
}



void freeHotel(Hotel_t* hotel)
{
	int i;
	for (i = 0; i < hotel->floors; i++)
	{
		free(hotel->roomsMatrix[i]);
	}
	free(hotel);
}



