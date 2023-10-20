#include "pch.h"
#include "BaseWindow.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    BaseWindow game({WINDOW_WIDTH, WINDOW_HEIGHT});
    game.Run(hInstance, nCmdShow);
}