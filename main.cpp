#include <iostream>
#include <Windows.h>
#include "NesFile.h"
#include "Emulator/cpu.h"
#include "WindowsGraphics/window.h"
#include "Emulator/ppu.h"
using namespace std;

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine,int nShowCmd)
{
	Window window(1280, 1024, L"test", L"NES emulator");

	string filename = lpCmdLine;
	NesFile game(filename);
	PPU ppu_emulator(window.GetWindowHWND(), &game);
	CPU cpu_emulator(&game, &ppu_emulator);

	UINT ticks = 0;
	bool run_app = true;
	while (run_app)
	{
		ppu_emulator.clock();

		if ((ticks + 1) % 3 == 0)
		{
			cpu_emulator.clock();
		}

		if (ppu_emulator.triggerNMI())
		{
			cpu_emulator.nonMaskableInterrupt();
		}

		// for performance reasons perform window related events every n iterations of main loop
		if ((ticks +1)%(3 * 100 * 200) == 0 )
		{
			ticks = 0;
			run_app = window.ProcessMessages() == 0;
		}


		cpu_emulator.pressA(window.IsKeyPressed('A'));
		cpu_emulator.pressB(window.IsKeyPressed('S'));
		cpu_emulator.pressSelect(window.IsKeyPressed('D'));
		cpu_emulator.pressStart(window.IsKeyPressed(VK_SPACE));
		cpu_emulator.pressUp(window.IsKeyPressed(VK_UP));
		cpu_emulator.pressDown(window.IsKeyPressed(VK_DOWN));
		cpu_emulator.pressLeft(window.IsKeyPressed(VK_LEFT));
		cpu_emulator.pressRight(window.IsKeyPressed(VK_RIGHT));



		ticks++;
	}
}