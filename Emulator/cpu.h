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
	uint16_t REL(void* data);
	uint16_t IND_Y(void* data);
	uint16_t X_IDX(void* data);
	uint16_t ZPG(void* data);
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
	void STA(void* data);
	void STX(void* data);
	void STY(void* data);
	void DEX(void* data);
	void DEY(void* data);
	void BNE(void* data);
	void INX(void* data);
	void CPX(void* data);
	void RTS(void* data);
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
	static TableEntry instructionTable[0x10][0x10];
	uint16_t cycles;
	PPU* ppu;
};

