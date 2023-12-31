#include <iostream>
#include <Windows.h>
#include "NesFile.h"
#include "./Emulator/cpu.h"
using namespace std;


int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine,int nShowCmd)
{
	string filename = lpCmdLine;
	NesFile* game = readNESFile(filename);
	CPU emulator(game);
	while (true)
	{
		emulator.clock();
	}
}