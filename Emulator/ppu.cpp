#include "ppu.h"
#include "../WindowsGraphics/d3dx12.h"

#define PATTERN_TILE_SIZE 2
#define PATTERN_TABLE_OFFSET_X 1024
#define PATTERN_TABLE_OFFSET_Y 0
#define RENDER_PATTERN_TABLE
#define PRERENDER_SCANLINE 261

PPU::PPU(HWND hwnd, NesFile* cartridge)
	:DeviceResources(hwnd), cartridge(cartridge), trigger_nmi(false)
{
	initRenderingResources(hwnd);
	reset();
	nametableRAM = new uint8_t[0x0800];
	palleteRAM = new  uint8_t[0x20];
	OAMtable = new uint8_t[64 * 4];
	secondaryOAM = new  OAMentry[8];
	palleteLookup = new PixelColor[0x40];
	clearingOAM = false;
	secondaryOAMsize = 0;

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

uint8_t PPU::readDataRegister()
{

	uint8_t data = prevoius_read_data;
	prevoius_read_data =  readByte(internal_addr);
	if (internal_addr >= 0x3F00) data = prevoius_read_data;

	internal_addr += controller.flags.addr_increment > 0 ? 32 : 1;
	return data;
}

uint8_t PPU::readOAMdataRegister()
{
	return clearingOAM? 0xFF : OAMtable[OAMaddr];
}

void PPU::writeOAMaddrRegister(uint8_t data)
{
	OAMaddr = data;
}

void PPU::writeOAMdataRegister(uint8_t data)
{
	OAMtable[OAMaddr] = data;
	OAMaddr++;
}

void PPU::writeControllRegister(uint8_t data)
{
	uint8_t nmi_bit = controller.flags.trigger_nmi;
	controller.Byte = data;

	switch (controller.flags.base_addr)
	{
	case 0:
		nametable_base_addr = 0x2000;
		break;
	case 1:
		nametable_base_addr = 0x2400;
		break;
	case 2:
		nametable_base_addr = 0x2800;
		break;
	case 3:
		nametable_base_addr = 0x2C00;
		break;
	}
	pattern_base_addr = controller.flags.background_pt_addr ? 0x1000 : 0x0 ;

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
		internal_addr = (data << 8) | (internal_addr & 0x00FF);
		w_register = 1;
	}
	else if (w_register == 1)
	{
		internal_addr = (data) | (internal_addr & 0xFF00);
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

void PPU::RenderPatternTables(uint8_t i, UINT x_offset, UINT y_offset)
{
	uint16_t base_addr = 0x1000 * i;
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
						palleteLookup[index].G, palleteLookup[index].B, palleteLookup[index].A, x_offset, y_offset);

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
			uint8_t patternTableIndex =  readByte(0x2000  + y * 32 + x);
			uint16_t patternTableAddr = patternTableIndex * 16;

			for (uint8_t j = 0; j < 8; j++)
			{
				uint8_t lo = readByte(patternTableAddr);
				uint8_t hi = readByte(0x0008 + patternTableAddr);
				for (uint8_t i = 0; i < 8; i++)
				{
					uint8_t index = ((hi & 0x80) >> 6) | ((lo & 0x80) >> 7) + 1;
					hi <<= 1;
					lo <<= 1;

					drawTile(x * 8 + i, y * 8 + j, 2, patternTableIndex,
						patternTableIndex, patternTableIndex,255, 0, 0);

				}
				patternTableAddr++;
			}


		}
	}
}

void PPU::loadSpriteShiftRegisters()
{

	fetched_sprites = secondaryOAMsize;
	uint8_t sprite_index = floor((cycle - 257) / 8.0);
	UINT prefetch_scanline = scanline == PRERENDER_SCANLINE ? 0 : scanline;

	uint8_t sprite_y = prefetch_scanline - secondaryOAM[sprite_index].y;
	if (secondaryOAM[sprite_index].attribute.flags.flip_ver > 0) sprite_y = 7 - sprite_y;

	if (sprite_index >= secondaryOAMsize)
	{
		sprite_shift_lo[sprite_index] = 0xFF;
		sprite_shift_hi[sprite_index] = 0xFF;
		sprite_latch[sprite_index] = 0xFF;
		counter[sprite_index] = 0xFF;
		return;
	}

	uint16_t sprite_offset = ((uint16_t)secondaryOAM[sprite_index].index_number) * 16 ;
	uint16_t sprite_base_addr = controller.flags.sprite_pt_addr ? 0x1000 : 0x0000;

	sprite_shift_lo[sprite_index] = readByte(sprite_base_addr + sprite_offset + sprite_y );
	sprite_shift_hi[sprite_index] = readByte(sprite_base_addr + sprite_offset + 0x0008 + sprite_y);

	sprite_latch[sprite_index] = secondaryOAM[sprite_index].attribute.Byte;
	counter[sprite_index] = secondaryOAM[sprite_index].x;
	sprite_y_latch[sprite_index] = secondaryOAM[sprite_index].y;
}

void PPU::clearOAM()
{
	uint8_t cycle_norm = cycle - 1;
	secondaryOAMsize = 0;
	clearingOAM = true;

	if (cycle_norm % 2 == 0)
	{
		((uint8_t*)secondaryOAM)[cycle_norm / 2] = 0xFF;
	}
}

void PPU::spriteEvaluation()
{

	clearingOAM = false;
	if (secondaryOAMsize == 8)
	{
		// add sprite overflow mechanism
		return;
	}


	UINT prefetch_scanline = scanline == PRERENDER_SCANLINE ? 0 : scanline;
	uint8_t primaryIndex = ((cycle - 65) % 64) * sizeof(OAMentry);
	memcpy((void*)&secondaryOAM[secondaryOAMsize], (void*)&OAMtable[primaryIndex], sizeof(OAMentry) );
	OAMentry* oamObject = &secondaryOAM[secondaryOAMsize];

	if ( !( (prefetch_scanline - oamObject->y) >= 0 && (prefetch_scanline - oamObject->y) < 8 ))
	{
		return;
	}

	if (primaryIndex == 0) sprite_0_selected = true;
	secondaryOAMsize++;
}

void PPU::spritePrefetch()
{
	
	if (cycle > 0 && cycle < 65)
	{
		sprite_0_selected = false;
		clearOAM();
	}

	if (cycle >= 65 && cycle < 257)
	{
		spriteEvaluation();
	}

	if (cycle >= 257 && cycle <= 320)
	{
		loadSpriteShiftRegisters();
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
		sprite_0_hit_possible = false;
		scanline++;
	}

	if (scanline >= 0 && scanline <= 239)
	{
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
		RenderPatternTables(0, PATTERN_TABLE_OFFSET_X, PATTERN_TABLE_OFFSET_Y);
		RenderPatternTables(1, PATTERN_TABLE_OFFSET_X, PATTERN_TABLE_OFFSET_Y + 256);
#endif
#ifdef RENDER_NAME_TABLE
		RenderRawNametable(0);
#endif 

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

	trigger_dma = false;
	sprite_0_selected = false;
}

bool PPU::triggerNMI()
{
	bool nmiBuff = trigger_nmi;
	trigger_nmi = false;
	return nmiBuff;
}

bool PPU::isDmaTriggered()
{
	return trigger_dma;
}

uint8_t PPU::getDmaPage()
{
	return dma_page;
}

void PPU::startDMA(uint8_t page)
{
	trigger_dma = true;
	dma_page = page;
}

void PPU::stopDMA()
{
	trigger_dma = false;
}

void PPU::prefetch()
{
	//fetch data for first 16 pixels
	if (cycle >= 321 && cycle <= 337)
	{
		uint8_t pixelId = (cycle - 321) % 8;
		UINT prefetch_scanline = scanline == PRERENDER_SCANLINE ? 0 : scanline + 1;

		if (pixelId == 0 && cycle > 321)
		{
			shift_register_down >>= 8;
			shift_register_up >>= 8;

			shift_register_down = (shift_register_down & 0x00FF) | (shifter_down_latch << 8);
			shift_register_up = (shift_register_up & 0x00FF) | (shifter_up_latch << 8);

			attribute_reg >>= 8;
			attribute_reg = (attribute_reg & 0x00FF) | ((uint16_t)attribute_latch << 8);
		}

		switch (pixelId)
		{
		case 0:
		{
			uint8_t y_tile = floor((prefetch_scanline) / 8);
			uint8_t x_tile = floor((cycle - 321) / 8);
			nametable_latch = readByte(nametable_base_addr + y_tile * 32 + x_tile);

		}
		break;
		case 2:
		{
			uint8_t y_tile = floor((prefetch_scanline) / 32);
			uint8_t x_tile = floor((cycle - 321) / 32);
			attribute_latch = readByte(nametable_base_addr + 0x03C0 + y_tile * 8 + x_tile);
		}
		break;
		case 4:
			shifter_down_latch = readByte(pattern_base_addr + nametable_latch * 16 + prefetch_scanline % 8);
			break;
		case 6:
			shifter_up_latch = readByte(pattern_base_addr + nametable_latch * 16 + 0x0008 + prefetch_scanline % 8);
			break;
		}
	}
}

PixelColor PPU::renderSprites(uint8_t background, uint8_t universalBackground)
{
	uint8_t sprite_to_draw = 0xFF;
	PixelColor out = palleteLookup[background];

	bool OAMprint = false;


	for (int i = fetched_sprites - 1; i >= 0; i--)
	{

		if (counter[i] <= 0 && counter[i] > -8)
		{
			uint8_t shftOffset = (sprite_latch[i] & 0x40) > 0 ? -counter[i] : (counter[i] + 7 );
			uint8_t patternLo = (sprite_shift_lo[i] >> shftOffset) & 0x01;
			uint8_t patternHi = (sprite_shift_hi[i] >> shftOffset) & 0x01;
			uint8_t pallete = sprite_latch[i] & 0x03;

			uint8_t sprite_id = readByte(0x3F10 + pallete * 4 + ((patternHi << 1) | patternLo));
			if (universalBackground != sprite_id)
			{
				out = palleteLookup[sprite_id];
				if (sprite_0_hit_possible && i == 0 && background != universalBackground)
				{
					status_reg.status.sprite_0_hit = 1;
				}
			}
		}

		counter[i]--;
	}
	return out;
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
		if (cartridge->getNametableMirroring() == VERTICAL) //vertical
		{
			if (nametable_addr >= 0x0800) nametable_addr -= 0x0800;
			return nametableRAM[nametable_addr];
		}
	}
	if (addr >= 0x3F00 && addr <= 0x3FFF)
	{
		addr = addr & 0x001F;
		if (addr == 0x0010) addr = 0x0000;
		else if (addr == 0x0014) addr = 0x0004;
		else if (addr == 0x0018) addr = 0x0008;
		else if (addr == 0x001C) addr = 0x000C;
		return palleteRAM[addr];
	}
}

void PPU::writeByte(uint16_t addr, uint8_t data)
{
	if (addr >= 0x0000 && addr <= 0x1FFF)
	{
		cartridge->writeBytePPU(addr, data);
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

	if (cycle == 0)
	{
		if (sprite_0_selected) sprite_0_hit_possible = true;
		return;
	}

	if (cycle >= 1 && cycle < 257 )
	{
		uint8_t pixelId = (cycle - 1) % 8;

		if (pixelId == 0 && cycle > 1)
		{
			shift_register_down >>= 8;
			shift_register_up >>= 8;

			shift_register_down = (shift_register_down & 0x00FF) | ((uint16_t)shifter_down_latch << 8);
			shift_register_up = (shift_register_up & 0x00FF) | ((uint16_t)shifter_up_latch << 8);

			attribute_reg >>= 8;
			attribute_reg = (attribute_reg & 0x00FF) | ((uint16_t)attribute_latch << 8);
		}	


		switch (pixelId)
		{
		// store nametable for next tile in latch
		case 0:
		{
			uint8_t y_tile = floor(scanline / 8);
			uint8_t x_tile = floor((cycle-1 + 16) / 8);
			nametable_latch = readByte(nametable_base_addr + y_tile * 32 + x_tile);

		}
			break;
		//  store attribute for next tiles in latch 
		case 2:
		{
			uint8_t y_tile = floor(scanline / 32);
			uint8_t x_tile = floor((cycle - 1 + 16) / 32);
			attribute_latch = readByte(nametable_base_addr + 0x03C0 + y_tile * 8 + x_tile);
		}
			break;
		//  store lo patter on for next tile in latch 
		case 4:
			shifter_down_latch = readByte(pattern_base_addr +  nametable_latch * 16 + scanline%8);
			break;
		//  store hi patter on for next tile in latch 
		case 6:
			shifter_up_latch = readByte(pattern_base_addr + nametable_latch * 16 + 0x0008 + scanline % 8);
			break;
		}


		uint8_t currentAtribute = attribute_reg & 0x00FF;
		uint8_t y_atribute_tile = (uint8_t)floor(scanline / 16) % 2; // x coord of 2x2 tile within  4x4 tile
		uint8_t x_atribute_tile = (uint8_t)floor((cycle - 1) / 16) % 2; // y coord of 2x2 tile within  4x4 tile

		uint8_t pallete = (currentAtribute >> ((y_atribute_tile * 4 + x_atribute_tile *2))) & 0x03;

		pixelId = 7 - pixelId; //linear map 0-7 to 7-0 because bit for pixel 0 in given tile is 7th bit in register
		uint8_t patternLo = (shift_register_down >> pixelId) & 0x1;
		uint8_t patternHi = (shift_register_up >> pixelId) & 0x1;

		uint8_t index =  readByte(0x3F00  + pallete * 4 + ((patternHi << 1) | patternLo) );

		PixelColor color = palleteLookup[index];
		if (mask_reg.flags.show_sprites)
		{
			color = renderSprites(index, readByte(0x3F00));
		}
		drawTile(cycle - 1, scanline, 4, color.R, color.G, color.B, color.A);
	}

	spritePrefetch();
	prefetch();
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


	spritePrefetch();
	prefetch();
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
