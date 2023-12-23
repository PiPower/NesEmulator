#include "NesFile.h"
#include <fstream>

using namespace std;
NesFile::NesFile(char* filePath)
{

}

NesFile::NesFile(std::string filePath)
	:
	NesFile(filePath.c_str())
{
}
