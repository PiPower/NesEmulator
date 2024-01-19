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

struct AttributeFlags
{
	byte pallete : 2;
	byte unimplemented : 3;

	byte priority : 1;
	byte flip_hor : 1;
	byte flip_ver : 1;

};

union Attribute
{
	AttributeFlags flags;
	byte Byte;
};
struct OAMentry
{
	uint8_t y;
	uint8_t index_number;
	Attribute attribute;
	uint8_t x;
};

union InternalAddress
{
	struct
	{
		uint16_t coarse_x : 5;
		uint16_t coarse_y : 5;
		uint16_t nametable : 2;
		uint16_t fine_y : 3;
		uint16_t padding : 1;
	};

	uint16_t word;
};