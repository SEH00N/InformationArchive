#include <iostream>
#include <windows.h>
#include <mmsystem.h>
#include <conio.h>
#include "resource.h"

#pragma comment(lib, "winmm.lib")

using namespace std;

int main()
{
	//PlaySound(TEXT("explosion.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
	//PlaySound(MAKEINTRESOURCE(IDR_WAVE1), NULL, SND_RESOURCE);
	PlaySound(TEXT("SystemDefault"), NULL, SND_ASYNC);
	_getch();

	return 0;
}
