#pragma once

typedef unsigned char byte;
struct PPUStatusFlags
{
	byte open_bus : 5;
	byte sprite_overflow : 1;
	byte sprite_0_hit : 1;
	byte vblank : 1;
};

struct PPUConstrolFlags
{
	byte base_addr : 2;
	byte addr_increment : 1;
	byte sprite_pt_addr : 1;

	byte background_pt_addr : 1;
	byte sprite_size : 1;
	byte ppu_master_slave : 1;
	byte trigger_nmi : 1;
};
struct PPUMaskFlags
{
	byte grayscale : 1;
	byte show_bg_leftmost : 1;
	byte show_sprite_leftmost : 1;
	byte show_bg : 1;

	byte show_sprites : 1;
	byte emph_red : 1;
	byte emph_green : 1;
	byte emph_blue : 1;
};


union PPUSTATUS
{
	PPUStatusFlags status;
	byte statusByte;
};

union PPUCTRL
{
	PPUConstrolFlags flags;
	byte Byte;
};


union PPUMASK
{
	PPUMaskFlags flags;
	byte Byte;
};

struct PixelColor
{
	byte R;
	byte G;
	byte B;
	byte A;
};
