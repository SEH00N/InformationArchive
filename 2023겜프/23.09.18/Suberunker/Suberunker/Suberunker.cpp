#include "framework.h"
#include "Suberunker.h"
#include <vector>
#include <time.h>

#define MAX_LOADSTRING 100
#define RECT_RENDER(posx, posy, scalex, scaley) Rectangle(hdc, posx - scalex / 2, posy - scaley / 2, posx + scalex / 2, posy + scaley / 2)
#define RECT_MAKE(posx, posy, scalex, scaley) { posx - scalex / 2, posy - scaley / 2, posx + scalex / 2, posy + scaley / 2 }

#define WINSIZEX 1280
#define WINSIZEY 720


typedef struct tObjInfo {
    POINT pos;
    POINT scale;
} Obj, *pObj;

enum class MoveDir {
    Idle,
    Left,
    Right,
    Up,
    Down
};

HINSTANCE hInst;
WCHAR szTitle[MAX_LOADSTRING];
WCHAR szWindowClass[MAX_LOADSTRING];

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_SUBERUNKER, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SUBERUNKER));

    MSG msg;

    //while (true)
    //{
    //    if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
    //    {
    //        if (msg.message == WM_QUIT)
    //            break;

    //        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
    //        {
    //            TranslateMessage(&msg);
    //            DispatchMessage(&msg);
    //        }
    //    }
    //    else
    //    {

    //    }
    //}


    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SUBERUNKER));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_SUBERUNKER);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance;

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, WINSIZEX, WINSIZEY, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static tObjInfo Player = { {WINSIZEX / 2, WINSIZEY - 110}, {100, 100} };
    static std::vector<tObjInfo> vecObj;
    //static tObjInfo Object = { {500, 100}, {100, 100} };
    static MoveDir MoveDir = MoveDir::Idle;
    static float MoveSpeed = 20.0f;
    static int delay = 0, score = 0;

    switch (message)
    {
    case WM_CREATE:
        srand((unsigned int)time(nullptr));
        SetTimer(hWnd, 1, 10, nullptr); // 0.01초마다 한 번
        break;
    case WM_TIMER:
    {
        if (delay >= 50)
        {
            tObjInfo temp;
            temp.pos = { rand() % WINSIZEX, 0 };
            temp.scale = { 50, 50 };
            vecObj.push_back(temp);

            delay = rand() % 50;
        }
        else
            ++delay;

        RECT tempRT, playerRT, objRT;

        for (size_t i = 0; i < vecObj.size();)
        {
            vecObj[i].pos.y += MoveSpeed / 2;
            
            playerRT = RECT_MAKE(Player.pos.x, Player.pos.y, Player.scale.x, Player.scale.y);
            objRT = RECT_MAKE(vecObj[i].pos.x, vecObj[i].pos.y, vecObj[i].scale.x, vecObj[i].scale.y);

            if (vecObj[i].pos.y > WINSIZEY || IntersectRect(&tempRT, &playerRT, &objRT))
            {
                vecObj.erase(vecObj.begin() + i);
                ++score;
            }
            else
                ++i;
        }

		InvalidateRect(hWnd, nullptr, true);
    }
        break;
    case WM_KEYDOWN:
        switch (wParam)
        {
        case 'A':
        case VK_LEFT:
            Player.pos.x -= MoveSpeed;
            break;
        case 'D':
        case VK_RIGHT:
            Player.pos.x += MoveSpeed;
            break;
        }

        InvalidateRect(hWnd, nullptr, true);
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);

            wchar_t scoreBuffer[32];
            _itow_s(score, scoreBuffer, 10);

            TextOut(hdc, 10, 10, scoreBuffer, wcslen(scoreBuffer));

            RECT_RENDER(Player.pos.x, Player.pos.y, Player.scale.x, Player.scale.y);

            for (size_t i = 0; i < vecObj.size(); ++i)
                RECT_RENDER(vecObj[i].pos.x, vecObj[i].pos.y, vecObj[i].scale.x, vecObj[i].scale.y);
            
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}