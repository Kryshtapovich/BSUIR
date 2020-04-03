#include "stdafx.h"
#include "Lab8.h"
#include <TlHelp32.h>
#include <windowsx.h>

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

HMENU hPopupMenu;

#define N 500

int procCount = 0;
PROCESSENTRY32 procs[N];

int moduleCount = 0;
MODULEENTRY32 modules[N];

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPTSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_LAB8, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB8));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
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
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB8));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

#define LISTBOX1_ID 1001
#define LISTBOX2_ID 1002

void ClearListBox(HWND listBox) {
	while (SendMessage(listBox, LB_GETCOUNT, 0, NULL))
		SendMessage(listBox, LB_DELETESTRING, 0, NULL);
}

void ShowProcs(HWND listBox)
{
	procCount = 0;
	procs[0].dwSize = sizeof(PROCESSENTRY32);

	HANDLE toolHelp = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	bool result = Process32First(toolHelp, &procs[0]);
	while (result)
	{
		procCount++;
		procs[procCount].dwSize = sizeof(PROCESSENTRY32);
		result = Process32Next(toolHelp, &procs[procCount]);
	}
	CloseHandle(toolHelp);

	ClearListBox(listBox);
	for (int i = 0; i < procCount; i++)
		SendMessage(listBox, LB_ADDSTRING, 0, (LPARAM)procs[i].szExeFile);
}

void GetModuleListByPID(DWORD pid, HWND listBox)
{
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pid);
	if (snapshot != INVALID_HANDLE_VALUE)
	{
		MODULEENTRY32 module;
		module.dwSize = sizeof(MODULEENTRY32);
		Module32First(snapshot, &module);

		do {
			SendMessage(listBox, LB_ADDSTRING, 0, (LPARAM)module.szModule);
		} while (Module32Next(snapshot, &module));// find it
	}

	CloseHandle(snapshot);
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
	HWND hWnd;

	hInst = hInstance; // Store instance handle in our global variable

	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, 600, 600, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

#define ID_IDLE 10
#define ID_NORMAL 11
#define ID_HIGH 12
#define ID_REAL_TIME 13

void SetPriority(DWORD priorityClass, HWND listBox) {
	int itemId = SendMessage(listBox, LB_GETCURSEL, 0, NULL);
	if (itemId != -1) {
		HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procs[itemId].th32ProcessID);
		SetPriorityClass(hProcess, priorityClass);
		CloseHandle(hProcess);
	}
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	static HWND listBox1, listBox2;

	switch (message)
	{
	case WM_CREATE:
	{
		listBox1 = CreateWindow(L"LISTBOX", L"Processes", WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | LBS_NOTIFY,
			20, 20, 250, 500, hWnd, (HMENU)LISTBOX1_ID, hInst, NULL);
		listBox2 = CreateWindow(L"LISTBOX", L"Modules", WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL,
			300, 20, 250, 500, hWnd, (HMENU)LISTBOX2_ID, hInst, NULL);

		ShowProcs(listBox1);
	}
	break;
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case LISTBOX1_ID:
			if (wmEvent == LBN_SELCHANGE)
			{
				int itemId = SendMessage(listBox1, LB_GETCURSEL, 0, NULL);
				if (itemId != -1) {
					SendMessage(listBox2, LB_RESETCONTENT, 0, NULL);
					GetModuleListByPID(procs[itemId].th32ProcessID, listBox2);
				}
			}
			break;
		case ID_IDLE:
			SetPriority(IDLE_PRIORITY_CLASS, listBox1);
			break;
		case ID_NORMAL:
			SetPriority(NORMAL_PRIORITY_CLASS, listBox1);
			break;
		case ID_HIGH:
			SetPriority(HIGH_PRIORITY_CLASS, listBox1);
			break;
		case ID_REAL_TIME:
			SetPriority(REALTIME_PRIORITY_CLASS, listBox1);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_CONTEXTMENU:
		if ((HWND)wParam == listBox1) {
			int itemId = SendMessage(listBox1, LB_GETCURSEL, 0, NULL);
			if (itemId != -1) {
				HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procs[itemId].th32ProcessID);
				int pC = GetPriorityClass(hProcess);
				CloseHandle(hProcess);

				hPopupMenu = CreatePopupMenu();
				AppendMenu(hPopupMenu, pC == IDLE_PRIORITY_CLASS ? MF_CHECKED : MF_STRING, ID_IDLE, L"Idle");
				AppendMenu(hPopupMenu, pC == NORMAL_PRIORITY_CLASS ? MF_CHECKED : MF_STRING, ID_NORMAL, L"Normal");
				AppendMenu(hPopupMenu, pC == HIGH_PRIORITY_CLASS ? MF_CHECKED : MF_STRING, ID_HIGH, L"High");
				AppendMenu(hPopupMenu, pC == REALTIME_PRIORITY_CLASS ? MF_CHECKED : MF_STRING, ID_REAL_TIME, L"Real time");
				TrackPopupMenu(hPopupMenu, TPM_TOPALIGN | TPM_LEFTALIGN, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), 0, hWnd, NULL);
			}
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}