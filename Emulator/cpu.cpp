#include "cpu.h"

CPU::CPU(NesFile* file)
{
	RAM = new uint8_t[0x07FF];
	cartridge = file;
}

void CPU::clock()
{
	uint8_t instruction_code = fetchByte();
	TableEntry currentInstruction = instructionTable[3][4];
	int x = 2;
}

uint8_t CPU::fetchByte()
{
	uint8_t byte = *cartridge->PGR_ROM;
	cartridge->PGR_ROM++;
	return byte;
}
