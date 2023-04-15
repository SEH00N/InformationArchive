#include <io.h>
#include <iostream>
#include <fcntl.h>
#include "console.h"
#include <string>
#include "bombman.h"

using namespace std;

int cursorY = 0;

void AsciiArt()
{
	int previewMode = _setmode(_fileno(stdout), _O_U16TEXT);

	wcout << L"██████╗  ██████╗ ███╗   ███╗██████╗ ███╗   ███╗ █████╗ ███╗   ██╗ \n";
	wcout << L"██╔══██╗██╔═══██╗████╗ ████║██╔══██╗████╗ ████║██╔══██╗████╗  ██║ \n";
	wcout << L"██████╔╝██║   ██║██╔████╔██║██████╔╝██╔████╔██║███████║██╔██╗ ██║ \n";
	wcout << L"██╔══██╗██║   ██║██║╚██╔╝██║██╔══██╗██║╚██╔╝██║██╔══██║██║╚██╗██║ \n";
	wcout << L"██████╔╝╚██████╔╝██║ ╚═╝ ██║██████╔╝██║ ╚═╝ ██║██║  ██║██║ ╚████║ \n";
	wcout << L"╚═════╝  ╚═════╝ ╚═╝     ╚═╝╚═════╝ ╚═╝     ╚═╝╚═╝  ╚═╝╚═╝  ╚═══╝ \n";

	int curMode = _setmode(_fileno(stdout), _O_TEXT);
}

void MenuSelectCursor()
{
	if (GetAsyncKeyState(VK_UP) & 0x8000) (cursorY - 1) % 3;
	if (GetAsyncKeyState(VK_DOWN) & 0x8000) (cursorY + 1) % 3;

	Go2xy(29, 12 + cursorY);
	cout << '>';
}