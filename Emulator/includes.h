#pragma once

typedef unsigned char bit; 
struct FlagBits
{
	bit carry : 1;
	bit zero : 1;
	bit interrupt : 1;
	bit decimal : 1;
	bit break_bit : 1;
	bit ignored : 1;
	bit overflow : 1;
	bit negative : 1;
};

union FLAGS
{
	FlagBits FLAGS;
	unsigned  char flagByte;
};