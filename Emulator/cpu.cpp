#include "cpu.h"

TableEntry CPU::instructionTable[0x0F][0x0F] = {
	{ TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr},  TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr} },
	{ TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr},  TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr} },
	{ TableEntry{&CPU::jumpToNewLocationSavingReturnAddress, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr},  TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr} },
	{ TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr},  TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr} },
	{ TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr},  TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr} },
	{ TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr},  TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr} },
	{ TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr},  TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr} },
	{ TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr},  TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr} },
};

CPU::CPU(NesFile* file)
{
	RAM = new uint8_t[0x07FF];
	cartridge = file;
	ip = 0;
}

void CPU::clock()
{
	uint8_t instruction_code = fetchByte();
	uint8_t highNibble= instruction_code >> 4;
	uint8_t lowNibble = instruction_code & 0b00001111;
	TableEntry currentInstruction = this->instructionTable[highNibble][lowNibble];

	if (currentInstruction.mapper == nullptr)
	{
		(this->*(currentInstruction.translator))(nullptr);
	}
}

uint8_t CPU::fetchByte()
{
	uint8_t byte = *cartridge->PGR_ROM;
	cartridge->PGR_ROM++;
	return byte;
}

void CPU::jumpToNewLocationSavingReturnAddress(void*)
{
}
