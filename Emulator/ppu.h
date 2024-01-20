#pragma once
#include "../WindowsGraphics/DeviceResources.h"
#include "ppu_includes.h"
#include "../NesFile.h"
class PPU : public DeviceResources
{
public:
	//emulator functions
	PPU(HWND hwnd, NesFile* cartridge);
	// reading from registers
	uint8_t readStatusRegister();
	uint8_t readDataRegister();
	uint8_t readOAMdataRegister();
	//writing to registers
	void writeOAMaddrRegister(uint8_t data);
	void writeOAMdataRegister(uint8_t data);
	void writeControllRegister(uint8_t data);
	void writeMaskRegister(uint8_t data);
	void writeScrollRegister(uint8_t data);
	void writeAddrRegister(uint8_t data);
	void writeDataRegister(uint8_t data);
	//system general
	void clock();
	void reset();
	bool triggerNMI();
	bool isDmaTriggered();
	uint8_t getDmaPage();
	void startDMA(uint8_t page);
	void stopDMA();
	// graphics function
	void render();
	void writePixel(UINT x, UINT y, UCHAR R, UCHAR G, UCHAR B, UCHAR A);
	void RenderPatternTables(uint8_t i, UINT x_offset, UINT y_offset);
	void RenderRawNametable(uint8_t i);
private:
	void drawPixel(uint8_t pixel_offset_bg, uint8_t pallete_bg, uint8_t pixel_offset_fg, uint8_t pallete_fg);
	void loadSpriteShiftRegisters();
	void clearOAM();
	void coarseXincrement();
	void coarseYincrement();
	void spriteEvaluation();
	void spritePrefetch();
	void prefetch();
	void resetX();
	uint16_t renderSprites();
	uint8_t readByte(uint16_t addr);
	void writeByte(uint16_t addr, uint8_t);
	void initRenderingResources(HWND hwnd);
	void initResourceTransitionTable();
	void visibleScanline();
	void postRenderScanline();
	void vblankScanline();
	void preRenderScanline();
	void drawTile(UINT x, UINT y, UINT  tile_size ,UCHAR R, UCHAR G, UCHAR B, UCHAR A, UINT tile_offset_x = 0, UINT tile_offset_y = 0);
private:
	// PPU registers
	PPUSTATUS status_reg;
	PPUCTRL controller;
	PPUMASK mask_reg;
	uint8_t w_register;
	//background registers
	uint16_t shift_register_up;// lower 8 bits are for currently processed tile 
	uint16_t shift_register_down; // lower 8 bits are for currently processed tile 
	uint16_t attribute_reg; // lower 8 bits are for currently processed tile 
	// sprite registers;
	uint8_t sprite_shift_lo[8];
	uint8_t sprite_shift_hi[8]; 
	// latches for temporal data
	uint8_t nametable_latch;
	uint8_t shifter_up_latch;
	uint8_t shifter_down_latch;
	uint8_t attribute_latch;
	uint8_t prevoius_read_data;
	uint8_t sprite_latch[8];// holds OAM attribute for sprite
	uint8_t sprite_y_latch[8];
	int counter[8]; // holds x for sprite
	// internal data
	uint8_t fine_x;
	InternalAddress internal_addr;
	InternalAddress temp_addr;
	bool sprite_0_selected;
	bool sprite_0_hit_possible;
	uint8_t dma_page;
	uint8_t OAMaddr;
	uint16_t pattern_base_addr;
	bool trigger_nmi;
	bool trigger_dma;
	UINT scanline;
	UINT cycle;
	uint8_t fetched_sprites;
	uint8_t secondaryOAMsize;
	uint8_t* OAMtable;
	OAMentry* secondaryOAM;
	uint8_t* nametableRAM;
	uint8_t* palleteRAM;
	PixelColor* palleteLookup;
	NesFile* cartridge;
	bool clearingOAM;
	// DirectX stuff
	D3D12_RESOURCE_BARRIER transitionTable[8];
	ComPtr<ID3D12Resource> ScreenTexture;
	ComPtr<ID3D12Resource> ScreenTextureUploadBuffer;
	D3D12_TEXTURE_COPY_LOCATION textureLocation;
	D3D12_TEXTURE_COPY_LOCATION bufferLocation;
	UCHAR* cpuScreenBufferData;
	UINT* mappedResource;
	UINT64 bufferSize;
};

