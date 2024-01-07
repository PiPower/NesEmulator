#include "cpu.h"

TableEntry CPU::instructionTable[0x10][0x10] = {
/* 0 */	{ TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0},  TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0},  TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}},
/* 1 */	{ TableEntry{&CPU::BPL, &CPU::REL, 2}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0},  TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{&CPU::CLC, nullptr, 2}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0},  TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}},
/* 2 */	{ TableEntry{&CPU::JSR, &CPU::ABS, 6}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0},  TableEntry{nullptr, nullptr, 0}, TableEntry{&CPU::AND, &CPU::ZPG, 3}, TableEntry{&CPU::ROL, &CPU::ZPG, 5}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0},  TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}},
/* 3 */	{ TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0},  TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0},  TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}},
/* 4 */	{ TableEntry{&CPU::RTI, nullptr, 6}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0},  TableEntry{nullptr, nullptr, 0}, TableEntry{&CPU::EOR, &CPU::ZPG, 3}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{&CPU::PHA, nullptr, 3}, TableEntry{nullptr, nullptr, 0}, TableEntry{&CPU::LSRA, nullptr, 2}, TableEntry{nullptr, nullptr, 0},  TableEntry{&CPU::JMP, &CPU::ABS, 3}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}},
/* 5 */	{ TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0},  TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0},  TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}},
/* 6 */	{ TableEntry{&CPU::RTS, nullptr, 6}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0},  TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{&CPU::PLA, nullptr, 4}, TableEntry{&CPU::ADC, &CPU::IMM, 2}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0},  TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}},
/* 7 */	{ TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0},  TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{&CPU::SEI, nullptr, 2}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0},  TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}},
/* 8 */	{ TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0},  TableEntry{nullptr, nullptr, 0},  TableEntry{&CPU::STA, &CPU::ZPG, 3}, TableEntry{&CPU::STX, &CPU::ZPG, 3}, TableEntry{nullptr, nullptr, 0}, TableEntry{&CPU::DEY, nullptr, 2}, TableEntry{nullptr, nullptr, 0}, TableEntry{&CPU::TXA, nullptr, 2}, TableEntry{nullptr, nullptr, 0},  TableEntry{&CPU::STY, &CPU::ABS, 4}, TableEntry{&CPU::STA, &CPU::ABS, 4}, TableEntry{&CPU::STX, &CPU::ABS,4}, TableEntry{nullptr, nullptr, 0}},
/* 9 */	{ TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0},  TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{&CPU::TXS, nullptr, 2}, TableEntry{nullptr, nullptr, 0},  TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}},
/* A */	{ TableEntry{&CPU::LDY, &CPU::IMM, 2}, TableEntry{nullptr, nullptr, 0}, TableEntry{&CPU::LDX, &CPU::IMM, 2}, TableEntry{nullptr, nullptr, 0},  TableEntry{nullptr, nullptr, 0}, TableEntry{&CPU::LDA, &CPU::ZPG, 3}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{&CPU::TAY, nullptr,2}, TableEntry{&CPU::LDA, &CPU::IMM, 2}, TableEntry{&CPU::TAX, nullptr, 2}, TableEntry{nullptr, nullptr, 0},  TableEntry{&CPU::LDY, &CPU::ABS, 4}, TableEntry{&CPU::LDA, &CPU::ABS, 4}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}},
/* B */	{ TableEntry{&CPU::BCS,  &CPU::REL, 2}, TableEntry{&CPU::LDA, &CPU::IND_Y, 5}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0},  TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0},  TableEntry{nullptr, nullptr, 0}, TableEntry{&CPU::LDA, &CPU::X_IDX, 4}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}},
/* C */	{ TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0},  TableEntry{nullptr, nullptr, 0}, TableEntry{&CPU::CMP, &CPU::ZPG, 3}, TableEntry{&CPU::DEC, &CPU::ZPG, 5}, TableEntry{nullptr, nullptr, 0}, TableEntry{&CPU::INY, nullptr, 2}, TableEntry{&CPU::CMP, &CPU::IMM, 2}, TableEntry{&CPU::DEX, nullptr, 2}, TableEntry{nullptr, nullptr, 0},  TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}},
/* D */	{ TableEntry{&CPU::BNE, &CPU::REL, 2}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0},  TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{&CPU::CLD, nullptr, 2}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0},  TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}},
/* E */	{ TableEntry{&CPU::CPX, &CPU::IMM, 2}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0},  TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{&CPU::INC, &CPU::ZPG, 5}, TableEntry{nullptr, nullptr, 0}, TableEntry{&CPU::INX, nullptr, 2}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0},  TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}},
/* F */	{ TableEntry{&CPU::BEQ, &CPU::REL, 2}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0},  TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0},  TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}, TableEntry{nullptr, nullptr, 0}}
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

	uint8_t opcode = readByte(ip++);
	uint8_t highNibble= opcode >> 4;
	uint8_t lowNibble = opcode & 0x0F;
	TableEntry instructionEntry = this->instructionTable[highNibble][lowNibble];
	
	uint16_t loadedAddres;
	uint16_t* ptrAddr = nullptr;
	if (instructionEntry.memoryLoader != nullptr)
	{
		loadedAddres = (this->*(instructionEntry.memoryLoader))(nullptr);
		ptrAddr = &loadedAddres;
	}

	(this->*(instructionEntry.translator))(ptrAddr);
	status_reg.FLAGS.ignored = 1;
	cycles += instructionEntry.cycles;
	
}

void CPU::nonMaskableInterrupt()
{
	writeByte(0x0100 + stack_ptr, ip >> 8);
	stack_ptr--;
	writeByte(0x0100 + stack_ptr, ip & 0xFF);
	stack_ptr--;
	writeByte(0x0100 + stack_ptr, status_reg.flagByte);
	stack_ptr--;

	status_reg.FLAGS.interrupt = 1;

	uint16_t lo = readByte(0xFFFA);
	uint16_t hi = readByte(0xFFFB);

	ip = lo | hi << 8;

	cycles = 8;
}

void CPU::resetController()
{
	controllerState = 0;
}

void CPU::pressA(bool pressed)
{
	controllerState |= pressed ? 0x80 : 0x00;
}

void CPU::pressB(bool pressed)
{
	controllerState |= pressed ? 0x40 : 0x00;
}

void CPU::pressSelect(bool pressed)
{
	controllerState |= pressed ? 0x20 : 0x00;
}

void CPU::pressStart(bool pressed)
{
	controllerState |= pressed ? 0x10 : 0x00;
}

void CPU::pressUp(bool pressed)
{
	controllerState |= pressed ? 0x08 : 0x00;
}

void CPU::pressDown(bool pressed)
{
	controllerState |= pressed ? 0x04 : 0x00;
}

void CPU::pressLeft(bool pressed)
{
	controllerState |= pressed ? 0x02 : 0x00;
}

void CPU::pressRight(bool pressed)
{
	controllerState |= pressed ? 0x01 : 0x00;
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
			return ppu->readStatusRegister();
			break;
		default:
			exit(-1);
			break;
		}
	}
	else if (addr >= 0x4016 && addr <= 0x4017)
	{
		uint8_t data = (controllerLatch[addr - 0x4016] & 0x80 ) > 0;
		if (data != 0)
		{
			int x = 2;
		}
		controllerLatch[addr - 0x4016] <<= 1;
		return data;
	}
	else if (addr >= 0x8000 && addr <= 0xFFFF)
	{
		uint8_t byte = cartridge->readByteCPU(addr);
		return byte;
	}

}

void CPU::writeByte(uint16_t addr, uint8_t data)
{
	if (addr >= 0 && addr <= 0x1FFF)
	{
		addr = addr & 0x07FF;
		RAM[addr] = data;
	}
	else if (addr >= 0x2000 && addr <= 0x3FFF)
	{
		uint8_t registerAddr = addr & 0x0007;
		switch (registerAddr)
		{
		case 0 :
			ppu->writeControllRegister(data);
			break;
		case 1:
			ppu->writeMaskRegister(data);
			break;
		case 5:
			ppu->writeScrollRegister(data);
			break;
		case 6:
			ppu->writeAddrRegister(data);
			break;
		case 7:
			ppu->writeDataRegister(data);
			break;
		default:
			exit(-1);
			break;
		}
	}
	else if (addr >= 0x4016 && addr <= 0x4017)
	{
		controllerLatch[addr - 0x4016] = controllerState;
	}
	else if (addr >= 0x8000 && addr <= 0xFFFF)
	{
		exit(-1);
	}
}

uint16_t CPU::IMM(void* data)
{
	return ip++;
}

uint16_t CPU::ABS(void* data)
{
	uint16_t lo = readByte(ip++);
	uint16_t hi = readByte(ip++);
	uint16_t addr = lo | hi << 8;
	return addr;
}

uint16_t CPU::REL(void* data)
{
	
	return readByte(ip++);
}

uint16_t CPU::IND_Y(void* data)
{
	uint8_t page_offset = readByte(ip++);
	uint16_t lo = readByte(page_offset);
	uint16_t hi = readByte(page_offset + 1);
	uint16_t addr = lo | hi << 8;
	uint16_t effective_addr = addr + y_reg;
	if ((effective_addr & 0xFF00) != (hi << 8)) cycles++;
	return effective_addr;
}

uint16_t CPU::X_IDX(void* data)
{
	uint16_t lo = readByte(ip++);
	uint16_t hi = readByte(ip++);
	uint16_t addr = lo | hi << 8;
	addr += x_reg;
	if ((addr & 0xFF00) != (hi << 8)) cycles++;
	return addr;
}

uint16_t CPU::ZPG(void* data)
{
	uint16_t addr = 0;
	addr |= readByte(ip++);
	return addr;
}

void CPU::JSR(void* data)
{
	ip--;

	writeByte(0x0100 + stack_ptr, ip >> 8);
	stack_ptr--;
	writeByte(0x0100 + stack_ptr, ip );
	stack_ptr--;


	ip = *(uint16_t*)data;
}

void CPU::SEI(void* data)
{
	status_reg.FLAGS.interrupt = 1;
}

void CPU::CLD(void* data)
{
	status_reg.FLAGS.decimal = 0;
}

void CPU::CLC(void* data)
{
	status_reg.FLAGS.carry = 0;
}

void CPU::LDX(void* data)
{
	x_reg = readByte(*(uint16_t*)data);
	if(x_reg == 0 )   status_reg.FLAGS.zero = 1;
	else status_reg.FLAGS.zero = 0;
	if (x_reg & 0x80  ) status_reg.FLAGS.negative = 1;
	else status_reg.FLAGS.negative = 0;
}

void CPU::TXS(void* data)
{
	stack_ptr = x_reg;
}

void CPU::TXA(void* data)
{
	accumulator = x_reg;
	if (accumulator == 0)   status_reg.FLAGS.zero = 1;
	else status_reg.FLAGS.zero = 0;
	if (accumulator & 0x80) status_reg.FLAGS.negative = 1;
	else status_reg.FLAGS.negative = 0;
}

void CPU::TAX(void* data)
{
	x_reg = accumulator;
	if (x_reg == 0)   status_reg.FLAGS.zero = 1;
	else status_reg.FLAGS.zero = 0;
	if (x_reg & 0x80) status_reg.FLAGS.negative = 1;
	else status_reg.FLAGS.negative = 0;
}

void CPU::TAY(void* data)
{
	y_reg = accumulator;
	status_reg.FLAGS.zero = y_reg == 0 ? 1 : 0;
	status_reg.FLAGS.negative = (x_reg & 0x80) > 0? 1 : 0;
}

void CPU::LDA(void* data)
{
	accumulator = readByte(*(uint16_t*)data);
	if (accumulator == 0)   status_reg.FLAGS.zero = 1;
	else status_reg.FLAGS.zero = 0;
	if (accumulator & 0x80) status_reg.FLAGS.negative = 1;
	else status_reg.FLAGS.negative = 0;
}

void CPU::LDY(void* data)
{
	y_reg = readByte(*(uint16_t*)data);
	if (y_reg == 0)   status_reg.FLAGS.zero = 1;
	else status_reg.FLAGS.negative = 0;
	if (y_reg & 0x80) status_reg.FLAGS.negative = 1;
	else status_reg.FLAGS.negative = 0;
}

void CPU::BPL(void* data)
{
	char addr_rel = (*(uint16_t*)data) & 0x00FF;
	if (status_reg.FLAGS.negative == 0)
	{
		cycles++;
		uint16_t addr_abs =  ip + addr_rel;

		if ((addr_abs & 0xFF00) != (ip & 0xFF00)) // different pages
			cycles++;
		ip = addr_abs;
	}
}

void CPU::RTI(void* data)
{
	stack_ptr++;
	status_reg.flagByte = readByte(0x0100 + stack_ptr);
	stack_ptr++;
	uint16_t lo = readByte(0x0100 + stack_ptr);
	stack_ptr++;
	uint16_t hi = readByte(0x0100 + stack_ptr);
	ip = lo | hi << 8;
}

void CPU::STA(void* data)
{
	uint16_t* addr = (uint16_t * )data;
	writeByte(*addr, accumulator);
}

void CPU::STX(void* data)
{
	uint16_t* addr = (uint16_t*)data;
	writeByte(*addr, x_reg);
}

void CPU::STY(void* data)
{
	uint16_t* addr = (uint16_t*)data;
	writeByte(*addr, y_reg);
}

void CPU::DEX(void* data)
{
	x_reg--;
	if (x_reg == 0)   status_reg.FLAGS.zero = 1;
	else status_reg.FLAGS.zero = 0;
	if (x_reg & 0x80) status_reg.FLAGS.negative = 1;
	else status_reg.FLAGS.negative = 0;
}

void CPU::DEY(void* data)
{
	y_reg--;
	if (y_reg == 0)   status_reg.FLAGS.zero = 1;
	else status_reg.FLAGS.zero = 0;
	if (y_reg & 0x80) status_reg.FLAGS.negative = 1;
	else status_reg.FLAGS.negative = 0;
}

void CPU::DEC(void* data)
{
	uint8_t byte = readByte(*(uint16_t*)data);
	byte--;

	status_reg.FLAGS.zero = byte == 0 ? 1 : 0;
	status_reg.FLAGS.negative = (byte & 0x80) > 0 ? 1 : 0;
	writeByte(*(uint16_t*)data, byte);
}

void CPU::BNE(void* data)
{
	char addr_rel = (*(uint16_t*)data) & 0x00FF;
	if (status_reg.FLAGS.zero == 0)
	{
		cycles++;
		uint16_t addr_abs = ip + addr_rel;

		if ((addr_abs & 0xFF00) != (ip & 0xFF00)) // different pages
			cycles++;
		ip = addr_abs;
	}
}

void CPU::INX(void* data)
{
	x_reg++;
	if (x_reg == 0)   status_reg.FLAGS.zero = 1;
	else status_reg.FLAGS.zero = 0;
	if (x_reg & 0x80) status_reg.FLAGS.negative = 1;
	else status_reg.FLAGS.negative = 0;
}

void CPU::INY(void* data)
{
	y_reg++;
	if (y_reg == 0)   status_reg.FLAGS.zero = 1;
	else status_reg.FLAGS.zero = 0;
	if (y_reg & 0x80) status_reg.FLAGS.negative = 1;
	else status_reg.FLAGS.negative = 0;
}

void CPU::INC(void* data)
{
	uint8_t loadedData = readByte(*(uint16_t*)data) + 1;
	if (loadedData == 0)   status_reg.FLAGS.zero = 1;
	else status_reg.FLAGS.zero = 0;
	if (loadedData & 0x80) status_reg.FLAGS.negative = 1;
	else status_reg.FLAGS.negative = 0;
	writeByte(*(uint16_t*)data, loadedData);
}

void CPU::CPX(void* data)
{
	uint8_t result = x_reg - readByte(*(uint16_t*)data);
	if (x_reg >= readByte(*(uint16_t*)data))   status_reg.FLAGS.carry = 1;
	else status_reg.FLAGS.carry = 0;
	if (result == 0)   status_reg.FLAGS.zero = 1;
	else status_reg.FLAGS.zero = 0;
	if (result & 0x80) status_reg.FLAGS.negative = 1;
	else status_reg.FLAGS.negative = 0;
}

void CPU::CMP(void* data)
{
	uint8_t temp = readByte(*(uint16_t*)data);
	uint8_t result = accumulator - temp;
	if (accumulator >= result)   status_reg.FLAGS.carry = 1;
	else status_reg.FLAGS.carry = 0;
	if (result == 0)   status_reg.FLAGS.zero = 1;
	else status_reg.FLAGS.zero = 0;
	if (result & 0x80) status_reg.FLAGS.negative = 1;
	else status_reg.FLAGS.negative = 0;
}

void CPU::RTS(void* data)
{
	stack_ptr++;
	uint16_t lo = readByte(0x0100 + stack_ptr);
	stack_ptr++;
	uint16_t hi = readByte(0x0100 + stack_ptr);
	ip = lo | hi << 8;
	ip++;
}

void CPU::BEQ(void* data)
{
	char addr_rel = (*(uint16_t*)data) & 0x00FF;
	if (status_reg.FLAGS.zero == 1)
	{
		cycles++;
		uint16_t addr_abs = ip + addr_rel;

		if ((addr_abs & 0xFF00) != (ip & 0xFF00)) // different pages
			cycles++;
		ip = addr_abs;
	}
}

void CPU::PHA(void* data)
{
	writeByte(0x0100 + stack_ptr, accumulator);
	stack_ptr--;
}

void CPU::LSRA(void* data)
{
	if (accumulator & 0x01) status_reg.FLAGS.carry = 1;
	else status_reg.FLAGS.carry = 0;

	accumulator >>= 1;
	if (accumulator == 0)  status_reg.FLAGS.zero = 1;
	else status_reg.FLAGS.zero = 0;

	status_reg.FLAGS.negative = 0;

}

void CPU::ROLA(void* data)
{


	uint16_t temp = (uint16_t)(accumulator << 1) | status_reg.FLAGS.carry;
	if (temp & 0xFF00)  status_reg.FLAGS.carry = 1;
	else status_reg.FLAGS.carry = 0;
	if (temp == 0)  status_reg.FLAGS.zero = 1;
	else status_reg.FLAGS.zero = 0;
	if (temp & 0x0080) status_reg.FLAGS.negative = 1;
	else status_reg.FLAGS.negative = 0;

	accumulator = temp & 0x00FF;
}

void CPU::ROL(void* data)
{
	uint8_t byte = readByte(*(uint16_t*)data);

	uint16_t temp = (uint16_t)(byte <<1 ) | status_reg.FLAGS.carry;
	if (temp & 0xFF00)  status_reg.FLAGS.carry = 1;
	else status_reg.FLAGS.carry = 0;
	if (temp == 0)  status_reg.FLAGS.zero = 1;
	else status_reg.FLAGS.zero = 0;
	if (temp & 0x0080) status_reg.FLAGS.negative = 1;
	else status_reg.FLAGS.negative = 0;

	writeByte(*(uint16_t*)data, temp& 0x00FF);
}

void CPU::EOR(void* data)
{
	uint8_t byte = readByte(*(uint16_t*)data);
	accumulator = accumulator ^ byte;

	if (accumulator == 0)  status_reg.FLAGS.zero = 1;
	else status_reg.FLAGS.zero = 0;
	if (accumulator & 0x80) status_reg.FLAGS.negative = 1;
	else status_reg.FLAGS.negative = 0;
}

void CPU::AND(void* data)
{
	uint8_t byte = readByte(*(uint16_t*)data);
	accumulator = accumulator & byte;

	if (accumulator == 0)  status_reg.FLAGS.zero = 1;
	else status_reg.FLAGS.zero = 0;
	if (accumulator & 0x80) status_reg.FLAGS.negative = 1;
	else status_reg.FLAGS.negative = 0;
}

void CPU::ORA(void* data)
{
	uint8_t byte = readByte(*(uint16_t*)data);
	accumulator = accumulator | byte;

	if (accumulator == 0)  status_reg.FLAGS.zero = 1;
	else status_reg.FLAGS.zero = 0;
	if (accumulator & 0x80) status_reg.FLAGS.negative = 1;
	else status_reg.FLAGS.negative = 0;
}

void CPU::PLA(void* data)
{
	stack_ptr++;
	accumulator = readByte(0x0100 + stack_ptr);	

	if (accumulator == 0)  status_reg.FLAGS.zero = 1;
	else status_reg.FLAGS.zero = 0;
	if (accumulator & 0x80) status_reg.FLAGS.negative = 1;
	else status_reg.FLAGS.negative = 0;
}

void CPU::ADC(void* data)
{
	uint8_t byte = readByte(*(uint16_t*)data);
	uint16_t bufferCarry = accumulator + byte + status_reg.FLAGS.carry;
	status_reg.FLAGS.carry = bufferCarry > 255 ? 1 : 0;

	uint8_t buffer = bufferCarry & 0x00FF;
	bool overflow = ((~(accumulator ^ byte) & (accumulator ^ buffer)) & 0x80 ) > 0;

	status_reg.FLAGS.overflow = overflow ? 1 : 0;
	status_reg.FLAGS.zero = buffer == 0 ? 1 : 0;
	status_reg.FLAGS.negative = (buffer & 0x80) > 0 ? 1 : 0;

	accumulator = buffer;
}

void CPU::JMP(void* data)
{
	ip = *(uint16_t*)data;
}

void CPU::BCS(void* data)
{
	char addr_rel = (*(uint16_t*)data) & 0x00FF;
	if (status_reg.FLAGS.carry == 1)
	{
		cycles++;
		uint16_t addr_abs = ip + addr_rel;

		if ((addr_abs & 0xFF00) != (ip & 0xFF00)) // different pages
			cycles++;
		ip = addr_abs;
	}
}
