#pragma once
#include "inttypes.h"
#include "includes.h"
#include 
class CPU
{
public:
	CPU();

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
	char* RAM;
};

