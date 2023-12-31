#include "cpu.h"

TableEntry CPU::instructionTable[0x0F][0x0F] = {
	{ TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr},  TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr},  TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}},
	{ TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr},  TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr},  TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}},
	{ TableEntry{&CPU::JSR, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr},  TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr},  TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}},
	{ TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr},  TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr},  TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}},
	{ TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr},  TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr},  TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}},
	{ TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr},  TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr},  TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}},
	{ TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr},  TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr},  TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}},
	{ TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr},  TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{&CPU::SEI, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr},  TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}},
	{ TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr},  TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr},  TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}},
	{ TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr},  TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr},  TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}},
	{ TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr},  TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr},  TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}},
	{ TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr},  TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr},  TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}},
	{ TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr},  TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr},  TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}},
	{ TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr},  TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr},  TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}},
	{ TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr},  TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr},  TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}, TableEntry{nullptr, nullptr}},
};

CPU::CPU(NesFile* file)
{
	cartridge = file;

	RAM = new uint8_t[0x07FF];
	ip = 0xFFFC;

	readByte(0x8000);
	uint16_t lo = readByte(ip);
	uint16_t hi = readByte(++ip);

	ip = lo | hi << 8;
	stack_ptr = 0xFD;

	accumulator = 0;
	x_reg = 0;
	y_reg = 0;
	flags_reg.flagByte = 0;
}

void CPU::clock()
{
	uint8_t instruction_code = readByte(ip);
	uint8_t highNibble= instruction_code >> 4;
	uint8_t lowNibble = instruction_code & 0b00001111;
	TableEntry currentInstruction = this->instructionTable[highNibble][lowNibble];

	if (currentInstruction.mapper == nullptr)
	{
		(this->*(currentInstruction.translator))(nullptr);
	}
}

uint8_t CPU::readByte(uint16_t addr)
{
	if (addr >= 0x8000 && addr <= 0xFFFF)
	{
		uint8_t byte = cartridge->readByte(addr);
		return byte;
	}
}

void CPU::JSR(void* data)
{
	uint8_t lo = 255;
	uint8_t hi = 255;
	uint16_t  addr_abs = (hi << 8) | lo;
}

void CPU::SEI(void* data)
{
	flags_reg.FLAGS.interrupt = 1;
}
