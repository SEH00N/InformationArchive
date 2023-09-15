// ChasingGamee.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "ChasingGamee.h"
#include <string>

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

const double LimitFrameRate = 1 / (double)60;
UINT64 lastFrequency = 0;
UINT64 period = 0;
double frameElapsed = 0;
HWND handleWindow;

float speed = 5;

bool mouseClicked = false;
RECT ggmBound = { 100, 100, 200, 150 };
RECT myBound = { 0, 0, 0, 0 };
POINT boundSize = { 100, 50 };
LPCWSTR ggmStr = L"겜마고";
LPCWSTR myStr = L"SEH00N";

void Update(float dt);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_CHASINGGAMEE, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CHASINGGAMEE));

    MSG msg;

    while (true)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
                break;

            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            UINT64 currentFrequency = 0;
            ::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&currentFrequency));

            double deltaTime = (currentFrequency - lastFrequency) / static_cast<double>(period);
            lastFrequency = currentFrequency;
            frameElapsed += deltaTime;

            if (frameElapsed >= LimitFrameRate)
            {
                Update(frameElapsed);
                frameElapsed = 0;
            }
            // something task kind of rendering
        }
    }

    return (int) msg.wParam;
}

void Update(float dt)
{
    if (mouseClicked)
    {
        POINT myPos = { myBound.left, myBound.top };
        POINT ggmPos = { ggmBound.left, ggmBound.top };

        POINT dirVector = { myPos.x - ggmPos.x, myPos.y - ggmPos.y };
        float magnitude = sqrt(dirVector.x * dirVector.x + dirVector.y * dirVector.y);

        if (magnitude > 0.1)
		{
			dirVector.x = round(dirVector.x / magnitude);
			dirVector.y = round(dirVector.y / magnitude);

            ggmPos.x += dirVector.x * speed * ceil(dt);
            ggmPos.y += dirVector.y * speed * ceil(dt);

            ggmBound.left = ggmPos.x;
            ggmBound.right = ggmBound.left + boundSize.x;
            ggmBound.top = ggmPos.y;
            ggmBound.bottom = ggmBound.top + boundSize.y;

            InvalidateRect(handleWindow, nullptr, true);
        }
    }
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CHASINGGAMEE));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = nullptr; // MAKEINTRESOURCEW(IDC_CHASINGGAMEE);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

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
    switch (message)
    {
    case WM_CREATE:
        handleWindow = hWnd;
        ::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&lastFrequency));
        ::QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&period));
        mouseClicked = false;
        break;
    case WM_LBUTTONDOWN:
    {
        myBound.left = LOWORD(lParam);
        myBound.top = HIWORD(lParam);
        myBound.right = myBound.left + boundSize.x;
        myBound.bottom = myBound.top + boundSize.y;

        mouseClicked = true;
        InvalidateRect(hWnd, nullptr, true);
    }
        break;
    case WM_LBUTTONUP:
        mouseClicked = false;
        InvalidateRect(hWnd, nullptr, true);
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);

            DrawText(hdc, ggmStr, _tcslen(ggmStr), &ggmBound, DT_TOP | DT_LEFT);

            if (mouseClicked)
            {
                DrawText(hdc, myStr, _tcslen(myStr), &myBound, DT_TOP | DT_LEFT);
            }

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