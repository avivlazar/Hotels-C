#pragma once
#include "Bits_Functions.h"


unsigned char encodeByte(unsigned char ch, int x);


void encodeStruct(void* variable, int NumOfBytes, int x);


unsigned char decodeByte(unsigned char ch, int x);


void decodeStruct(void* variable, int NumOfBytes, int x);



