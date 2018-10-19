#pragma once
#include "Room.h"
#include <stdio.h>
#ifndef HOTEL_H
#define HOTEL_H


#define MIN_NUM_OF_FLOORS 1
#define MIN_NUM_OF_ROOMS_EACH_FLOOR 1
#define MAX_NUM_OF_ROOMS_EACH_FLOOR 100

typedef struct
{
	int floors;  // num of floors
	int roomsEachFloor;  // number of rooms in each floor
	Room_t** roomsMatrix;  // all rooms in hotel
}Hotel_t;

#endif // !HOTEL_H

void readHotelFromUser(Hotel_t* hotel);


void printHotel(Hotel_t* hotel);


void printAllRoomsInHotelWithProAndNotOccuppied(Hotel_t* hotel, int roomBooleanType);


int readHotel(Hotel_t* hotel, FILE* file, int x);


void writeHotel(Hotel_t* hotel, FILE* file, int x);


Hotel_t* hotelcpy(Hotel_t* dest, const Hotel_t* source);


void freeHotel(Hotel_t* hotel);





