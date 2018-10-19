#include "EncodeAndDecode.h"
#include "Bits_Functions.h"

#define ONE_BYTE 0xFF


///////////////////////////////////////////////*** Encode *** Encode *** Encode ***//////////////////////////////////////////////////



/* the method take an unsigned char ponter and an int (X), and encode it */
/* Result: encoded byte */
/* Assumption : char is one byte*/
unsigned char encodeByte(unsigned char ch, int x)
{   //For Exmple:    ch = 001 |10| 000   , x = 3

	/*Level A: swap betwwen two bits in 'x' and 'x+1' places*/
	ch = swapBits(ch, x, (x + 1) % 8);

	/*Level B: XOR with 0xFF*/
	ch = ch ^ ONE_BYTE; // XOR with 11111111
						// In example:   currentCh   =  001 01 000
						// XOR on:       anotherTemp =  111 11 111
						// Result:       currentCh   =  110 10 111

						/*Level C: do right Circular Jumping */
	ch = rightCircularJumping(ch, x);

	return ch;
	// Result:     |111| 11010
}


/*Encoding function, which write to file the key for decoding (x) and the encoded 'variable'*/
/*return: int x, which is the key for decoding*/
/*Assumptions: the file is already exist,
the file is a binary one,
the file ready to write. */
void encodeStruct(void* variable, int NumOfBytes, int x)
{
	unsigned char* str = (unsigned char*)variable;  // casting 'variable' to array of 'unsigned char'
													// str can be named to location OR cast
	int i;
	for (i = 0; i < NumOfBytes; i++)
	{
		str[i] = encodeByte(str[i], x);
	}// loop end
}



///////////////////////////////////////////////*** Decode *** Decode *** Decode ***//////////////////////////////////////////////////




/*Decoding a whole byte ('chPointer' is his pointer)*/
/* x must be between 0 to 7*/
unsigned char decodeByte(unsigned char ch, int x)
{  //For Exmple:    ch = | 111 | 11010   , x = 3
   // In encode proccess, we did circular-jumping of 'x' places to the right (for e.m: x=3)
   // we need only to do circular-jumping of '8-x' places (e.m: 5) to gain the same variable befor level_C(x)

   /*Level C: do right Circular Jumping */
	ch = rightCircularJumping(ch, 8 - x);

	/*Level B: XOR with 0xFF*/
	ch = ch ^ ONE_BYTE;

	/*Level A: swap betwwen two bits in 'x' and 'x+1' places*/
	ch = swapBits(ch, x, (x + 1) % 8);

	return ch;
	// Final Result:    0011 | 0000
	// end of decoding one byte
}


/*Decoding a whole struct (that should not contain pointers)*/
/* x must be between 0 to 7*/
void decodeStruct(void* variable, int NumOfBytes, int x)
{
	unsigned char* str = (unsigned char*)variable;  // casting 'variable' to array of 'unsigned char'

	int i;
	for (i = 0; i < NumOfBytes; i++)
	{
		str[i] = decodeByte(str[i], x);
	}// loop end

}
