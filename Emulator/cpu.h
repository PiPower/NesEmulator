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
	// memory loading
	uint8_t IMM(void* data);
	uint8_t ABS(void* data);
	// instruction types
	void JSR(void* data);
	void SEI(void* data);
	void CLD(void* data);
	void LDX(void* data);
	void TXS(void* data);
	void LDA(void* data);
	void LDY(void* data);
private:
	// registers
	uint16_t ip;
	uint8_t accumulator;
	uint8_t x_reg;
	uint8_t y_reg;
	uint8_t stack_ptr;
	FLAGS status_reg;
	// device 
	uint8_t* RAM;
	NesFile* cartridge;
	static TableEntry instructionTable[0x0F][0x0F];
	uint16_t cycles;
};

