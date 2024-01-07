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
	//joystick constroll
	void resetController();
	void pressA(bool pressed);
	void pressB(bool pressed);
	void pressSelect(bool pressed);
	void pressStart(bool pressed);
	void pressUp(bool pressed);
	void pressDown(bool pressed);
	void pressLeft(bool pressed);
	void pressRight(bool pressed);
private:
	uint8_t readByte(uint16_t addr);
	void writeByte(uint16_t addr, uint8_t data);
private:
	// memory loading
	uint16_t IMM(void* data);
	uint16_t ABS(void* data);
	uint16_t REL(void* data);
	uint16_t IND(void* data);
	uint16_t IND_Y(void* data);
	uint16_t X_IDX(void* data);
	uint16_t ZPG(void* data);
	// instruction types
	void JSR(void* data);
	void SEI(void* data);
	void SEC(void* data);
	void SED(void* data);
	void CLD(void* data);
	void CLC(void* data);
	void LDX(void* data);
	void TXS(void* data);
	void TXA(void* data);
	void TAX(void* data);
	void TAY(void* data);
	void LDA(void* data);
	void LDY(void* data);
	void BPL(void* data);
	void RTI(void* data);
	void STA(void* data);
	void STX(void* data);
	void STY(void* data);
	void DEX(void* data);
	void DEY(void* data);
	void DEC(void* data);
	void BNE(void* data);
	void INX(void* data);
	void INY(void* data);
	void INC(void* data);
	void CPX(void* data);
	void CMP(void* data);
	void RTS(void* data);
	void BEQ(void* data);
	void BCC(void* data);
	void BVS(void* data);
	void BVC(void* data);
	void BMI(void* data);
	void PHA(void* data);
	void PHP(void* data);
	void LSRA(void* data);
	void ROLA(void* data);
	void ROL(void* data);
	void EOR(void* data);
	void AND(void* data);
	void ORA(void* data);
	void PLA(void* data);
	void PLP(void* data);
	void ADC(void* data);
	void JMP(void* data);
	void BCS(void* data);
	void ASLA(void* data);
	void NOP(void* data);
	void BIT(void* data);
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
	uint8_t controllerLatch[2];
	uint8_t controllerState;
};

