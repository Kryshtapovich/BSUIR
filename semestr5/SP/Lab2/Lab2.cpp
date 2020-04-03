// Lab2.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Lab2.h"

#define MAX_LOADSTRING 100

// CONTROL ITEMS

#define ID_LIST_LEFT 1
#define ID_LIST_RIGHT 2
#define ID_ADD 3
#define ID_CLEAR 4
#define ID_TO_RIGHT 5
#define ID_DELETE 6
#define ID_EDIT 7


// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
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

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_LAB2, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB2));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB2));
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
      CW_USEDEFAULT, 0, 700, 525, nullptr, nullptr, hInstance, nullptr);

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
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;
    RECT rc;

    static HWND hLeftListBox;
    static HWND hRightListBox;
    static HWND hAddButton;
    static HWND hClearButton;
    static HWND hToRightButton;
    static HWND hDeleteButton;
    static HWND hEdit;

    switch (message)
    {
    case WM_CREATE:
    {
        GetClientRect(hWnd, &rc);
        hLeftListBox = CreateWindow(L"listbox", NULL,
            WS_CHILD | WS_VISIBLE | LBS_STANDARD |
            LBS_WANTKEYBOARDINPUT,
            rc.left + 30, 30, 200, 400,
            hWnd, (HMENU)ID_LIST_LEFT, hInst, NULL);

        hRightListBox = CreateWindow(L"listbox", NULL,
            WS_CHILD | WS_VISIBLE | LBS_STANDARD |
            LBS_WANTKEYBOARDINPUT,
            rc.left + 430, 30, 200, 400,
            hWnd, (HMENU)ID_LIST_RIGHT, hInst, NULL);

        hAddButton = CreateWindow(L"button", L"Add",
            WS_CHILD | WS_VISIBLE |
            BS_PUSHBUTTON,
            250, 30, 100, 30,
            hWnd, (HMENU)ID_ADD, hInst, NULL);

        hClearButton = CreateWindow(L"button", L"Clear",
            WS_CHILD | WS_VISIBLE |
            BS_PUSHBUTTON,
            250, 80, 100, 30,
            hWnd, (HMENU)ID_CLEAR, hInst, NULL);

        hToRightButton = CreateWindow(L"button", L"To Right",
            WS_CHILD | WS_VISIBLE |
            BS_PUSHBUTTON,
            250, 130, 100, 30,
            hWnd, (HMENU)ID_TO_RIGHT, hInst, NULL);

        hDeleteButton = CreateWindow(L"button", L"Delete",
            WS_CHILD | WS_VISIBLE |
            BS_PUSHBUTTON,
            250, 180, 100, 30,
            hWnd, (HMENU)ID_DELETE, hInst, NULL);

        hEdit = CreateWindow(L"edit", NULL,
            WS_CHILD | WS_VISIBLE | WS_BORDER |
            ES_LEFT,
            30, 430, 300, 30,
            hWnd, (HMENU)ID_EDIT, hInst, NULL);
    }
    break;
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // Parse the menu selections:
        switch (wmId)
        {
        case ID_ADD:
            TCHAR chBuff[80];
            WORD cbText;

            cbText = SendMessage(hEdit, EM_GETLINE, 0,
                (LPARAM)(LPSTR)chBuff);

            chBuff[cbText] = '\0';
            if(SendMessage(hLeftListBox, LB_FINDSTRINGEXACT, 0, (LPARAM)(LPSTR)chBuff) == LB_ERR)
                SendMessage(hLeftListBox, LB_ADDSTRING, 0, (LPARAM)(LPSTR)chBuff);
            break;
        case ID_CLEAR:
            SendMessage(hLeftListBox, LB_RESETCONTENT, 0, 0L);
            SendMessage(hRightListBox, LB_RESETCONTENT, 0, 0L);
            break;
        case ID_TO_RIGHT:
            INT pos;

            pos = SendMessage(hLeftListBox, LB_GETCURSEL, 0, 0L);
            if (pos == LB_ERR)
                break;

            *(WORD*)chBuff = sizeof(chBuff) - 1;

            SendMessage(hLeftListBox, LB_GETTEXT, (WPARAM)pos, (LPARAM)(LPSTR)chBuff);
            if (SendMessage(hRightListBox, LB_FINDSTRINGEXACT, 0, (LPARAM)(LPSTR)chBuff) == LB_ERR)
                SendMessage(hRightListBox, LB_ADDSTRING, 0, (LPARAM)(LPSTR)chBuff);
            break;
        case ID_DELETE:
            pos = SendMessage(hLeftListBox, LB_GETCURSEL, 0, 0L);
            if (pos != LB_ERR) {
                SendMessage(hLeftListBox, LB_DELETESTRING, (WPARAM)pos, 0L);
            }
            pos = SendMessage(hRightListBox, LB_GETCURSEL, 0, 0L);
            if (pos != LB_ERR) {
                SendMessage(hRightListBox, LB_DELETESTRING, (WPARAM)pos, 0L);
            }
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
        break;
    case WM_PAINT:
        {
            hdc = BeginPaint(hWnd, &ps);
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
