// Second.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Second.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

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
	LoadStringW(hInstance, IDC_SECOND, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SECOND));

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
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SECOND));
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

	WM_WINDOW_INTERCONNECTION = RegisterWindowMessage(L"WM_WINDOW_INTERCOONECTION");

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
	RECT rc;
	HWND hServer;
	PCOPYDATASTRUCT pMyDS;
	static DRAWING_PROPERTIES dp;
	static INT x, y;

	switch (message)
	{
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
		if (dp.draw) {
			SelectObject(hdc, GetStockObject(DC_BRUSH));
			switch (dp.cl)
			{
			case color::Red:
				SetDCBrushColor(hdc, RGB(255, 0, 0));
				break;
			case color::Green:
				SetDCBrushColor(hdc, RGB(0, 255, 0));
				break;
			case color::Blue:
				SetDCBrushColor(hdc, RGB(0, 0, 255));
				break;
			default:
				break;
			}
			switch (dp.fg)
			{
			case figure::Square:
				Rectangle(hdc, x, y, x + 100, y + 100);
				break;
			case figure::Rhombus: {
				POINT pt[] = { { x - 50, y }, { x , y + 50 }, { x + 50, y } , { x , y - 50 } , { x - 50, y } };
				Polygon(hdc, pt, 5);
				break;
			}
			case figure::Circus:
				Ellipse(hdc, x, y, x + 100, y + 100);
				break;
			case figure::Star:
				POINT pts[11];
				pts[0] = { x - 50, y - 10 };
				pts[1] = { x - 15, y - 10 };
				pts[2] = { x, y - 50 };
				pts[3] = { x + 15, y - 10 };
				pts[4] = { x + 50, y - 10 };
				pts[5] = { x + 18, y + 10 };
				pts[6] = { x + 40, y + 50 };
				pts[7] = { x, y + 30 };
				pts[8] = { x - 40, y + 50 };
				pts[9] = { x - 18, y + 10 };
				pts[10] = { x - 50, y - 10 };
				Polygon(hdc, pts, 11);
				break;
			default:
				break;
			}
		}
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_LBUTTONUP:
		x = LOWORD(lParam);
		y = HIWORD(lParam);
		hServer = FindWindow(NULL, L"First");
		if (!hServer) {
			MessageBox(hWnd, L"Can't locate another window", L"Second", MB_OK);
			break;
		}
		SendMessage(hServer, WM_WINDOW_INTERCONNECTION, (WPARAM)hWnd, 0L);  // send message to copy data
		break;
	case WM_COPYDATA:
	{
		GetClientRect(hWnd, &rc);
		pMyDS = (PCOPYDATASTRUCT)lParam;
		dp = *(DRAWING_PROPERTIES*)(pMyDS->lpData);
		if (dp.draw)
			InvalidateRect(hWnd, &rc, TRUE);
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
