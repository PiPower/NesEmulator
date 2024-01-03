#pragma once
#include "includes.h"
#include "ppu.h"
#include "../NesFile.h"

class CPU
{
public:
	CPU(NesFile* file, PPU* ppu);
	void reset();
	void clock();
	void nonMaskableInterrupt();
private:
	uint8_t readByte(uint16_t addr);
	void writeByte(uint16_t addr, uint8_t data);
private:
	// memory loading
	uint16_t IMM(void* data);
	uint16_t ABS(void* data);
	// instruction types
	void JSR(void* data);
	void SEI(void* data);
	void CLD(void* data);
	void LDX(void* data);
	void TXS(void* data);
	void LDA(void* data);
	void LDY(void* data);
	void BPL(void* data);
	void RTI(void* data);
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
	PPU* ppu;
};

