#include "ppu.h"
#include "../WindowsGraphics/d3dx12.h"

#define PATTERN_TILE_SIZE 2
#define PATTERN_TABLE_OFFSET_X 768
#define PATTERN_TABLE_OFFSET_Y 0
#define RENDER_PATTERN_TABLE
#define RENDER_NAME_TABLE
PPU::PPU(HWND hwnd, NesFile* cartridge)
	:DeviceResources(hwnd), cartridge(cartridge), trigger_nmi(false)
{
	initRenderingResources(hwnd);
	reset();
	nametableRAM = new uint8_t[0x0800];
	palleteRAM = new  uint8_t[0x20];

	palleteLookup = new PixelColor[0x40];
	palleteLookup[0x00] = PixelColor{84, 84, 84, 255};
	palleteLookup[0x01] = PixelColor{0, 30, 116, 255};
	palleteLookup[0x02] = PixelColor{8, 16, 144, 255};
	palleteLookup[0x03] = PixelColor{48, 0, 136, 255};
	palleteLookup[0x04] = PixelColor{68, 0, 100, 255};
	palleteLookup[0x05] = PixelColor{92, 0, 48, 255};
	palleteLookup[0x06] = PixelColor{84, 4, 0, 255};
	palleteLookup[0x07] = PixelColor{60, 24, 0, 255};
	palleteLookup[0x08] = PixelColor{32, 42, 0, 255};
	palleteLookup[0x09] = PixelColor{8, 58, 0, 255};
	palleteLookup[0x0A] = PixelColor{0, 64, 0, 255};
	palleteLookup[0x0B] = PixelColor{0, 60, 0, 255};
	palleteLookup[0x0C] = PixelColor{0, 50, 60, 255};
	palleteLookup[0x0D] = PixelColor{0, 0, 0, 255};
	palleteLookup[0x0E] = PixelColor{0, 0, 0, 255};
	palleteLookup[0x0F] = PixelColor{0, 0, 0, 255};
						  
	palleteLookup[0x10] = PixelColor{152, 150, 152, 255};
	palleteLookup[0x11] = PixelColor{8, 76, 196, 255};
	palleteLookup[0x12] = PixelColor{48, 50, 236, 255};
	palleteLookup[0x13] = PixelColor{92, 30, 228, 255};
	palleteLookup[0x14] = PixelColor{136, 20, 176, 255};
	palleteLookup[0x15] = PixelColor{160, 20, 100, 255};
	palleteLookup[0x16] = PixelColor{152, 34, 32, 255};
	palleteLookup[0x17] = PixelColor{120, 60, 0, 255};
	palleteLookup[0x18] = PixelColor{84, 90, 0, 255};
	palleteLookup[0x19] = PixelColor{40, 114, 0, 255};
	palleteLookup[0x1A] = PixelColor{8, 124, 0, 255};
	palleteLookup[0x1B] = PixelColor{0, 118, 40, 255};
	palleteLookup[0x1C] = PixelColor{0, 102, 120, 255};
	palleteLookup[0x1D] = PixelColor{0, 0, 0, 255};
	palleteLookup[0x1E] = PixelColor{0, 0, 0, 255};
	palleteLookup[0x1F] = PixelColor{0, 0, 0, 255};
						  
	palleteLookup[0x20] = PixelColor{236, 238, 236, 255};
	palleteLookup[0x21] = PixelColor{76, 154, 236, 255};
	palleteLookup[0x22] = PixelColor{120, 124, 236, 255};
	palleteLookup[0x23] = PixelColor{176, 98, 236, 255};
	palleteLookup[0x24] = PixelColor{228, 84, 236, 255};
	palleteLookup[0x25] = PixelColor{236, 88, 180, 255};
	palleteLookup[0x26] = PixelColor{236, 106, 100, 255};
	palleteLookup[0x27] = PixelColor{212, 136, 32, 255};
	palleteLookup[0x28] = PixelColor{160, 170, 0, 255};
	palleteLookup[0x29] = PixelColor{116, 196, 0, 255};
	palleteLookup[0x2A] = PixelColor{76, 208, 32, 255};
	palleteLookup[0x2B] = PixelColor{56, 204, 108, 255};
	palleteLookup[0x2C] = PixelColor{56, 180, 204, 255};
	palleteLookup[0x2D] = PixelColor{60, 60, 60, 255};
	palleteLookup[0x2E] = PixelColor{0, 0, 0, 255};
	palleteLookup[0x2F] = PixelColor{0, 0, 0, 255};
						  
	palleteLookup[0x30] = PixelColor{236, 238, 236, 255};
	palleteLookup[0x31] = PixelColor{168, 204, 236, 255};
	palleteLookup[0x32] = PixelColor{188, 188, 236, 255};
	palleteLookup[0x33] = PixelColor{212, 178, 236, 255};
	palleteLookup[0x34] = PixelColor{236, 174, 236, 255};
	palleteLookup[0x35] = PixelColor{236, 174, 212, 255};
	palleteLookup[0x36] = PixelColor{236, 180, 176, 255};
	palleteLookup[0x37] = PixelColor{228, 196, 144, 255};
	palleteLookup[0x38] = PixelColor{204, 210, 120, 255};
	palleteLookup[0x39] = PixelColor{180, 222, 120, 255};
	palleteLookup[0x3A] = PixelColor{168, 226, 144, 255};
	palleteLookup[0x3B] = PixelColor{152, 226, 180, 255};
	palleteLookup[0x3C] = PixelColor{160, 214, 228, 255};
	palleteLookup[0x3D] = PixelColor{160, 162, 160, 255};
	palleteLookup[0x3E] = PixelColor{0, 0, 0, 255};
	palleteLookup[0x3F] = PixelColor{0, 0, 0, 255};
}

uint8_t PPU::readStatusRegister()
{
	uint8_t statusBuffer = status_reg.statusByte;
	status_reg.status.vblank = 0;
	w_register = 0;
	return statusBuffer;
}

void PPU::writeControllRegister(uint8_t data)
{
	uint8_t nmi_bit = controller.flags.trigger_nmi;
	controller.Byte = data;
	if (status_reg.status.vblank > 0 && nmi_bit == 0 && controller.flags.trigger_nmi > 0)
	{
		trigger_nmi = true;
	}
}

void PPU::writeMaskRegister(uint8_t data)
{
	mask_reg.Byte = data;
}

void PPU::writeScrollRegister(uint8_t data)
{
	if (w_register == 0)
	{
		x_scroll = data;
		w_register = 1;
	}
	else if (w_register == 1)
	{
		y_scroll = data;
		w_register = 0;
	}
}

void PPU::writeAddrRegister(uint8_t data)
{
	if (w_register == 0)
	{
		internal_addr |= data << 8;
		w_register = 1;
	}
	else if (w_register == 1)
	{
		internal_addr |= data;
		w_register = 0;
	}
}

void PPU::writeDataRegister(uint8_t data)
{
	writeByte(internal_addr, data);
	internal_addr += controller.flags.addr_increment > 0 ? 32 : 1;
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

void PPU::RenderPatternTables()
{
	uint16_t base_addr = 0;
	for (uint8_t y = 0; y < 16; y++)
	{
		for (uint8_t x = 0; x < 16; x++)
		{

			for (uint8_t j = 0; j < 8; j++)
			{
				uint8_t lo = readByte(base_addr);
				uint8_t hi = readByte(0x0008 + base_addr);
				for (uint8_t  i = 0; i < 8; i++)
				{
					uint8_t index =( (hi & 0x80) >> 6) |( (lo & 0x80) >> 7 );
					hi <<= 1;
					lo <<= 1;

					drawTile(x * 8 + i, y * 8 + j,PATTERN_TILE_SIZE ,palleteLookup[index].R,
						palleteLookup[index].G, palleteLookup[index].B, palleteLookup[index].A, PATTERN_TABLE_OFFSET_X, PATTERN_TABLE_OFFSET_Y);

				}
				base_addr++;
			}

			base_addr += 0x08;
		}
	}
}

void PPU::RenderRawNametable(uint8_t i)
{
	for (uint8_t y = 0; y < 30; y++)
	{
		for (uint8_t x = 0; x < 32; x++)
		{
			uint8_t patternTableIndex =  readByte(0x2000 + y * 32 + x);
			uint16_t patternTableAddr = patternTableIndex * 16;

			for (uint8_t j = 0; j < 8; j++)
			{
				uint8_t lo = readByte(patternTableAddr);
				uint8_t hi = readByte(0x0008 + patternTableAddr);
				for (uint8_t i = 0; i < 8; i++)
				{
					uint8_t index = ((hi & 0x80) >> 6) | ((lo & 0x80) >> 7);
					hi <<= 1;
					lo <<= 1;

					drawTile(x * 8 + i, y * 8 + j, 2, palleteLookup[index].R,
						palleteLookup[index].G, palleteLookup[index].B, palleteLookup[index].A, 0, 0);

				}
				patternTableAddr++;
			}


		}
	}
}

void PPU::clock()
{
	if (scanline == 0)
	{
		status_reg.status.vblank = 0;
	}

	if (cycle > 340)
	{
		cycle = 0;
		scanline++;
	}

	if (scanline >= 0 && scanline <= 239)
	{
		if(cycle < 256 )writePixel(cycle, scanline, 144, 255, 34, 255);
		visibleScanline();
	}

	if (scanline == 240)
	{
		postRenderScanline();
	}

	if (scanline >= 241 && scanline <= 260)
	{
		vblankScanline();
	}

	if (scanline == 261)
	{
		preRenderScanline();
	}

	cycle++;
	if (scanline == 261 && cycle >= 341)
	{
		cycle = 0; 
		scanline = 0;

#ifdef RENDER_PATTERN_TABLE
		RenderPatternTables();
#endif
#ifdef RENDER_NAME_TABLE
		RenderRawNametable(0);
#endif // RENDER_NAME_TABLE

		render();
	}
}

void PPU::reset()
{
	scanline = 0;
	cycle = 0;

	x_scroll = 0;
	y_scroll = 0;
	w_register = 0;
	controller.Byte = 0;
	mask_reg.Byte = 0;
	status_reg.statusByte = 0;
	status_reg.status.vblank = 1;
	status_reg.status.sprite_0_hit = 1;
}

bool PPU::triggerNMI()
{
	bool nmiBuff = trigger_nmi;
	trigger_nmi = false;
	return nmiBuff;
}

uint8_t PPU::readByte(uint16_t addr)
{
	if (addr >= 0x0000 && addr <= 0x1FFF)
	{
		return cartridge->readBytePPU(addr);
	}
	if (addr >= 0x2000 && addr <= 0x3EFF)
	{
		uint16_t nametable_addr = addr &= 0x0FFF;
		if (cartridge->getNametableMirroring() == HORIZONTAL) //horizontal
		{
			if (nametable_addr >= 0x0400 && nametable_addr <= 0x07FF) nametable_addr -= 0x0400; // map to 0 - 0x3FF
			else if (nametable_addr >= 0x0800 && nametable_addr <= 0x0BFF) nametable_addr -= 0x0400;// map to 0x0400 - 0x7FF
			else if (nametable_addr >= 0x0C00 && nametable_addr <= 0x0FFF) nametable_addr -= 0x0800; // map to 0x0400 - 0x7FF

			return nametableRAM[nametable_addr];
		}
		if (cartridge->getNametableMirroring() == VERTICAL) //horizontal
		{
			if (nametable_addr >= 0x0800) nametable_addr -= 0x0800;
			return nametableRAM[nametable_addr];
		}
	}
	if (addr >= 0x3F00 && addr <= 0x3FFF)
	{
		addr = addr & 0x001F;
		if (addr == 0x0010) addr = 0x0000;
		if (addr == 0x0014) addr = 0x0004;
		if (addr == 0x0018) addr = 0x0008;
		if (addr == 0x001C) addr = 0x000C;
		return palleteRAM[addr];
	}
}

void PPU::writeByte(uint16_t addr, uint8_t data)
{
	if (addr >= 0x0000 && addr <= 0x1FFF)
	{
		OutputDebugStringW(L"Pattern table writes not supported \n");
		exit(-1);
	}
	if (addr >= 0x2000 && addr <= 0x3EFF)
	{
		uint16_t nametable_addr = addr &= 0x0FFF;
		if (cartridge->getNametableMirroring() == HORIZONTAL) //horizontal
		{
			if (nametable_addr >= 0x0400 && nametable_addr <= 0x07FF) nametable_addr -= 0x0400; // map to 0 - 0x3FF
			else if (nametable_addr >= 0x0800 && nametable_addr <= 0x0BFF) nametable_addr -= 0x0400; // map to 0x0400 - 0x7FF
			else if (nametable_addr >= 0x0C00 && nametable_addr <= 0x0FFF) nametable_addr -= 0x0800; // map to 0x0400 - 0x7FF

			nametableRAM[nametable_addr] = data;
		}
		if (cartridge->getNametableMirroring() == VERTICAL) //horizontal
		{
			if (nametable_addr >= 0x0800) nametable_addr -= 0x0800; // map to 0 - 0x07FF
			nametableRAM[nametable_addr] = data;
		}
	}
	if (addr >= 0x3F00 && addr <= 0x3FFF)
	{
		addr = addr & 0x001F;
		if (addr == 0x0010) addr = 0x0000;
		if (addr == 0x0014) addr = 0x0004;
		if (addr == 0x0018) addr = 0x0008;
		if (addr == 0x001C) addr = 0x000C;
		palleteRAM[addr] = data;
	}
}

void PPU::initRenderingResources(HWND hwnd)
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
	memset(cpuScreenBufferData, 0, bufferSize);

	initResourceTransitionTable();
}

void PPU::initResourceTransitionTable()
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

void PPU::visibleScanline()
{
}

void PPU::postRenderScanline()
{
}

void PPU::vblankScanline()
{
	if (scanline == 241 && cycle == 0)
	{
		trigger_nmi = controller.flags.trigger_nmi > 0 ? true : false;
		status_reg.status.vblank = 1;
	}
}

void PPU::preRenderScanline()
{
	if (cycle == 1)
	{
		status_reg.status.sprite_0_hit = 0;
		status_reg.status.sprite_overflow = 0;
		status_reg.status.vblank = 0;
		trigger_nmi = false;
	}
}

void PPU::drawTile(UINT x, UINT y, UINT  tile_size, UCHAR R, UCHAR G, UCHAR B, UCHAR A, UINT tile_offset_x, UINT tile_offset_y)
{

	uint16_t pixel_x = x * tile_size;
	uint16_t pixel_y = y * tile_size;
	for (uint16_t j = 0; j < tile_size; j++)
	{
		for (uint16_t i = 0; i < tile_size; i++)
		{
			writePixel(pixel_x + i + tile_offset_x, pixel_y + j + tile_offset_y, R, G, B, A);
		}
	}
}
