#include "cpu.h"

TableEntry CPU::instructionTable[0x0F][0x0F] = {

/* 0 */	{ TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0},  TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0},  TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}},
/* 1 */	{ TableEntry{&CPU::BPL, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0},  TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0},  TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}},
/* 2 */	{ TableEntry{nullptr, nullptr, 6}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0},  TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0},  TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}},
/* 3 */	{ TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0},  TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0},  TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}},
/* 4 */	{ TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0},  TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0},  TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}},
/* 5 */	{ TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0},  TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0},  TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}},
/* 6 */	{ TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0},  TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0},  TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}},
/* 7 */	{ TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0},  TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{&CPU::SEI, nullptr, 2}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0},  TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}},
/* 8 */	{ TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0},  TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0},  TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}},
/* 9 */	{ TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0},  TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{&CPU::TXS, nullptr, 2}, TableEntry{nullptr, nullptr, 0},  TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}},
/* A */	{ TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{&CPU::LDX, &CPU::IMM, 2}, TableEntry{nullptr, nullptr, 0},  TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0},  TableEntry{&CPU::LDY, &CPU::ABS, 4}, TableEntry{&CPU::LDA, &CPU::ABS, 4}, TableEntry{nullptr, nullptr, 0}},
/* B */	{ TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0},  TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0},  TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}},
/* C */	{ TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0},  TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0},  TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}},
/* D */	{ TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0},  TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{&CPU::CLD, nullptr, 2}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0},  TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}},
/* F */	{ TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0},  TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0},  TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}},
};


CPU::CPU(NesFile* file, PPU* ppu)
	:
	ppu(ppu)
{
	cartridge = file;

	RAM = new uint8_t[0x07FF];
	reset();
}

void CPU::reset()
{
	ip = 0xFFFC;
	uint16_t lo = readByte(ip);
	uint16_t hi = readByte(++ip);

	ip = lo | hi << 8;
	stack_ptr = 0xFD;

	accumulator = 0;
	x_reg = 0;
	y_reg = 0;
	status_reg.flagByte = 0;
	cycles = 8;
}

void CPU::clock()
{
	if(cycles > 0 )
	{ 
		cycles--;
		return;
	}

	uint8_t instruction_code = readByte(ip++);
	uint8_t highNibble= instruction_code >> 4;
	uint8_t lowNibble = instruction_code & 0x0F;
	TableEntry instructionEntry = this->instructionTable[highNibble][lowNibble];

	uint8_t loadedByte;
	uint8_t* loaded_addr = nullptr;
	if (instructionEntry.memoryLoader != nullptr)
	{
		loadedByte = (this->*(instructionEntry.memoryLoader))(nullptr);
		loaded_addr = &loadedByte;
	}

	(this->*(instructionEntry.translator))(loaded_addr);
	status_reg.FLAGS.ignored = 1;
	cycles += instructionEntry.cycles;
	
}

uint8_t CPU::readByte(uint16_t addr)
{
	if (addr >= 0 && addr <= 0x1FFF)
	{
		return RAM[addr & 0x07FF]; //looping adress 
	}
	else if (addr >= 0x2000 && addr <= 0x3FFF)
	{
		// PPU Address range, mirrored every 8
		uint8_t registerAddr = addr & 0x0007;
		switch (registerAddr)
		{
		case 0x02:
			return ppu->readStatus();
		}
	}
	else if (addr >= 0x8000 && addr <= 0xFFFF)
	{
		uint8_t byte = cartridge->readByte(addr);
		return byte;
	}

}

uint8_t CPU::IMM(void* data)
{
	return readByte(ip++);
}

uint8_t CPU::ABS(void* data)
{
	uint16_t lo = readByte(ip++);
	uint16_t hi = readByte(ip++);
	uint16_t addr = lo | hi << 8;
	return readByte(addr);
}

void CPU::JSR(void* data)
{
	uint8_t lo = 255;
	uint8_t hi = 255;
	exit(-1);
	uint16_t  addr_abs = (hi << 8) | lo;
}

void CPU::SEI(void* data)
{
	status_reg.FLAGS.interrupt = 1;
}

void CPU::CLD(void* data)
{
	status_reg.FLAGS.decimal = 0;
}

void CPU::LDX(void* data)
{
	x_reg = *(uint8_t*)data;
	if(x_reg == 0 )   status_reg.FLAGS.zero = 1;
	else status_reg.FLAGS.zero = 0;
	if (x_reg & 0x80  ) status_reg.FLAGS.negative = 1;
	else status_reg.FLAGS.negative = 0;
}

void CPU::TXS(void* data)
{
	stack_ptr = x_reg;
}

void CPU::LDA(void* data)
{
	accumulator = *(uint8_t*)data;
	if (accumulator == 0)   status_reg.FLAGS.zero = 1;
	else status_reg.FLAGS.zero = 0;
	if (accumulator & 0x80) status_reg.FLAGS.negative = 1;
	else status_reg.FLAGS.negative = 0;
}

void CPU::LDY(void* data)
{
	y_reg = *(uint8_t*)data;
	if (y_reg == 0)   status_reg.FLAGS.zero = 1;
	else status_reg.FLAGS.negative = 0;
	if (y_reg & 0x80) status_reg.FLAGS.negative = 1;
	else status_reg.FLAGS.negative = 0;
}

void CPU::BPL(void* data)
{
	char addr_rel = readByte(ip++);
	if (status_reg.FLAGS.negative == 0)
	{
		cycles++;
		uint16_t addr_abs =  ip + addr_rel;

		if ((addr_abs & 0xFF00) != (ip & 0xFF00)) // different pages
			cycles++;
		ip = addr_abs;
	}
}
