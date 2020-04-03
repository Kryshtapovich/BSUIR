#include <windows.h>

enum Tools
{
	PENCIL = 10,
	LINE,
	COLOR,
	RECTANGLE,
	ELLIPSE,
	ERASER,
	CLEAR
};

enum Width
{
	WIDTH_1 = 1,
	WIDTH_2,
	WIDTH_3,
	WIDTH_4,
	WIDTH_5,
	WIDTH_6
};

class Painter
{
private:

	HDC drawingArea;
	HDC finalPicture;
	int* hdcWidth;
	int* hdcHeight;
	HPEN currentPen;
	DWORD currentColor;
	int currentPenWidth;
	POINT* points;

	void InitializeHDC(HWND hWnd)
	{
		HBITMAP bmFinalCopy;
		HBITMAP bmDrawingCopy;
		HBRUSH brush;
		HDC hdc;
		HBRUSH temp;

		brush = CreateSolidBrush(0xffffff);
		hdc = GetDC(hWnd);

		// Drawing HDC //
		drawingArea = CreateCompatibleDC(hdc);
		bmDrawingCopy = CreateCompatibleBitmap(hdc, *hdcWidth, *hdcHeight);
		SelectObject(drawingArea, bmDrawingCopy);
		temp = (HBRUSH)SelectObject(drawingArea, brush);
		DeleteObject(temp);
		PatBlt(drawingArea, 0, 0, *hdcWidth, *hdcHeight, PATCOPY);

		// Result HDC //
		finalPicture = CreateCompatibleDC(hdc);
		bmFinalCopy = CreateCompatibleBitmap(hdc, *hdcWidth, *hdcHeight);
		SelectObject(finalPicture, bmFinalCopy);
		temp = (HBRUSH)SelectObject(finalPicture, brush);
		DeleteObject(temp);
		PatBlt(finalPicture, 0, 0, *hdcWidth, *hdcHeight, PATCOPY);

		ReleaseDC(hWnd, hdc);
		DeleteObject(brush);
		DeleteObject(bmDrawingCopy);
		DeleteObject(bmFinalCopy);
		temp = (HBRUSH)SelectObject(drawingArea, GetStockObject(HOLLOW_BRUSH));
		DeleteObject(temp);
	}

	void SetPen()
	{
		HPEN temp;
		temp = (HPEN)SelectObject(drawingArea, currentPen);
		DeleteObject(temp);
		temp = (HPEN)SelectObject(finalPicture, currentPen);
		DeleteObject(temp);
	}

	BOOL Line(HDC hdc, int x1, int y1, int x2, int y2)
	{
		MoveToEx(hdc, x1, y1, NULL);
		return LineTo(hdc, x2, y2);
	}

public:

	Painter(HWND hWnd, int* hdcWidth, int* hdcHeight)
	{
		this->hdcHeight = hdcHeight;
		this->hdcWidth = hdcWidth;
		InitializeHDC(hWnd);
		currentPenWidth = WIDTH_2;
		currentColor = RGB(0, 0, 0);
	}

	void DrawPencil(HDC hdc, int x1, int y1, int x2, int y2)
	{
		currentPen = CreatePen(PS_SOLID, currentPenWidth, currentColor);
		SetPen();
		StretchBlt(drawingArea, 0, 0, *hdcWidth, *hdcHeight,
			finalPicture, 0, 0, *hdcWidth, *hdcHeight, SRCCOPY);

		Line(drawingArea, x1, y1, x2, y2);
		StretchBlt(hdc, 0, 0, *hdcWidth, *hdcHeight,
			drawingArea, 0, 0, *hdcWidth, *hdcHeight, SRCCOPY);

		StretchBlt(finalPicture, 0, 0, *hdcWidth, *hdcHeight,
			drawingArea, 0, 0, *hdcWidth, *hdcHeight, SRCCOPY);
	}

	void DrawLine(HDC hdc, int x1, int y1, int x2, int y2)
	{
		currentPen = CreatePen(PS_SOLID, currentPenWidth, currentColor);
		SetPen();
		StretchBlt(drawingArea, 0, 0, *hdcWidth, *hdcHeight,
			finalPicture, 0, 0, *hdcWidth, *hdcHeight, SRCCOPY);

		Line(drawingArea, x1, y1, x2, y2);
		StretchBlt(hdc, 0, 0, *hdcWidth, *hdcHeight,
			drawingArea, 0, 0, *hdcWidth, *hdcHeight, SRCCOPY);
	}

	void DrawEllipse(HDC hdc, int x1, int y1, int x2, int y2)
	{
		currentPen = CreatePen(PS_SOLID, currentPenWidth, currentColor);
		SetPen();
		StretchBlt(drawingArea, 0, 0, *hdcWidth, *hdcHeight,
			finalPicture, 0, 0, *hdcWidth, *hdcHeight, SRCCOPY);

		Ellipse(drawingArea, x1, y1, x2, y2);
		StretchBlt(hdc, 0, 0, *hdcWidth, *hdcHeight,
			drawingArea, 0, 0, *hdcWidth, *hdcHeight, SRCCOPY);
	}

	void DrawRectangle(HDC hdc, int x1, int y1, int x2, int y2)
	{
		currentPen = CreatePen(PS_SOLID, currentPenWidth, currentColor);
		SetPen();
		StretchBlt(drawingArea, 0, 0, *hdcWidth, *hdcHeight,
			finalPicture, 0, 0, *hdcWidth, *hdcHeight, SRCCOPY);

		Rectangle(drawingArea, x1, y1, x2, y2);
		StretchBlt(hdc, 0, 0, *hdcWidth, *hdcHeight,
			drawingArea, 0, 0, *hdcWidth, *hdcHeight, SRCCOPY);
	}

	void Erase(HDC hdc, int x1, int y1, int x2, int y2)
	{
		currentPen = CreatePen(PS_SOLID, currentPenWidth, RGB(255, 255, 255));
		SetPen();
		StretchBlt(drawingArea, 0, 0, *hdcWidth, *hdcHeight,
			finalPicture, 0, 0, *hdcWidth, *hdcHeight, SRCCOPY);

		Line(drawingArea, x1, y1, x2, y2);
		StretchBlt(hdc, 0, 0, *hdcWidth, *hdcHeight,
			drawingArea, 0, 0, *hdcWidth, *hdcHeight, SRCCOPY);

		StretchBlt(finalPicture, 0, 0, *hdcWidth, *hdcHeight,
			drawingArea, 0, 0, *hdcWidth, *hdcHeight, SRCCOPY);
	}

	void Clear(HWND hWnd)
	{
		RECT rect;
		GetClientRect(hWnd, &rect);
		FillRect(drawingArea, &rect, (HBRUSH)(COLOR_WINDOW + 1));
	}

	void EndDraw()
	{
		StretchBlt(finalPicture, 0, 0, *hdcWidth, *hdcHeight,
			drawingArea, 0, 0, *hdcWidth, *hdcHeight, SRCCOPY);
	}

	void SetColor(DWORD color)
	{	
		currentColor = color;
		HBRUSH tempBrush, deleteObj;
		tempBrush = CreateSolidBrush(color);
		deleteObj = (HBRUSH)SelectObject(drawingArea, tempBrush);
		DeleteObject(deleteObj);
	}

	void SetPenWidth(int penWidth)
	{
		currentPenWidth = penWidth;
		currentPen = CreatePen(PS_SOLID, currentPenWidth, currentColor);
		SetPen();
	}

	void OnClose()
	{
		DeleteObject(currentPen);
		DeleteObject(drawingArea);
		DeleteObject(finalPicture);
	}

	void UpdateWindow(HDC hdc)
	{
		StretchBlt(hdc, 0, 0, *hdcWidth, *hdcHeight,
			finalPicture, 0, 0, *hdcWidth, *hdcHeight, SRCCOPY);
	}
};

class Window
{
private:

	Painter* painter;
	POINT mousePosition;
	POINT previousMousePosition;
	POINT savedPosition;
	bool isNeedUpdateMousePos = true;
	bool isDrawing;
	UINT currentTool;
	int hdcWidth;
	int hdcHeight;

public:

	Window(HWND hWnd)
	{
		isDrawing = false;
		HDC hdc = GetDC(hWnd);
		hdcWidth = GetDeviceCaps(hdc, HORZRES);
		hdcHeight = GetDeviceCaps(hdc, VERTRES);
		ReleaseDC(hWnd, hdc);
		painter = new Painter(hWnd, &hdcWidth, &hdcHeight);
	}

	void SetMousePosition(HWND hWnd)
	{
		if (isNeedUpdateMousePos)
		{
			previousMousePosition = mousePosition;
		}
		GetCursorPos(&mousePosition);
		ScreenToClient(hWnd, &mousePosition);
	}

	void Draw(HDC hdc)
	{
		if (!isDrawing)
		{
			painter->UpdateWindow(hdc);
			return;
		}

		switch (currentTool)
		{
			case PENCIL:
			{
				painter->DrawPencil(hdc, mousePosition.x, mousePosition.y,
					previousMousePosition.x, previousMousePosition.y);
				break;
			}

			case LINE:
			{
				painter->DrawLine(hdc, mousePosition.x, mousePosition.y,
					previousMousePosition.x, previousMousePosition.y);
				break;
			}

			case RECTANGLE:
			{
				painter->DrawRectangle(hdc, mousePosition.x, mousePosition.y,
					previousMousePosition.x, previousMousePosition.y);
				break;
			}

			case ELLIPSE:
			{
				painter->DrawEllipse(hdc, mousePosition.x, mousePosition.y,
					previousMousePosition.x, previousMousePosition.y);
				break;
			}

			case ERASER:
			{	
				painter->Erase(hdc, mousePosition.x, mousePosition.y,
					previousMousePosition.x, previousMousePosition.y);
				break;
			}
		}
	}

	void ClearWindow(HWND hwnd)
	{
		painter->Clear(hwnd);
	}

	void SaveMousePosition(HWND hWnd)
	{
		GetCursorPos(&savedPosition);
		ScreenToClient(hWnd, &savedPosition);
	}

	void SetTool(UINT tool, HWND hWnd)
	{
		currentTool = tool;
		isNeedUpdateMousePos = (tool == PENCIL || tool == ERASER) ? true : false;
		SetMousePosition(hWnd);
		isDrawing = true;
	}

	void EndDraw(HWND hWnd)
	{
		painter->EndDraw();
		isDrawing = false;
		isNeedUpdateMousePos = true;
		SetMousePosition(hWnd);
	}

	bool IsDrawing()
	{
		return isDrawing;
	}

	void SetPenColor(DWORD color)
	{
		painter->SetColor(color);
	}

	void SetPenWidth(int penWidth)
	{
		painter->SetPenWidth(penWidth);
	}

	void OnClose()
	{
		painter->OnClose();
	}
};

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM); // message handler
void MenuCommand(HWND hWnd, WPARAM param, int tool);
void SetChoosenWidth(int choosenWidth);
void TrackMouse(HWND hwnd);
UINT CheckTool();
void SwitchColor(HWND hWnd, int tool);
void SetTool(int newTool, int tool);
HMENU toolsMenu;
HMENU penWidthMenu;
Window* window = NULL;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	TCHAR szClassName[] = L"MyClass";
	HWND hMainWindow;
	MSG msg;
	WNDCLASSEX wc;
	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = szClassName;
	wc.cbWndExtra = NULL;
	wc.cbClsExtra = NULL;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm = LoadIcon(NULL, IDI_WINLOGO);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.hInstance = hInstance;

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, L"Error", L"Class not found!", MB_OK);
		return NULL;
	}

	hMainWindow = CreateWindow(szClassName, L"LR7", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, NULL, CW_USEDEFAULT, NULL, NULL, NULL, hInstance, NULL);

	if (!hMainWindow)
	{
		MessageBox(NULL, L"Cannot create the class!", L"Error", MB_OK);
		return NULL;
	}

	ShowWindow(hMainWindow, nCmdShow);
	UpdateWindow(hMainWindow);

	while (GetMessage(&msg, NULL, NULL, NULL))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

void CreateMainMenu(HWND hWnd)
{
	HMENU hMenu = CreateMenu();
	HMENU colorMenu = CreateMenu();
	HMENU clearMenu = CreateMenu();

	toolsMenu = CreateMenu();
	AppendMenu(toolsMenu, MF_CHECKED, PENCIL, L"Pencil");
	AppendMenu(toolsMenu, MF_UNCHECKED, LINE, L"Line");
	AppendMenu(toolsMenu, MF_UNCHECKED, RECTANGLE, L"Rectangle");
	AppendMenu(toolsMenu, MF_UNCHECKED, ELLIPSE, L"Ellipse");
	AppendMenu(toolsMenu, MF_UNCHECKED, ERASER, L"Eraser");
	AppendMenu(hMenu, MF_POPUP, (UINT)toolsMenu, L"Tools");

	penWidthMenu = CreateMenu();
	AppendMenu(penWidthMenu, MF_UNCHECKED, WIDTH_1, L"1");
	AppendMenu(penWidthMenu, MF_CHECKED, WIDTH_2, L"2");
	AppendMenu(penWidthMenu, MF_UNCHECKED, WIDTH_3, L"3");
	AppendMenu(penWidthMenu, MF_UNCHECKED, WIDTH_4, L"4");
	AppendMenu(penWidthMenu, MF_UNCHECKED, WIDTH_5, L"5");
	AppendMenu(penWidthMenu, MF_UNCHECKED, WIDTH_6, L"6");
	AppendMenu(hMenu, MF_POPUP, (UINT)penWidthMenu, L"Width");

	AppendMenu(colorMenu, MF_STRING, COLOR, L"Choose Color");
	AppendMenu(hMenu, MF_POPUP, (UINT)colorMenu, L"Color");

	AppendMenu(clearMenu, MF_STRING, CLEAR, L"Clear Window");
	AppendMenu(hMenu, MF_POPUP, (UINT)clearMenu, L"Clear");
	SetMenu(hWnd, hMenu);
}

LRESULT WINAPI WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT paintStruct;
	static UINT tool;
	static int windowWidth;
	static int windowHeight;

	switch (uMsg)
	{
		case WM_CREATE:
		{
			CreateMainMenu(hWnd);
			window = new Window(hWnd);
			tool = PENCIL;
			break;
		}

		case WM_LBUTTONDOWN:
		{
			tool = CheckTool();
			if (!window->IsDrawing())
			{
				window->SetTool(tool, hWnd);
				window->SaveMousePosition(hWnd);
			}
			else
			{
				window->EndDraw(hWnd);
			}
			break;
		}

		case WM_MOUSELEAVE:
		{
			window->EndDraw(hWnd);
			break;
		}

		case WM_LBUTTONUP:
		{
			if (tool == PENCIL || tool == ERASER)
			{
				window->EndDraw(hWnd);
			}
			break;
		}

		case WM_MOUSEMOVE:
		{
			TrackMouse(hWnd);
			window->SetMousePosition(hWnd);
			if (window->IsDrawing())
			{
				hdc = GetDC(hWnd);
				window->Draw(hdc);
				ReleaseDC(hWnd, hdc);
			}
			break;
		}

		case WM_COMMAND:
		{
			MenuCommand(hWnd, wParam, tool);
			window->EndDraw(hWnd);
			break;
		}

		case WM_PAINT:
		{
			hdc = BeginPaint(hWnd, &paintStruct);
			window->Draw(hdc);
			EndPaint(hWnd, &paintStruct);
			break;
		}

		case WM_DESTROY:
		{
			window->OnClose();
			PostQuitMessage(NULL);
			break;
		}

		default:
		{
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
		}
	}
	return NULL;
}

UINT CheckTool()
{
	UINT temp = GetMenuState(toolsMenu, PENCIL, MF_BYCOMMAND);
	if (temp & MF_CHECKED)
	{
		return PENCIL;
	}

	temp = GetMenuState(toolsMenu, LINE, MF_BYCOMMAND);
	if (temp & MF_CHECKED)
	{
		return LINE;
	}

	temp = GetMenuState(toolsMenu, RECTANGLE, MF_BYCOMMAND);
	if (temp & MF_CHECKED)
	{
		return RECTANGLE;
	}

	temp = GetMenuState(toolsMenu, ELLIPSE, MF_BYCOMMAND);
	if (temp & MF_CHECKED)
	{
		return ELLIPSE;
	}

	temp = GetMenuState(toolsMenu, ERASER, MF_BYCOMMAND);
	if (temp && MF_CHECKED)
	{
		return ERASER;
	}

	return 0;
}

void TrackMouse(HWND hWnd)
{
	TRACKMOUSEEVENT tme;
	tme.cbSize = sizeof(tme);
	tme.dwFlags = TME_LEAVE;
	tme.dwHoverTime = 1;
	tme.hwndTrack = hWnd;
	TrackMouseEvent(&tme);
}

void MenuCommand(HWND hWnd, WPARAM param, int tool)
{
	switch (param)
	{
		case COLOR:
		{
			SwitchColor(hWnd, tool);
			break;
		}

		case CLEAR:
		{
			window->ClearWindow(hWnd);
			RECT rect;
			GetClientRect(hWnd, &rect);
			FillRect(GetDC(hWnd), &rect, (HBRUSH)(COLOR_WINDOW + 1));
			return;
		}

		case RECTANGLE:
		{
			SetTool(RECTANGLE, tool);
			break;
		}

		case PENCIL:
		{
			SetTool(PENCIL, tool);
			break;
		}

		case LINE:
		{
			SetTool(LINE, tool);
			break;
		}

		case ELLIPSE:
		{
			SetTool(ELLIPSE, tool);
			break;
		}

		case ERASER:
		{
			SetTool(ERASER, tool);
			break;
		}

		default:
		{
			if (param <= WIDTH_6 && param >= WIDTH_1)
			{
				SetChoosenWidth(param);
				window->SetPenWidth(param);
			}
		}
	}
}

void SetTool(int newTool, int tool)
{
	CheckMenuItem(toolsMenu, newTool, MF_CHECKED);
	CheckMenuItem(toolsMenu, tool, MF_UNCHECKED);
}

void SetChoosenWidth(int choosenWidth)
{
	static int previousWidth = WIDTH_2;
	CheckMenuItem(penWidthMenu, choosenWidth, MF_CHECKED);
	CheckMenuItem(penWidthMenu, previousWidth, MF_UNCHECKED);
	previousWidth = choosenWidth;
}

void SwitchColor(HWND hWnd, int tool)
{
	CHOOSECOLOR chooseColor;
	static COLORREF choosenColors[16];
	static DWORD rgbCurrent;

	ZeroMemory(&chooseColor, sizeof(CHOOSECOLOR));
	chooseColor.lStructSize = sizeof(CHOOSECOLOR);
	chooseColor.hwndOwner = hWnd;
	chooseColor.lpCustColors = choosenColors;
	chooseColor.rgbResult = rgbCurrent;

	chooseColor.Flags = CC_FULLOPEN | CC_RGBINIT;

	if (ChooseColor(&chooseColor) == TRUE)
	{
		rgbCurrent = chooseColor.rgbResult;
		window->SetPenColor(rgbCurrent);
	}
}