// Lab4.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Lab4.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name


typedef struct _object {
    HBITMAP hBitmap;
    int x;
    int y;
}OBJECT;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
void DrawBitmap(HDC, int, int, HBITMAP);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_LAB4, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB4));

    MSG msg;

    // Main message loop:
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



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB4));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = NULL;
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

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

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//

int current = 0;

HBITMAP next(HBITMAP* stages) {
    if (current == 10) current = 0;
    else current++;
    return stages[current];
}

HBITMAP prev(HBITMAP* stages) {
    if (current == -1) current = 10;
    else current--;
    return stages[current];
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    RECT rc;
    static HBITMAP hStages[10];
    static OBJECT  obj;
    static WORD destX, destY;
    HDC hdc;
    switch (message)
    {
    case WM_CREATE:
    {   
        hStages[0] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP1));
        hStages[1] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP2));
        hStages[2] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP3));
        hStages[3] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP4));
        hStages[4] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP5));
        hStages[5] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP6));
        hStages[6] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP7));
        hStages[7] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP8));
        hStages[8] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP9));
        hStages[9] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP10));
    
        obj = { hStages[0], 100, 100 };
    }
    break;
    case WM_COMMAND:
        break;
    case WM_TIMER:
    {
        GetClientRect(hWnd, &rc);
        if (destX == obj.x && obj.y == destY) {
            KillTimer(hWnd, 1);
            InvalidateRect(hWnd, &rc, TRUE);
            break;
        }
        if (destX < obj.x) {
            obj.hBitmap = prev(hStages);
            obj.x--;
        }
        else if (destX > obj.x) {
            obj.hBitmap = next(hStages);
            obj.x++;
        }
        else {
            if (destY < obj.y) {
                obj.y--;
                obj.hBitmap = prev(hStages);
            }
            if (destY > obj.y) {
                obj.y++;
                obj.hBitmap = next(hStages);
            }
        }
        InvalidateRect(hWnd, &rc, TRUE);
    }
        break;
    case WM_LBUTTONUP:
        destX = LOWORD(lParam);
        destY = HIWORD(lParam);
        SetTimer(hWnd, 1, 20, NULL);
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            DrawBitmap(hdc, obj.x, obj.y, obj.hBitmap);
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

void DrawBitmap(HDC hDC, int x, int y, HBITMAP hBitmap)
{
    HDC hMemDC =CreateCompatibleDC(hDC);
    HBITMAP hbm;
    HBITMAP hOldbm = (HBITMAP)SelectObject(hMemDC, hBitmap);
    BITMAP bm;
    POINT  ptSize, ptOrg;
    if (hOldbm)
    {
        SetMapMode(hMemDC, GetMapMode(hDC));
        GetObject(hBitmap, sizeof(BITMAP), (LPSTR)&bm);

        ptSize.x = bm.bmWidth;   
        ptSize.y = bm.bmHeight;  
        DPtoLP(hDC, &ptSize, 1);

        ptOrg.x = 0;
        ptOrg.y = 0;
        DPtoLP(hMemDC, &ptOrg, 1);
        BitBlt(hDC, x, y, ptSize.x, ptSize.y, hMemDC, ptOrg.x, ptOrg.y, SRCCOPY);
        SelectObject(hMemDC, hOldbm);
    }
    DeleteDC(hMemDC);
}
