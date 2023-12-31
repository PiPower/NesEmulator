#pragma once
#include <string>
struct NesFile
{
	unsigned char PGR_ROM_size;
	unsigned char CHR_ROM_size;
	char Flags6;
	char Flags7;
	char Flags8;
	char Flags9;
	char Flags10;
	char Mapper;
	char* PGR_ROM;
	char* CHR_ROM;
	char* Trainer;
};

NesFile* readNESFile(std::string path);
