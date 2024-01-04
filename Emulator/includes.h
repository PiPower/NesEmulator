#pragma once
#include "inttypes.h"

typedef unsigned char byte;
struct FlagBits
{
	byte carry : 1;
	byte zero : 1;
	byte interrupt : 1;
	byte decimal : 1;
	byte break_bit : 1;
	byte ignored : 1;
	byte overflow : 1;
	byte negative : 1;
};

union FLAGS
{
	FlagBits FLAGS;
	byte flagByte;
};


class CPU;
struct TableEntry
{
	// translates given instruction
	void (CPU::* translator)(void* data);
	//translates given addres to required one by instruction
	uint16_t (CPU::* memoryLoader)(void* data);
	uint8_t cycles;
};

extern TableEntry instructionTable[0x0F][0x0F];