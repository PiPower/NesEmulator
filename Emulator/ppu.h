#pragma once
#include "../WindowsGraphics/DeviceResources.h"
#include "includes.h"
class PPU : public DeviceResources
{
public:
	PPU(HWND hwnd);
	uint8_t readStatus();
	void render();
	void writePixel(UINT x, UINT y, UCHAR R, UCHAR G, UCHAR B, UCHAR A);
	void clock();
	void reset();
private:
	void initRenderingResources(HWND hwnd);
	void initResourceTransitionTable();
	void visibleScanline();
	void postRenderScanline();
	void vblankScanline();
	void preRenderScanline();
private:
	// PPU registers
	PPUSTATUS status_reg;
	// internal data
	UINT scanline;
	UINT cycle;
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

