// 헤더파일
#include "framework.h"
#include "WindowsProject.h"

// 디파인
#define MAX_LOADSTRING 100

HINSTANCE hInst; // 현재 인스턴스핸들 전역변수
WCHAR szTitle[MAX_LOADSTRING]; // 윈도우 제목
WCHAR szWindowClass[MAX_LOADSTRING]; // 기본 윈도우 클래스 이름

// 함수 전방 선언
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

// 윈도우 앱이 실행되는 메인 함수
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    // UNREFERENCED_PARAMETER => 미리 사용하지 않겠다고 알리는 매크로
    UNREFERENCED_PARAMETER(hPrevInstance); // hPrevInstance 는 구 버전에서만 사용되었음. 호환성 때문에 존재
    UNREFERENCED_PARAMETER(lpCmdLine); // cmd에서 프로그램을 구동시켰을 때 전달받는 문자열. 이 역시 사용하지 않음

    // 전역 문자열 초기화
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING); // 제목 초기화
    LoadStringW(hInstance, IDC_WINDOWSPROJECT, szWindowClass, MAX_LOADSTRING); // 윈도우 클래스 이름 초기화

    MyRegisterClass(hInstance); // 윈도우 클래스 등록

    // 윈도우 생성
    if (!InitInstance (hInstance, nCmdShow)) // 윈도우 생성이 실패하면
    {
        return FALSE; // false 반환
    }

    // 단축키 등록
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT));

    MSG msg; // 메세지 객체 생성

    // 메세지 루프
    while (GetMessage(&msg, nullptr, 0, 0)) // 메세지 큐에서 메세지 읽기
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) // 단축키 검사
        {
            TranslateMessage(&msg); // 키보드 입력 해석
            DispatchMessage(&msg); // 메세지를 처리하는 WndProc함수에 메세지 전달
        }
    }

    return (int) msg.wParam;
}

// 윈도우 클래스를 등록하는 함수
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex; // 윈도우 정보를 담고 있는 구조체

    wcex.cbSize = sizeof(WNDCLASSEX); // 구조체의 크기

    wcex.style          = CS_HREDRAW | CS_VREDRAW;  // 윈도우 출력 스타일. 
                                                    // CS_HREDRAW => 윈도우 가로 길이가 바뀌었을 때 다시 그린다
                                                    // CS_VREDRAW => 윈도우 세로 길이가 바뀌었을 때 다시 그린다

    wcex.lpfnWndProc    = WndProc;                  // 메세지 처리하는 함수 포인터
    wcex.cbClsExtra     = 0;                        // 클래스 여분 메모리
    wcex.cbWndExtra     = 0;                        // 윈도우 여분 메모리
    wcex.hInstance      = hInstance;                // 윈도우 인스턴스
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT)); // 아이콘
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);                           // 커서
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);                                 // 배경 색
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT);                     // 메뉴 이름 (nullptr로 할당하여 없앨 수 있음)
    wcex.lpszClassName  = szWindowClass;                                            // 클래스 이름
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));     // 작은 아이콘

    return RegisterClassExW(&wcex); // 윈도우 클래스 등록
}

// 인스턴스 핸들을 생성하는 함수
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   HWND hWnd = CreateWindowW(
       szWindowClass,       // 윈도우 클래스 이름
       szTitle,             // 윈도우 제목
       WS_OVERLAPPEDWINDOW, // 윈도우 스타일
       CW_USEDEFAULT, 0,    // 윈도우 생성 x, y 좌표
       CW_USEDEFAULT, 0,    // 윈도우 가로, 세로 사이즈
       nullptr,             // 부모 윈도우
       nullptr,             // 메뉴 핸들
       hInstance,           // 현재 인스턴스 핸들
       nullptr              // 윈도우를 생성할 때 넘길 데이터
   );

   if (!hWnd) // 윈도우 핸들 생성에 실패헀다면
   {
      return FALSE; // false 반환
   }

   ShowWindow(hWnd, nCmdShow); // 윈도우 창 띄우기
   UpdateWindow(hWnd); // 윈도우 창 업데이트

   return TRUE; // 성공적으로 생성됨을 알림
}

// 메세지 처리 함수
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message) // 메세지에 대하여 switch
    {
    case WM_COMMAND: // 대화상자, 버튼, 단축기, 메뉴 등을 선택했을 때 호출되는 메세지
        {
            int wmId = LOWORD(wParam);

            // 메뉴에 대해서 처리
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT: // 화면 드로우 요청 메세지
        {
            PAINTSTRUCT ps; // 화면에 그리기 위한 정보를 담고 있는 구조체
            HDC hdc = BeginPaint(hWnd, &ps); // 출력에 필요한 정보를 담고있는 구조체(Device Context) 핸들
            

            
            EndPaint(hWnd, &ps); // 드로우가 끝났음을 알리고 리소스 반환
        }
        break;
    case WM_DESTROY: // 윈도우가 파괴될 때 발생하는 메세지
        PostQuitMessage(0); // WM_QUIT 메세지 발생
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam); // 처리되지 않은 메세지 디폴트 처리
    }
    return 0;
}

// 정보 창을 띄우는 함수
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
