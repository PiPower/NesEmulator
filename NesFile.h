#pragma once
#include <string>
class NesFile
{
public:
	NesFile(char* filePath);
	NesFile(std::string filePath);
	char GetMirroring();
	char GetBatteryBacked();
	char GetTrainer();
	char GetIgnore();
private:
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

