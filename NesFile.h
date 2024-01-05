#pragma once
#include <string>
#define HORIZONTAL 0 
#define VERTICAL 1
class NesFile
{
public:
	NesFile(std::string path);
	uint8_t getNametableMirroring();
	uint8_t readByteCPU(uint16_t addr);
	uint8_t readBytePPU(uint16_t addr);
private:
	uint16_t readMirrorCPU000(uint16_t addr);
	uint16_t readMirrorPPU000(uint16_t addr);
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
	uint16_t(NesFile::* mapperCPU)(uint16_t addr);
	uint16_t(NesFile::* mapperPPU)(uint16_t addr);
};

