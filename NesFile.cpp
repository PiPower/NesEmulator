#include "NesFile.h"
#include <fstream>
#include <Windows.h>
#include <iostream>
using namespace std;
NesFile::NesFile(char* filePath)
{
	fstream file(filePath, ios::in | ios::binary);
	if (!file.good())
	{
		MessageBox(NULL, L"given file path does not exist", NULL, MB_OK);
		exit(-1);
	}
	char id[4];
	int signature = 0x1A53454E;
	file.read((char*)id, 4);
	if (memcmp(id, &signature, 2)!= 0)
	{
		MessageBox(NULL, L"incorrect file type", NULL, MB_OK);
		exit(-1);
	}
	file.read((char*)&PGR_ROM_size, 1);
	file.read((char*)&CHR_ROM_size, 1);
	file.read(&Flags6, 1);
	file.read(&Flags7, 1);
	file.read(&Flags8, 1);
	file.read(&Flags9, 1);
	file.read(&Flags10, 1);
	file.seekp(file.cur + 5);
	char xd = GetMirroring();
	Mapper = (Flags6 >> 4 )|(Flags7 & 0b11110000);
	if (this->GetTrainer() > 0)
	{
		Trainer = new char[512];
		file.read(Trainer, 512);
	}

	PGR_ROM = new char[16384 * PGR_ROM_size];
	file.read(PGR_ROM, 16384 * PGR_ROM_size);

	CHR_ROM = new char[8192 * CHR_ROM_size];
	file.read(CHR_ROM, 8192 * CHR_ROM_size);

}

NesFile::NesFile(std::string filePath)
{
	NesFile(filePath.c_str());
}

char NesFile::GetMirroring()
{
	return Flags6 & 0x01;
}

char NesFile::GetBatteryBacked()
{
	return Flags6>>1 & 0x01;
}

char NesFile::GetTrainer()
{
	return Flags6 >> 2 & 0x01;
}

char NesFile::GetIgnore()
{
	return Flags6 >> 3 & 0x01;
}
