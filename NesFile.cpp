#include "NesFile.h"
#include <fstream>
#include <Windows.h>
#include <iostream>
using namespace std;
NesFile* readNESFile(std::string path)
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
	if (memcmp(id, &signature, 2)!= 0)
	{
		MessageBox(NULL, L"incorrect file type", NULL, MB_OK);
		exit(-1);
	}

	NesFile* cartridge = new NesFile();
	file.read((char*)&cartridge->PGR_ROM_size, 1);
	file.read((char*)&cartridge->CHR_ROM_size, 1);
	file.read(&cartridge->Flags6, 1);
	file.read(&cartridge->Flags7, 1);
	file.read(&cartridge->Flags8, 1);
	file.read(&cartridge->Flags9, 1);
	file.read(&cartridge->Flags10, 1);
	file.seekp(5, ios_base::cur);

	cartridge->Trainer = nullptr;
	if (cartridge->Flags6 & 0x01 > 0)
	{
		cartridge->Trainer = new char[512];
		file.read(cartridge->Trainer, 512);
	}

	cartridge->PGR_ROM = new char[16384 * cartridge->PGR_ROM_size];
	file.read(cartridge->PGR_ROM, 16384 * cartridge->PGR_ROM_size);

	cartridge->CHR_ROM = new char[8192 * cartridge->CHR_ROM_size];
	file.read(cartridge->CHR_ROM, 8192 * cartridge->CHR_ROM_size);


	return cartridge;
}

