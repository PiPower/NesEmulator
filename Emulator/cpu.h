#pragma once
#include "includes.h"
#include "../NesFile.h"

class CPU
{
public:
	CPU(NesFile* file);
	void clock();
private:
	uint8_t readByte(uint16_t addr);
private:
	void JSR(void* data);
	void SEI(void* data);
private:
	// registers
	uint16_t ip;
	char accumulator;
	char x_reg;
	char y_reg;
	char status_reg;
	uint16_t stack_ptr;
	FLAGS flags_reg;
	// device 
	uint8_t* RAM;
	NesFile* cartridge;
	static TableEntry instructionTable[0x0F][0x0F];
};

