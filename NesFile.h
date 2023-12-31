#pragma once
#include <string>
class NesFile
{
public:
	NesFile(std::string path);
	uint8_t readByte(uint16_t addr);
private:
	uint16_t readMirror000(uint16_t addr);
private:
	unsigned char PGR_ROM_size;
	unsigned char CHR_ROM_size;
	char Flags6;
	char Flags7;
	char Flags8;
	char Flags9;
	char Flags10;
	char Mapper;
	uint8_t* PGR_ROM;
	uint8_t* CHR_ROM;
	char* Trainer;
	uint16_t(NesFile::* mapper)(uint16_t addr);
};

