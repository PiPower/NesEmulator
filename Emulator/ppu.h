#pragma once
#include "../WindowsGraphics/DeviceResources.h"
#include "ppu_includes.h"
#include "../NesFile.h"
class PPU : public DeviceResources
{
public:
	//emulator functions
	PPU(HWND hwnd, NesFile* cartridge);
	uint8_t readStatus();
	void writeControll(uint8_t data);
	void writeMask(uint8_t data);
	void writeScroll(uint8_t data);
	void writeAddr(uint8_t data);
	void writeData(uint8_t data);
	void clock();
	void reset();
	bool triggerNMI();
	// graphics function
	void render();
	void writePixel(UINT x, UINT y, UCHAR R, UCHAR G, UCHAR B, UCHAR A);
	void RenderPatternTables();
private:
	uint8_t readByte(uint16_t addr);
	void writeByte(uint16_t addr, uint8_t);
	void initRenderingResources(HWND hwnd);
	void initResourceTransitionTable();
	void visibleScanline();
	void postRenderScanline();
	void vblankScanline();
	void preRenderScanline();
	void drawTile(UINT x, UINT y, UCHAR R, UCHAR G, UCHAR B, UCHAR A);
private:
	// PPU registers
	PPUSTATUS status_reg;
	PPUCTRL controller;
	PPUMASK mask_reg;
	uint8_t w_register;
	uint8_t x_scroll;
	uint8_t y_scroll;
	uint16_t internal_addr;
	// internal data
	bool trigger_nmi;
	UINT scanline;
	UINT cycle;
	uint8_t* nametableRAM;
	uint8_t* palleteRAM;
	PixelColor* palleteLookup;
	NesFile* cartridge;
	
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

