#pragma once

#ifndef ROOM_H
#define ROOM_H



typedef struct {
	int numOfBeds;  // value: > 0
	unsigned char roomChars;  // room' characteristics (value: 0 - 127)
}Room_t;


void printRoom(Room_t* roomPointer);


void createRoomByRandom(Room_t* roomPointer);


int isRoomHasPro(Room_t* roomPointer, int roomBooleanType);


int printRoomsWithPropertyByVariadicFunction(int roomBooleanType, ...);



#endif // ROOM_H
