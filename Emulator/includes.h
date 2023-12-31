#pragma once
#include "inttypes.h"

typedef unsigned char bit; 
struct FlagBits
{
	bit carry : 1;
	bit zero : 1;
	bit interrupt : 1;
	bit decimal : 1;
	bit break_bit : 1;
	bit ignored : 1;
	bit overflow : 1;
	bit negative : 1;
};

union FLAGS
{
	FlagBits FLAGS;
	unsigned  char flagByte;
};

class CPU;
struct TableEntry
{
	// translates given instruction
	void (CPU::* translator)(void* data);
	//translates given addres to required one by instruction
	uint16_t (CPU::* mapper)(void* data);
};

extern TableEntry instructionTable[0x0F][0x0F];