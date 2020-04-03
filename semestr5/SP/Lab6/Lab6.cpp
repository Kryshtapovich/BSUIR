// Lab6.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Lab6.h"
#include <ctime>

#define MAX_LOADSTRING 100

#define IDB_START 1
#define IDB_STOP 2

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

DWORD THREAD_ID_1;
DWORD THREAD_ID_2;
DWORD THREAD_ID_3;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

DWORD   CALLBACK    drawRectangle(LPVOID*);

typedef struct _params {
	HWND hWnd;
	unsigned int seed;
}PARAMS;

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
	LoadStringW(hInstance, IDC_LAB6, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB6));

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

	return (int)msg.wParam;
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

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB6));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HWND hStart;
	static HWND hStop;

	static HANDLE hThread1;
	static HANDLE hThread2;
	static HANDLE hThread3;

	switch (message)
	{
	case WM_CREATE:
	{
		hStart = CreateWindow(L"button", L"Start",
			WS_CHILD | WS_VISIBLE |
			BS_PUSHBUTTON,
			100, 100, 200, 50, hWnd, (HMENU)IDB_START, hInst, NULL);
		hStop = CreateWindow(L"button", L"Stop",
			WS_CHILD | WS_VISIBLE |
			BS_PUSHBUTTON,
			700, 100, 200, 50, hWnd, (HMENU)IDB_STOP, hInst, NULL);
		PARAMS* p1 = new PARAMS{ hWnd, static_cast<unsigned int>(100) };
		PARAMS* p2 = new PARAMS{ hWnd, static_cast<unsigned int>(200) };
		PARAMS* p3 = new PARAMS{ hWnd, static_cast<unsigned int>(300) };
		hThread1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)drawRectangle, (LPVOID*)p1, CREATE_SUSPENDED, (LPDWORD)&THREAD_ID_1);
		hThread2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)drawRectangle, (LPVOID*)p2, CREATE_SUSPENDED, (LPDWORD)&THREAD_ID_2);
		hThread3 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)drawRectangle, (LPVOID*)p3, CREATE_SUSPENDED, (LPDWORD)&THREAD_ID_3);
	}
	break;
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDB_START:
			ResumeThread(hThread1);
			ResumeThread(hThread2);
			ResumeThread(hThread3);
			break;
		case IDB_STOP:
			SuspendThread(hThread1);
			SuspendThread(hThread2);
			SuspendThread(hThread3);
			break;
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

DWORD CALLBACK drawRectangle(LPVOID* data) {
	PARAMS* pr = (PARAMS*)data;
	HWND hWnd = pr->hWnd;
	unsigned int seed = pr->seed;
	srand(seed);
	while (TRUE) {
		RECT rc;
		GetClientRect(hWnd, &rc);
		INT width = rc.right - rc.left;
		INT height = rc.bottom - rc.top;
		INT x = rand() % width;
		INT y = rand() % height;
		RECT myRC = { x, y, x + 100, y + 100 };
		HDC hdc = GetWindowDC(hWnd);
		Rectangle(hdc, x, y, x + 100, y + 100);
		Sleep(500);
		SelectObject(hdc, GetStockObject(DC_PEN));
		SetDCPenColor(hdc, RGB(255, 255, 255));
		SelectObject(hdc, GetStockObject(DC_BRUSH));
		SetDCBrushColor(hdc, RGB(255, 255, 255));
		Rectangle(hdc, x, y, x + 100, y + 100);
		InvalidateRect(hWnd, &rc, TRUE);
		Sleep(500);
	}
	delete pr;
	return 0;
}