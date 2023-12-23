#pragma once
#include <string>
class NesFile
{
public:
	NesFile(char* filePath);
	NesFile(std::string filePath);
private:
	unsigned int PGR_ROM_size;
	unsigned int CHR_ROM_size;
	char Flags6;
	char Flags7;
	char Flags8;
	char Flags9;
	char Flags10;
	char* PGR_ROM;
	char* CHR_ROM;
};

