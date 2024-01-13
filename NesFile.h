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
	void writeByteCPU(uint16_t addr, uint8_t data);
	uint8_t readBytePPU(uint16_t addr);
	void writeBytePPU(uint16_t addr, uint8_t data);
private:
	// mirror 000
	uint16_t readMirrorCPU000(uint16_t addr);
	uint16_t readMirrorPPU000(uint16_t addr);
	void writeByteMirrorCPU000(uint16_t addr, uint8_t data);
	void writeByteMirrorPPU000(uint16_t addr, uint8_t data);
	// mirror 003
	uint16_t readMirrorCPU003(uint16_t addr);
	uint16_t readMirrorPPU003(uint16_t addr);
	void writeByteMirrorCPU003(uint16_t addr, uint8_t data);
	void writeByteMirrorPPU003(uint16_t addr, uint8_t data);
private:
	unsigned char nPRGBanks;
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
	uint8_t nCHRBankSelect ;
	char* Trainer;
	uint16_t(NesFile::* ptrReadByteCPU)(uint16_t addr);
	uint16_t(NesFile::* ptrReadBytePPU)(uint16_t addr);
	void (NesFile::* ptrWriteByteCPU)(uint16_t addr, uint8_t data);
	void (NesFile::* ptrWriteBytePPU)(uint16_t addr, uint8_t data);
};

