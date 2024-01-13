#include "NesFile.h"
#include <fstream>
#include <Windows.h>
#include <iostream>
using namespace std;

NesFile::NesFile(std::string path)
	:nCHRBankSelect(0)
{
	fstream file(path.c_str(), ios::in | ios::binary);
	if (!file.good())
	{
		MessageBox(NULL, L"given file path does not exist", NULL, MB_OK);
		exit(-1);
	}

	char id[4];
	int signature = 0x1A53454E;
	file.read((char*)id, 4);
	if (memcmp(id, &signature, 2) != 0)
	{
		MessageBox(NULL, L"incorrect file type", NULL, MB_OK);
		exit(-1);
	}

	file.read((char*)&PGR_ROM_size, 1);
	file.read((char*)&CHR_ROM_size, 1);
	file.read(&(Flags6), 1);
	file.read(&Flags7, 1);
	file.read(&Flags8, 1);
	file.read(&Flags9, 1);
	file.read(&Flags10, 1);
	file.seekp(5, ios_base::cur);

	Trainer = nullptr;
	if ((Flags6 >> 2) & 0x01 > 0)
	{
		Trainer = new char[512];
		file.read(Trainer, 512);
	}

	PGR_ROM = new uint8_t[16384 * PGR_ROM_size];
	file.read((char*)PGR_ROM, 16384 * PGR_ROM_size);

	CHR_ROM = new uint8_t[8192 * CHR_ROM_size];
	file.read((char*)CHR_ROM, 8192 * CHR_ROM_size);


	switch ( (Flags7 & 0xF0)  | ((Flags6 & 0xF0) >> 4 ) )
	{
	case 0:
		ptrReadByteCPU = &NesFile::readMirrorCPU000;
		ptrReadBytePPU = &NesFile::readMirrorPPU000;
		ptrWriteByteCPU = &NesFile::writeByteMirrorCPU000;
		ptrWriteBytePPU = &NesFile::writeByteMirrorPPU000;
	case 3:
		ptrReadByteCPU = &NesFile::readMirrorCPU003;
		ptrReadBytePPU = &NesFile::readMirrorPPU003;
		ptrWriteByteCPU = &NesFile::writeByteMirrorCPU003;
		ptrWriteBytePPU = &NesFile::writeByteMirrorPPU003;
		break;
	default:
		exit(-1);
	}
}

uint8_t NesFile::getNametableMirroring()
{
	return Flags6 & 0x01;
}

uint8_t NesFile::readByteCPU(uint16_t addr)
{
	return (this->*ptrReadByteCPU)(addr);
}

void NesFile::writeByteCPU(uint16_t addr, uint8_t data)
{
	(this->*ptrWriteByteCPU)(addr, data);
}

uint8_t NesFile::readBytePPU(uint16_t addr)
{
	return (this->*ptrReadBytePPU)(addr);
}

void NesFile::writeBytePPU(uint16_t addr, uint8_t data)
{
	(this->*ptrWriteBytePPU)(addr, data);
}

uint16_t NesFile::readMirrorCPU000(uint16_t addr)
{
	uint16_t trasnlated_addr = addr& (PGR_ROM_size > 1 ? 0x7FFF : 0x3FFF);
	return PGR_ROM[trasnlated_addr];
}

uint16_t NesFile::readMirrorPPU000(uint16_t addr)
{
	return CHR_ROM[addr];
}

void NesFile::writeByteMirrorCPU000(uint16_t addr, uint8_t data)
{
	uint16_t trasnlated_addr = addr & (PGR_ROM_size > 1 ? 0x7FFF : 0x3FFF);
	PGR_ROM[trasnlated_addr] = data;
}

void NesFile::writeByteMirrorPPU000(uint16_t addr, uint8_t data)
{
	CHR_ROM[addr] = data;
}

uint16_t NesFile::readMirrorCPU003(uint16_t addr)
{
	uint16_t trasnlated_addr = addr & (PGR_ROM_size > 1 ? 0x7FFF : 0x3FFF);
	return PGR_ROM[trasnlated_addr];
}

uint16_t NesFile::readMirrorPPU003(uint16_t addr)
{
	uint16_t mapped_addr = nCHRBankSelect * 0x2000 + addr;
	return CHR_ROM[mapped_addr];
}

void NesFile::writeByteMirrorCPU003(uint16_t addr, uint8_t data)
{
	nCHRBankSelect = data & 0x03; 
}

void NesFile::writeByteMirrorPPU003(uint16_t addr, uint8_t data)
{
}


