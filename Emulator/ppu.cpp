#include "ppu.h"
#include "../WindowsGraphics/d3dx12.h"
PPU::PPU(HWND hwnd)
	:DeviceResources(hwnd)
{
	D3D12_RESOURCE_DESC screen_texture_desc = renderTargets[0]->GetDesc();
	if (screen_texture_desc.Format != DXGI_FORMAT_R8G8B8A8_UNORM)
	{
		MessageBox(hwnd, L"Incorrect back buffer format", NULL, MB_OK);
		exit(-1);
	}
	CreateTexture2D(&ScreenTexture, screen_texture_desc.Width, screen_texture_desc.Height, 
		screen_texture_desc.MipLevels, D3D12_RESOURCE_FLAG_NONE, screen_texture_desc.Format);

	Device->GetCopyableFootprints(&screen_texture_desc, 0, 1, 0, &bufferLocation.PlacedFootprint, nullptr, nullptr, &bufferSize);
	CreateUploadBuffer(&ScreenTextureUploadBuffer, bufferSize);
	D3D12_RANGE readRange{ 0,0 };
	ScreenTextureUploadBuffer->Map(0, &readRange, (void**)&mappedResource);

	textureLocation.pResource = ScreenTexture.Get();
	textureLocation.Type = D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX;
	textureLocation.SubresourceIndex = 0;

	bufferLocation.pResource = ScreenTextureUploadBuffer.Get();
	bufferLocation.Type = D3D12_TEXTURE_COPY_TYPE_PLACED_FOOTPRINT;

	cpuScreenBufferData = new UCHAR[bufferSize];
	InitResourceTransitionTable();
}

void PPU::render()
{
	transitionTable[5].Transition.pResource = renderTargets[current_frame].Get();
	transitionTable[7].Transition.pResource = renderTargets[current_frame].Get();

	memcpy(mappedResource, cpuScreenBufferData, bufferSize);

	CommandAllocator->Reset();
	CommandList->Reset(CommandAllocator.Get(), nullptr);

	CommandList->ResourceBarrier(2, transitionTable);
	CommandList->CopyTextureRegion(&textureLocation, 0, 0, 0, &bufferLocation, nullptr);
	CommandList->ResourceBarrier(2, transitionTable + 2);

	CommandList->ResourceBarrier(2, transitionTable + 4);
	CommandList->CopyResource(renderTargets[current_frame].Get(), ScreenTexture.Get());
	CommandList->ResourceBarrier(2, transitionTable + 6);

	NOT_SUCCEEDED(CommandList->Close());
	ID3D12CommandList* ppCommandLists[] = { CommandList.Get() };
	CommandQueue->ExecuteCommandLists(_countof(ppCommandLists), ppCommandLists);

	SwapChain->Present(0, 0);
	current_frame = SwapChain->GetCurrentBackBufferIndex();
	memset(cpuScreenBufferData, 0, bufferSize);
	Synchronize();

}

void PPU::writePixel(UINT x, UINT y, UCHAR R, UCHAR G, UCHAR B, UCHAR A)
{
	UINT pixelIndex = y * bufferLocation.PlacedFootprint.Footprint.RowPitch + x * 4; //4 is for per element size 
	cpuScreenBufferData[pixelIndex] = R;
	cpuScreenBufferData[pixelIndex + 1] = G;
	cpuScreenBufferData[pixelIndex + 2] = B;
	cpuScreenBufferData[pixelIndex + 3] = A;

}

void PPU::InitResourceTransitionTable()
{
	// copy buffer to texture
	transitionTable[0] = CD3DX12_RESOURCE_BARRIER::Transition(ScreenTexture.Get(),
		D3D12_RESOURCE_STATE_GENERIC_READ, D3D12_RESOURCE_STATE_COPY_DEST);
	transitionTable[1] = CD3DX12_RESOURCE_BARRIER::Transition(ScreenTextureUploadBuffer.Get(),
		D3D12_RESOURCE_STATE_GENERIC_READ, D3D12_RESOURCE_STATE_COPY_SOURCE);

	//reverse ubove transition
	transitionTable[2] = CD3DX12_RESOURCE_BARRIER::Transition(ScreenTexture.Get(),
		D3D12_RESOURCE_STATE_COPY_DEST,D3D12_RESOURCE_STATE_GENERIC_READ);
	transitionTable[3] = CD3DX12_RESOURCE_BARRIER::Transition(ScreenTextureUploadBuffer.Get(),
		D3D12_RESOURCE_STATE_COPY_SOURCE, D3D12_RESOURCE_STATE_GENERIC_READ);

	// copy texture to bakc buffer
	transitionTable[4] = CD3DX12_RESOURCE_BARRIER::Transition(ScreenTexture.Get(),
		D3D12_RESOURCE_STATE_GENERIC_READ, D3D12_RESOURCE_STATE_COPY_SOURCE);
	transitionTable[5] = CD3DX12_RESOURCE_BARRIER::Transition(nullptr,
		D3D12_RESOURCE_STATE_COMMON, D3D12_RESOURCE_STATE_COPY_DEST);

	// copy buffer to texture
	transitionTable[6] = CD3DX12_RESOURCE_BARRIER::Transition(ScreenTexture.Get(),
		D3D12_RESOURCE_STATE_COPY_SOURCE, D3D12_RESOURCE_STATE_GENERIC_READ);
	transitionTable[7] = CD3DX12_RESOURCE_BARRIER::Transition(nullptr,
		 D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_COMMON);
}
