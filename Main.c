// Aviv Lazar 311514236
#pragma warning(disable: 4996)

#include <time.h>  // for 'time'
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include "Hotel.h"
#include "Bits_Functions.h"
#include "EncodeAndDecode.h"
#include "BooleanTypes.h"

const char* xFileName = "decodePar.txt";
const char* hotelFileName_DEFAULT = "myHotel.bin";

void main(int argc, char *argv[])
{

	srand((unsigned int)time(NULL));  // initialize random seed

									  //argc = 1;

	int x;
	Hotel_t* hotel = (Hotel_t*)malloc(sizeof(Hotel_t));
	FILE* Hotel_File = NULL;  // the file of hotel
	FILE* X_File = NULL;
	// reading the hotel



	if (argc == 2)
	{   // read file and encode the hotel
		// reading x parameter
		X_File = fopen(xFileName, "r");
		if (!X_File)
		{
			printf("\nError on opening file\n");
			return;
		}
		else
		{
			fscanf(X_File, "%d", &x);
			Hotel_File = fopen(argv[1], "rb");
			if (!Hotel_File)
			{
				printf("\nError on opening reading hotel\n");
				return;
			}
			else
			{
				readHotel(hotel, Hotel_File, x);
				fclose(Hotel_File);
			}
		}
		fclose(X_File);
	}
	else
	{   // create a new hotel
		x = rand() % 8;  // random value: 0 - 7
						 // 2a: read hotel from user
		readHotelFromUser(hotel);
	}
	// end of reading/creating hotel

	//Function 3 (not part from the menu) for check the method if you want:
	/*
	{
	printf("\nPlease choose one of the following options");
	int result, choise, i;
	for (i = 0; i < SIZE_ARRAY; i++)
	{   // print all options:
	printf("\n\n%d ---> %s", i + 1, names[i]);
	}
	do
	{   // get choise from user
	printf("\nYour choise (must be one of the follwing numbers): ");
	scanf("%d", &choise);
	} while (choise < 1 || choise > SIZE_ARRAY);
	if (hotel->roomsEachFloor >= 3)
	{   // first floor
	printf("\nThe rooms with %s are:", names[choise - 1]);
	result = printRoomsWithPropertyByVariadicFunction(choise - 1, hotel->roomsMatrix[0] + 0, hotel->roomsMatrix[0] + 1, hotel->roomsMatrix[0] + 2, NULL);
	if (result == 0)
	{
	printf("\nThere are no rooms from the first-three with %s", names[choise - 1]);
	}
	}
	else
	{   // if there isn't three rooms minimum in one floor:
	printf("\nThere are not enough rooms in one floor for this function");
	}
	}
	*/
	// end Function 3

	// The menu:
	int isExit = 0;
	int userChoise;
	do
	{
		printf("\n\n\n0 ---> Exit");
		printf("\n1 ---> Print Hotel Status");
		printf("\n2 ---> Print all romms in hotel which is not occuppied and have unique property");
		printf("\nPlease enter your choise: ");
		scanf("%d", &userChoise);
		switch (userChoise)
		{

		case 1:
		{
			// 2b: printing the status of the hotel
			printHotel(hotel);
			break;
		}

		case 2:
		{
			int i;
			int choise;
			printf("\n\nPlease enter one of the flowing properties:");
			for (i = 0; i < SIZE_ARRAY; i++)
			{   // print all options:
				printf("\n%d ---> %s", i + 1, names[i]);
			}
			do
			{   // get choise from user
				printf("\nYour choise (must be one of the follwing numbers): ");
				scanf("%d", &choise);
			} while (choise < 1 || choise > SIZE_ARRAY);
			printf("\nAll the rooms which has  %s and NOT OCCUPIED are:\n", names[choise - 1]);
			printAllRoomsInHotelWithProAndNotOccuppied(hotel, choise - 1);
			break;
		}

		case 0:
		{
			isExit = 1;
			break;
		}
		default:
		{
			printf("\n\nThis is wrong input");
			break;
		}

		}  // end of switch
	} while (isExit == 0);


	// exit proccess:

	// open for writing
	if (argc == 2)
	{
		Hotel_File = fopen(argv[1], "wb");
	}
	else
	{
		Hotel_File = fopen(hotelFileName_DEFAULT, "wb");
	}

	X_File = fopen(xFileName, "w");

	// writing hotel to Hotel_File (with encoding)
	writeHotel(hotel, Hotel_File, x);
	fprintf(X_File, "%d", x);

	// closing
	fclose(Hotel_File);
	fclose(X_File);
	printf("\nGoodBye");
	freeHotel(hotel);


}
