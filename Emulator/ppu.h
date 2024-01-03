#pragma once
#include "../WindowsGraphics/DeviceResources.h"
#include "includes.h"
#include "../NesFile.h"
class PPU : public DeviceResources
{
public:
	PPU(HWND hwnd, NesFile* cartridge);
	uint8_t readStatus();
	void writeControll(uint8_t data);
	void render();
	void writePixel(UINT x, UINT y, UCHAR R, UCHAR G, UCHAR B, UCHAR A);
	void clock();
	void reset();
	bool triggerNMI();
private:
	uint8_t readByte(uint16_t addr);
	void initRenderingResources(HWND hwnd);
	void initResourceTransitionTable();
	void visibleScanline();
	void postRenderScanline();
	void vblankScanline();
	void preRenderScanline();
private:
	// PPU registers
	PPUSTATUS status_reg;
	PPUCTRL controller;
	// internal data
	bool trigger_nmi;
	UINT scanline;
	UINT cycle;
	uint8_t* nametableRAM;
	uint8_t* palleteRAM;
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

