// First.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "First.h"

#define MAX_LOADSTRING 100

#define RB_COLOR_RED      111
#define RB_COLOR_GREEN    112
#define RB_COLOR_BLUE     113

#define RB_FIGURE_RHOMBUS 121
#define RB_FIGURE_SQUARE  122
#define RB_FIGURE_CIRCUS  123
#define RB_FIGURE_STAR    124

#define CB_DRAW           211



// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

UINT WM_WINDOW_INTERCONNECTION;

enum color {
    Red,
    Green,
    Blue
};

enum figure {
    Rhombus,
    Square,
    Circus,
    Star
};

typedef struct _drawprops {
    color cl;
    figure fg;
    BOOL draw;
}DRAWING_PROPERTIES;


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
    LoadStringW(hInstance, IDC_FIRST, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);



    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_FIRST));

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



ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_FIRST));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = NULL;
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

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

   WM_WINDOW_INTERCONNECTION = RegisterWindowMessage(L"WM_WINDOW_INTERCOONECTION");

   return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    COPYDATASTRUCT myDS;

    DRAWING_PROPERTIES dp;

    HWND hServer;

    static HWND rbRed;
    static HWND rbGreen;
    static HWND rbBlue;

    static HWND rbRhombus;
    static HWND rbSquare;
    static HWND rbCircus;
    static HWND rbStar;

    static HWND cbDraw;

    if (message == WM_WINDOW_INTERCONNECTION) {
        hServer = FindWindow(NULL, L"Second");
        if (!hServer) {
            MessageBox(hWnd, L"Can't locate another window", L"First", MB_OK);
            return 0;
        }
        if (SendMessage(rbRed, BM_GETCHECK, 0, 0L) == BST_CHECKED) {
            dp.cl = color::Red;
        }
        else if (SendMessage(rbGreen, BM_GETCHECK, 0, 0L) == BST_CHECKED) {
            dp.cl = color::Green;
        }
        else if (SendMessage(rbBlue, BM_GETCHECK, 0, 0L) == BST_CHECKED) {
            dp.cl = color::Blue;
        }
        if (SendMessage(rbRhombus, BM_GETCHECK, 0, 0L) == BST_CHECKED) {
            dp.fg = figure::Rhombus;
        }
        else if (SendMessage(rbSquare, BM_GETCHECK, 0, 0L) == BST_CHECKED) {
            dp.fg = figure::Square;
        }
        else if (SendMessage(rbCircus, BM_GETCHECK, 0, 0L) == BST_CHECKED) {
            dp.fg = figure::Circus;
        }
        else if (SendMessage(rbStar, BM_GETCHECK, 0, 0L) == BST_CHECKED) {
            dp.fg = figure::Star;
        }
        if (SendMessage(cbDraw, BM_GETCHECK, 0, 0L) == BST_CHECKED)
            dp.draw = TRUE;
        else dp.draw = FALSE;

        myDS.dwData = 1;
        myDS.cbData = sizeof(DRAWING_PROPERTIES);
        myDS.lpData = &dp;
        SendMessage(hServer, WM_COPYDATA, (WPARAM)hWnd, (LPARAM)(LPVOID)&myDS);
        return 0;
    }

    switch (message)
    {

    case WM_CREATE:
    {
        rbRed = CreateWindow(L"button", L"RED", WS_CHILD |
            WS_VISIBLE | BS_AUTORADIOBUTTON | BS_LEFTTEXT
            | WS_GROUP | WS_TABSTOP,
            50, 100, 70, 50, hWnd, (HMENU)RB_COLOR_RED, hInst, NULL);
        rbGreen = CreateWindow(L"button", L"GREEN", WS_CHILD |
            WS_VISIBLE | BS_AUTORADIOBUTTON | BS_LEFTTEXT,
            50, 150, 70, 50, hWnd, (HMENU)RB_COLOR_GREEN, hInst, NULL);
        rbBlue = CreateWindow(L"button", L"BLUE", WS_CHILD |
            WS_VISIBLE | BS_AUTORADIOBUTTON | BS_LEFTTEXT,
            50, 200, 70, 50, hWnd, (HMENU)RB_COLOR_BLUE, hInst, NULL);

        rbRhombus = CreateWindow(L"button", L"RHOMBUS", WS_CHILD |
            WS_VISIBLE | BS_AUTORADIOBUTTON | BS_LEFTTEXT |
            WS_GROUP | WS_TABSTOP,
            150, 100, 100, 50, hWnd, (HMENU)RB_FIGURE_RHOMBUS, hInst, NULL);
        rbSquare = CreateWindow(L"button", L"SQUARE", WS_CHILD |
            WS_VISIBLE | BS_AUTORADIOBUTTON | BS_LEFTTEXT,
            150, 150, 100, 50, hWnd, (HMENU)RB_FIGURE_SQUARE, hInst, NULL);
        rbCircus = CreateWindow(L"button", L"CIRCLE", WS_CHILD |
            WS_VISIBLE | BS_AUTORADIOBUTTON | BS_LEFTTEXT,
            150, 200, 100, 50, hWnd, (HMENU)RB_FIGURE_CIRCUS, hInst, NULL);
        rbStar = CreateWindow(L"button", L"STAR", WS_CHILD |
            WS_VISIBLE | BS_AUTORADIOBUTTON | BS_LEFTTEXT,
            150, 250, 100, 50, hWnd, (HMENU)RB_FIGURE_STAR, hInst, NULL);

        cbDraw = CreateWindow(L"button", L"DRAW", WS_CHILD |
            WS_VISIBLE | BS_AUTOCHECKBOX | BS_LEFTTEXT,
            50, 250, 70, 50, hWnd, (HMENU)CB_DRAW, hInst, NULL);
    }
        break;        
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
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
