// HelloWindowsDesktop.cpp
// compile with: /D_UNICODE /DUNICODE /DWIN32 /D_WINDOWS /c

#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <string>
#include <cstdio>

#include "Main.h"
#include "resource.h"

// Global variables
std::string b = "Hello";
char a[10] = "Hello";
struct ip_header ips;

// The main window class name.
static TCHAR szWindowClass[] = _T("DesktopApp");

// The string that appears in the application's title bar.
static TCHAR szTitle[] = _T("Uber Room Finder");

HINSTANCE hInst;

// Forward declarations of functions included in this code module:
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int CALLBACK WinMain(
	_In_ HINSTANCE hInstance,
	_In_ HINSTANCE hPrevInstance,
	_In_ LPSTR     lpCmdLine,
	_In_ int       nCmdShow
)
{
	fprintf(stdout, "Hello, World!\n");
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, (LPCTSTR)IDI_ICON1);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, (LPCTSTR)IDI_ICON1);

	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL,
			_T("Call to RegisterClassEx failed!"),
			_T("Windows Desktop Guided Tour"),
			NULL);

		return 1;
	}

	//ips = get_ip();
	//b += std::to_string(ips.ip[3]);
	//fprintf(stdout, "%s\n", a);
	//OutputDebugString(std::to_string(ips.ip[3]).c_str());

	HWND h_wnd = get_diablo();
	//if (!SetForegroundWindow(h_wnd)) {
	//	OutputDebugStringA("Couldn't set application to foreground.");
	//}
	char name[10] = "testid";
	char passwd[10] = "123";
	//click_create_diablo(h_wnd);
	//type_diablo(h_wnd, name, 6, 12, passwd, 3);

	if (!check_ip(111))
		exit_diablo(h_wnd);
	
	// Store instance handle in our global variable
	hInst = hInstance;

	// The parameters to CreateWindow explained:
	// szWindowClass: the name of the application
	// szTitle: the text that appears in the title bar
	// WS_OVERLAPPEDWINDOW: the type of window to create
	// CW_USEDEFAULT, CW_USEDEFAULT: initial position (x, y)
	// 500, 100: initial size (width, length)
	// NULL: the parent of this window
	// NULL: this application does not have a menu bar
	// hInstance: the first parameter from WinMain
	// NULL: not used in this application
	HWND hWnd = CreateWindow(
		szWindowClass,
		szTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		500, 500,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	if (!hWnd)
	{
		MessageBox(NULL,
			_T("Call to CreateWindow failed!"),
			_T("Windows Desktop Guided Tour"),
			NULL);

		return 1;
	}

	// The parameters to ShowWindow explained:
	// hWnd: the value returned from CreateWindow
	// nCmdShow: the fourth parameter from WinMain
	ShowWindow(hWnd,
		nCmdShow);
	UpdateWindow(hWnd);

	// Main message loop:
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}
HWND hEditSource;
HFONT hFont;
HWND hControl;
HWND hWndNew;

//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	LPCSTR WC_EDIT = "Hi";
	int CONTROL_MARGIN = 10;
	int EDIT_WIDTH = 300;
	int CONTROL_HEIGHT = 24;
	int ID_EDIT_SRC = 10;
	int FONT_SIZE = 16;
	LPCSTR FONT_FACE = "Segoe UI";

	switch (message)
	{
	case WM_CREATE:
		hControl = CreateWindow(TEXT("button"), TEXT("Show stdout"), WS_CHILD | WS_VISIBLE | WS_BORDER, 10, 10, 200, 24, hWnd, (HMENU)ID_BUTTON_CONTROL, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
		

		break;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_BUTTON_CONTROL: break;


		}
		break;
		/*
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		// Here your application is laid out.
		// For this introduction, we just print out "Hello, Windows desktop!"
		// in the top left corner.
		TextOut(hdc,
			5, 5,
			b.c_str(), strlen(b.c_str()));
		// End application-specific layout section.

		EndPaint(hWnd, &ps);
		break;
		*/
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}

	return 0;
}