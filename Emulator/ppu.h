#pragma once
#include "../WindowsGraphics/DeviceResources.h"
class PPU : public DeviceResources
{
public:
	PPU(HWND hwnd);
	void render();
	void writePixel(UINT x, UINT y, UCHAR R, UCHAR G, UCHAR B, UCHAR A);
private:
	void InitResourceTransitionTable();
private:
	D3D12_RESOURCE_BARRIER transitionTable[8];
	ComPtr<ID3D12Resource> ScreenTexture;
	ComPtr<ID3D12Resource> ScreenTextureUploadBuffer;
	D3D12_TEXTURE_COPY_LOCATION textureLocation;
	D3D12_TEXTURE_COPY_LOCATION bufferLocation;
	UCHAR* cpuScreenBufferData;
	UINT* mappedResource;
	UINT64 bufferSize;
};

