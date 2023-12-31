#pragma once
#include "includes.h"
#include "../NesFile.h"

class CPU
{
public:
	CPU(NesFile* file);
	void clock();
private:
	uint8_t fetchByte();
private:
	// registers
	uint16_t ip;
	char accumulator;
	char x_reg;
	char y_reg;
	char status_reg;
	char* stack_ptr;
	FLAGS flags_reg;
	// device 
	uint8_t* RAM;
	NesFile* cartridge;
};

