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
static TCHAR szWindowClass[] = _T("UberApp");

// The string that appears in the application's title bar.
static TCHAR szTitle[] = _T("Uber Room Finder");

HINSTANCE hInst;
HWND hRoot;

// Forward declarations of functions included in this code module:
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int CALLBACK WinMain(
	_In_ HINSTANCE hInstance,
	_In_ HINSTANCE hPrevInstance,
	_In_ LPSTR     lpCmdLine,
	_In_ int       nCmdShow
)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, (LPCTSTR)IDI_ICON1);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, (LPCTSTR)IDI_ICON1);

	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL,
			_T("Call to RegisterClassEx failed!"),
			_T("Uber Room Finder"),
			NULL);

		return 1;
	}

	wcex.lpfnWndProc = (WNDPROC)WndProcPopup;
	wcex.lpszClassName = "ProcessLog";
	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL,
			_T("Call to RegisterClassEx failed!"),
			_T("MyPopUp"),
			NULL);

		return 1;
	}

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

	/* Get Desktop Resolution */
	int x = GetSystemMetrics(SM_CXSCREEN);
	int y = GetSystemMetrics(SM_CYSCREEN);

	x = x ? (x - 285) / 2 : CW_USEDEFAULT;
	y = y ? (y - 260) / 2 : CW_USEDEFAULT;

	HWND hWnd = CreateWindow(
		szWindowClass,
		szTitle,
		WS_OVERLAPPEDWINDOW,
		x, y,
		285, 260,
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
	hRoot = hWnd;

	// The parameters to ShowWindow explained:
	// hWnd: the value returned from CreateWindow
	// nCmdShow: the fourth parameter from WinMain
	ShowWindow(hWnd,
		nCmdShow);
	UpdateWindow(hWnd);

	// Main message loop:
	MSG msg;
	/* Run the message loop. It will run until GetMessage() returns 0 */
	while (GetMessage(&msg, NULL, 0, 0))
	{
		/* Translate virtual-key messages into character messages */
		if (IsDialogMessage(hWnd, &msg) == 0)
		{
			TranslateMessage(&msg);
			/* Send message to WindowProcedure */
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}

HWND hIPGroup;
HWND hIPList;
HWND hIP;
HWND hIPAdd;
HWND hIPDel;

HWND hSettingGroup;
HWND hGameGroup;
HWND hGameNameText;
HWND hGameName;
HWND hGamePasswdText;
HWND hGamePasswd;
HWND hWaitGroup;
HWND hWaitLobbyText;
HWND hWaitLobby;
HWND hWaitGameText;
HWND hWaitGame;

HWND hStartStop;
HWND hRunPopup;
HWND hExit;
HWND hAbout;


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

	switch (message)
	{
	case WM_CREATE:
		hIPGroup = CreateWindow(TEXT("button"), TEXT("IP List"), WS_CHILD | WS_VISIBLE | BS_GROUPBOX, LEFT_MARGIN, TOP_MARGIN, 70, 172, hWnd, (HMENU)0, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
		hIPList = CreateWindow(TEXT("listbox"), NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | LBS_MULTIPLESEL | LBS_SORT | WS_VSCROLL, 2 * LEFT_MARGIN, 30, 50, 100, hWnd, (HMENU)ID_IP_LIST, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
		{
			SendMessage(hIPList, LB_ADDSTRING, 0, (LPARAM)"123");
			SendMessage(hIPList, LB_ADDSTRING, 0, (LPARAM)"124");
			SendMessage(hIPList, LB_ADDSTRING, 0, (LPARAM)"100");
			SendMessage(hIPList, LB_ADDSTRING, 0, (LPARAM)"182");
			SendMessage(hIPList, LB_ADDSTRING, 0, (LPARAM)"165");
			SendMessage(hIPList, LB_ADDSTRING, 0, (LPARAM)"172");
		}
		hIP = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | ES_CENTER | ES_NUMBER, 2 * LEFT_MARGIN, 130, 50, 16, hWnd, (HMENU)ID_IP_LIST, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
		SendMessage(hIP, EM_LIMITTEXT, (WPARAM)3, 0);
		hIPAdd = CreateWindow(TEXT("button"), TEXT("+"), WS_CHILD | WS_TABSTOP | WS_VISIBLE | WS_BORDER, 2 * LEFT_MARGIN, TOP_MARGIN + 142, 20, 20, hWnd, (HMENU)ID_BUTTON_ADD_IP, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
		hIPDel = CreateWindow(TEXT("button"), TEXT("-"), WS_CHILD | WS_TABSTOP | WS_VISIBLE | WS_BORDER, 3 * LEFT_MARGIN + 20, TOP_MARGIN + 142, 20, 20, hWnd, (HMENU)ID_BUTTON_REMOVE_IP, ((LPCREATESTRUCT)lParam)->hInstance, NULL);

		hSettingGroup = CreateWindow(TEXT("button"), TEXT("Settings"), WS_CHILD | WS_VISIBLE | BS_GROUPBOX, LEFT_MARGIN + 80, TOP_MARGIN, 170, 172, hWnd, (HMENU)0, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
		hGameGroup = CreateWindow(TEXT("button"), TEXT("Game Info"), WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 2 * LEFT_MARGIN + 80, 30, 150, 66, hWnd, (HMENU)0, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
		hGameNameText = CreateWindow(TEXT("static"), TEXT("Title:"), WS_CHILD | WS_VISIBLE, 3 * LEFT_MARGIN + 80, 50, 70, 16, hWnd, (HMENU)0, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
		hGameName = CreateWindow(TEXT("edit"), TEXT("test"), WS_CHILD | WS_TABSTOP | WS_VISIBLE, 4 * LEFT_MARGIN + 150, 50, 50, 16, hWnd, (HMENU)0, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
		hGamePasswdText = CreateWindow(TEXT("static"), TEXT("Password:"), WS_CHILD | WS_VISIBLE, 3 * LEFT_MARGIN + 80, 70, 70, 16, hWnd, (HMENU)0, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
		hGamePasswd = CreateWindow(TEXT("edit"), TEXT("12345"), WS_CHILD | WS_TABSTOP | WS_VISIBLE, 4 * LEFT_MARGIN + 150, 70, 50, 16, hWnd, (HMENU)0, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
		hWaitGroup = CreateWindow(TEXT("button"), TEXT("Waiting Info"), WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 2 * LEFT_MARGIN + 80, 106, 150, 66, hWnd, (HMENU)0, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
		hWaitLobbyText = CreateWindow(TEXT("static"), TEXT("Lobby (s):"), WS_CHILD | WS_VISIBLE, 3 * LEFT_MARGIN + 80, 126, 70, 16, hWnd, (HMENU)0, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
		hWaitLobby = CreateWindow(TEXT("edit"), TEXT("15"), WS_CHILD | WS_TABSTOP | WS_VISIBLE | ES_NUMBER, 4 * LEFT_MARGIN + 150, 126, 50, 16, hWnd, (HMENU)0, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
		hWaitGameText = CreateWindow(TEXT("static"), TEXT("Room (s):"), WS_CHILD | WS_VISIBLE, 3 * LEFT_MARGIN + 80, 146, 70, 16, hWnd, (HMENU)0, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
		hWaitGame = CreateWindow(TEXT("edit"), TEXT("120"), WS_CHILD | WS_TABSTOP | WS_VISIBLE | ES_NUMBER, 4 * LEFT_MARGIN + 150, 146, 50, 16, hWnd, (HMENU)0, ((LPCREATESTRUCT)lParam)->hInstance, NULL);

		hStartStop = CreateWindow(TEXT("button"), TEXT("Start"), WS_CHILD | WS_TABSTOP | WS_VISIBLE | WS_BORDER, LEFT_MARGIN, 190, BUTTON_W, BUTTON_H, hWnd, (HMENU)ID_BUTTON_STARTSTOP, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
		hExit = CreateWindow(TEXT("button"), TEXT("Exit"), WS_CHILD | WS_TABSTOP | WS_VISIBLE | WS_BORDER, 6 + 2 * LEFT_MARGIN + BUTTON_W, 190, BUTTON_W, BUTTON_H, hWnd, (HMENU)ID_BUTTON_EXIT, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
		hAbout = CreateWindow(TEXT("button"), TEXT("About"), WS_CHILD | WS_TABSTOP | WS_VISIBLE | WS_BORDER, 13 + 3 * LEFT_MARGIN + 2 * BUTTON_W, 190, BUTTON_W, BUTTON_H, hWnd, (HMENU)ID_BUTTON_ABOUT, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
		
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_BUTTON_STARTSTOP:
		{
			if (get_diablo())
				MessageBox(hWnd, "No Diablo II Detected", "ERROR", MB_OK | MB_ICONERROR);
			else
			{
				HWND hTemp = FindWindow(szWindowClass, szTitle);
				if (!hTemp) {
					MessageBox(hWnd, "No Parent Window", "ERROR", MB_OK | MB_ICONERROR);
					return 0;
				}

				RECT rect = { 0 };
				GetWindowRect(hTemp, &rect);

				hRunPopup = CreateWindow(
					"processlog",
					"Processing Log",
					WS_OVERLAPPEDWINDOW,
					rect.right, rect.top,
					285, 260,
					hWnd,
					(HMENU)0,
					hInst,
					NULL
				);
				ShowWindow(hRunPopup, SW_SHOW);
				EnableWindow(hWnd, FALSE);
				SendMessage(hRunPopup, WM_COMMAND, ID_LOG_START, 0);
			}

			break;
		}
		case ID_BUTTON_EXIT:
			PostQuitMessage(0);
			break;
		case ID_BUTTON_ABOUT:
			MessageBox(hWnd, "Uber Room Finder v0.1\nMade By πŸ∫∏∏€√ª¿Ã\nSpecial Thanks to HO", "About", MB_OK | MB_ICONINFORMATION);
			break;
		case ID_BUTTON_ADD_IP:
			char line[5];
			char tempLine[5];
			int k;
			k = SendMessage(hIP, EM_GETLINE, 0, (LPARAM)line);
			line[k] = 0;
			k = atoi(line);
			if (k < 100 || k > 199)
				MessageBox(hWnd, "Put integer 100~199", "ERROR", MB_OK | MB_ICONERROR);
			else
			{
				for (int i = 0; i < SendMessage(hIPList, LB_GETCOUNT, 0, 0); i++)
				{
					int tempK = SendMessage(hIPList, LB_GETTEXT, i, (LPARAM)tempLine);
					tempLine[tempK] = 0;
					if (strcmp(line, tempLine) == 0)
						return 0;
				}
				SendMessage(hIPList, LB_ADDSTRING, 0, (LPARAM)line);
			}
			break;
		case ID_BUTTON_REMOVE_IP:
			for (int i = 0; i < SendMessage(hIPList, LB_GETCOUNT, 0, 0); i++)
			{
				if (SendMessage(hIPList, LB_GETSEL, i, 0))
				{
					SendMessage(hIPList, LB_DELETESTRING, i, 0);
					i--;
				}
			}
			break;
		}
		break;
		
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		/*
		// Here your application is laid out.
		// For this introduction, we just print out "Hello, Windows desktop!"
		// in the top left corner.
		TextOut(hdc,
			5, 5,
			b.c_str(), strlen(b.c_str()));
		// End application-specific layout section.
		*/
		EndPaint(hWnd, &ps);
		break;
		
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}

	return 0;
}

HANDLE thread;
HWND PopupEdit;
struct threadArg * arg;

LRESULT CALLBACK WndProcPopup(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	switch (iMessage) {
	case WM_CREATE:
	{
		CreateWindow(TEXT("button"), TEXT("Log"), WS_CHILD | WS_VISIBLE | BS_GROUPBOX, LEFT_MARGIN, TOP_MARGIN, 250, 170, hWnd, (HMENU)0, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
		PopupEdit = CreateWindow(TEXT("edit"), TEXT(""), WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_MULTILINE | ES_READONLY, 2 * LEFT_MARGIN, 3 * TOP_MARGIN, 230, 140, hWnd, (HMENU)0, ((LPCREATESTRUCT)lParam)->hInstance, NULL);

		HWND hExit = CreateWindow(TEXT("button"), TEXT("Exit"), WS_CHILD | WS_TABSTOP | WS_VISIBLE | WS_BORDER, 6 + 2 * LEFT_MARGIN + BUTTON_W, 190, BUTTON_W, BUTTON_H, hWnd, (HMENU)ID_BUTTON_EXIT, ((LPCREATESTRUCT)lParam)->hInstance, NULL);

		thread = NULL;
		arg = NULL;
		break;
	}
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_LOG_START:
		{
			char line[5];
			int k;

			arg = (struct threadArg*)malloc(sizeof(struct threadArg));
			arg->hWnd = hRunPopup;
			arg->hEdit = PopupEdit;

			/* IP */
			arg->ipLen = SendMessage(hIPList, LB_GETCOUNT, 0, 0);
			arg->ip = (int *)malloc(arg->ipLen * sizeof(int));
			for (int i = 0; i < arg->ipLen; i++)
			{
				k = SendMessage(hIPList, EM_GETLINE, (WPARAM)i, (LPARAM)line);
				line[k] = 0;
				arg->ip[i] = atoi(line);
			}
			/* Lobby Wait */
			k = SendMessage(hWaitLobby, EM_GETLINE, 0, (LPARAM)line);
			line[k] = 0;
			arg->lobbyWait = atoi(line);

			/* Room Wait */
			k = SendMessage(hWaitGame, EM_GETLINE, 0, (LPARAM)line);
			line[k] = 0;
			arg->roomWait = atoi(line);
			
			/* Title */
			memset(arg->title, 0, 10);
			k = SendMessage(hGameName, EM_GETLINE, 0, (LPARAM)line);
			strncpy_s(arg->title, line, k);

			/* Passwd */
			memset(arg->passwd, 0, 10);
			k = SendMessage(hGamePasswd, EM_GETLINE, 0, (LPARAM)line);
			strncpy_s(arg->passwd, line, k);

			thread = CreateThread(NULL, 0, ThreadFunc, arg, 0, NULL);
			break;
		}
		case ID_BUTTON_EXIT:
			DestroyWindow(hWnd);
			break;
		case ID_LOG_END:
			break;
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		hRunPopup = NULL;
		if (thread)
		{
			TerminateThread(thread, 0);
			thread = NULL;
		}
		if (arg)
		{
			free(arg->ip);
			free(arg);
			arg = NULL;
		}
		EnableWindow(hRoot, TRUE);
		break;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}