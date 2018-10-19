#include <stdio.h>
#include "Bits_Functions.h"




/*Set the bit in 'ch' at the index 'index' from right (should be 0 - 7 ( '7 < index' will set result to zero)) */
/* the 'value' have to be 0 or 1 */
unsigned char setBitFromRight(unsigned char ch, int index, int value)
{
	unsigned char mask = 1; // 00000001
	unsigned char result;
	mask <<= index;
	if (value == 1)
		result = ch | mask;
	else
	{
		mask = ~mask;
		result = ch & mask;
	}
	return result;
}


/* Get the bit in 'ch' at the index 'index' from right*/
/* return: 0 or 1 (binary value)*/
int getBitFromRight(unsigned char ch, int index)
{
	unsigned char mask = 1; // 00000001
	mask = mask << index;
	if ((ch & mask) == 0)
		return 0;
	else
		return 1;
}


/*This function receives higher and lower bounds of bit indexes,
and creates a mask with 1 in this range, and 0 in all other places.
I.E: high=5, low=3, the mask char would be: 00111000
Assamptions: high bigger than low
high btween 1 to 7, and low between 0 to 6
*/
unsigned char createMask(int high, int low)
{
	return (1 << (high + 1)) - (1 << low);
}



/*Swap between two bits in one byte*/
/*Assamptons: place1 and place2 between 0 to 7*/
unsigned char swapBits(unsigned char ch, int place1, int place2)
{
	unsigned char temp;
	temp = 0;  // 00000000, will help us to do encoding
	int bit1 = getBitFromRight(ch, place1);  // get the bit in 'place1' 
	int bit2 = getBitFromRight(ch, place2);  // get the bit in 'place2'
	if (bit1 != bit2)
	{
		// if the bits in index 'place1' and index ''place2' are diffrent, do this specific swap: 
		//(in our example, we do it)
		temp = setBitFromRight(temp, place1, 1);  // In example: temp = 000 |01| 000
		temp = setBitFromRight(temp, place2, 1);  // In Example: temp = 000 |11| 000
		ch ^= temp;  // XOR method 
					 // In example:   ch   = 001 |10| 000
					 // XOR on:       temp = 000 |11| 000
					 // Result:       ch   = 001 |01| 000

	}
	else;  // else, do nothing. there bits are already the same.

	return ch;
}


/*The method do circular movment of 'x' jumps to the right (of one byte)
Assamptions: x is between 0 to 8*/
unsigned char rightCircularJumping(unsigned char ch, int x)
{
	unsigned char temp = 0;

	temp = createMask(x - 1, 0);  // In Example : (x=3) --> (c = 0000 | 0111)
	temp &= ch;  // In Example : (1101|0111) AND (0000|0111) = (0000|0111)
	temp <<= (8 - x);  // shift left: c = (1110|0000)
	ch >>= x;  // Shift right: currentCh = (0001|1010)
	return (ch | temp);  // OR: (1110|0000), (0001|1010) --> (1111|1010)
						 // Final Result:    1111 | 1010

}


/* Print a byte as same as the computer see (in ascii) */
/* Exemple: 'a' (ascii value: 97) --> Print '01100001'*/
void printCharAsBinary(char ch)
{
	int i;
	unsigned char temp;
	for (i = 0; i < 8; i++)
	{
		temp = ch << i;
		temp = temp >> 7;
		printf("%d", temp);
	}
}
