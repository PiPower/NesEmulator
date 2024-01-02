#include <iostream>
#include <Windows.h>
#include "NesFile.h"
#include "Emulator/cpu.h"
#include "WindowsGraphics/window.h"
#include "Emulator/ppu.h"
using namespace std;

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine,int nShowCmd)
{
	Window window(1024, 1024, L"test", L"NES emulator");

	string filename = lpCmdLine;
	NesFile game(filename);
	PPU ppu_emulator(window.GetWindowHWND());
	CPU cpu_emulator(&game, &ppu_emulator);

	char ppu_clocks = 0;
	while (window.ProcessMessages() == 0)
	{
		ppu_emulator.clock();

		if ((ppu_clocks + 1) % 3 == 0)
		{
			ppu_clocks = 0;
			cpu_emulator.clock();
		}

		ppu_emulator.render();
		ppu_clocks++;
	}
}