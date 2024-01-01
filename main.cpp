#include <iostream>
#include <Windows.h>
#include "NesFile.h"
#include "./Emulator/cpu.h"
#include "./WindowsGraphics/window.h"
using namespace std;


int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine,int nShowCmd)
{
	Window window(1000, 1000, L"test", L"NES emulator");
	string filename = lpCmdLine;
	NesFile game(filename);
	CPU emulator(&game);

	while (window.ProcessMessages() == 0)
	{
		emulator.clock();
	}
}