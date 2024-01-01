#include <iostream>
#include <Windows.h>
#include "NesFile.h"
#include "Emulator/cpu.h"
#include "WindowsGraphics/window.h"
#include "Emulator/ppu.h"
using namespace std;

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine,int nShowCmd)
{
	Window window(1000, 1000, L"test", L"NES emulator");
	string filename = lpCmdLine;
	NesFile game(filename);
	CPU cpu_emulator(&game);
	PPU ppu_emulator(window.GetWindowHWND());

	while (window.ProcessMessages() == 0)
	{
		cpu_emulator.clock();

		for (int y = 0; y < 10; y++)
		{
			for (int x = 40; x < 100; x++)
			{
				ppu_emulator.writePixel(x, y, 30, 123, 90, 255);
			}
		}


		for (int y = 0; y < 500; y++)
		{
			for (int x = 960; x < 999; x++)
			{
				ppu_emulator.writePixel(x, y, 255, 123, 90, 255);
			}
		}

		for (int y = 700; y < 999; y++)
		{
			for (int x = 400; x < 1000; x++)
			{
				ppu_emulator.writePixel(x, y, 255, 255, 255, 255);
			}
		}

		ppu_emulator.render();
	}
}