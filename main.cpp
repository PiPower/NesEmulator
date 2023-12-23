#include <iostream>
#include <Windows.h>
#include "NesFile.h"
using namespace std;


int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine,int nShowCmd)
{
	string filename = lpCmdLine;
	NesFile game(lpCmdLine);

}