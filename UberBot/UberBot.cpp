#include <stdlib.h>
#include <string.h>
#include <string>
#include <tchar.h>
#include <Windows.h>

#include "Main.h"
#include "UberBot.h"

struct ip_header get_ip()
{
	FILE *fpipe;
	char line[BUFFER_SIZE];
	memset(line, 0, BUFFER_SIZE);
	char port[10];
	_itoa_s(TARGET_PORT, port, 10, 10);
	if (0 == (fpipe = (FILE*)_popen(("netstat -n |findstr " + std::string(port)).c_str(), "r")))
	{
		perror("popen() failed.");
		exit(1);
	}


	while (fgets(line, BUFFER_SIZE, fpipe))
	{
		char *next_ptr;
		char *ptr = strtok_s(line, " ", &next_ptr);
		char *this_ip = strtok_s(NULL, " ", &next_ptr);
		char *target = strtok_s(NULL, " ", &next_ptr);

		char *target_port;
		char *target_ip1 = strtok_s(target, ".", &target_port);
		char *target_ip2 = strtok_s(NULL, ".", &target_port);
		char *target_ip3 = strtok_s(NULL, ".", &target_port);
		char *target_ip4 = strtok_s(NULL, ":", &target_port);

		if (strcmp(target_port, port) == 0
			&& strcmp(target_ip1, TARGET_IP1) == 0
			&& strcmp(target_ip2, TARGET_IP2) == 0
			&& strcmp(target_ip3, TARGET_IP3) == 0)
		{
			_pclose(fpipe);
			struct ip_header ret;
			ret.ip[0] = atoi(target_ip1);
			ret.ip[1] = atoi(target_ip2);
			ret.ip[2] = atoi(target_ip3);
			ret.ip[3] = atoi(target_ip4);
			ret.port = atoi(target_port);

			return ret;
		}

		memset(line, 0, BUFFER_SIZE);
	}
	_pclose(fpipe);

	struct ip_header ret;
	memset(&ret, 0, sizeof(ret));
	return ret;
}

HWND get_diablo()
{
	return FindWindow(NULL, "Diablo II");
}

void type_diablo(HWND hwnd, char* title, int title_len, int postfix, char* passwd, int passwd_len)
{
	// Title
	for (int i = 0; i < title_len; i++)
	{
		if (title[i] >= 'a' && title[i] <= 'z')
			title[i] += 'A' - 'a';
		PostMessage(hwnd, WM_KEYUP, title[i], 0);
	}

	// Postfix
	char a[5];
	strcpy_s(a, std::to_string(postfix).size()+1, std::to_string(postfix).c_str());
	for (int i = 0; i < strlen(a); i++)
	{
		PostMessage(hwnd, WM_KEYUP, a[i], 0);
	}

	// TAB
	PostMessage(hwnd, WM_KEYDOWN, 0x09, 0);
	PostMessage(hwnd, WM_KEYUP, 0x09, 0);
	Sleep(50);

	// Password
	for (int i = 0; i < passwd_len; i++)
	{
		if (passwd[i] >= 'a' && passwd[i] <= 'z')
			passwd[i] += 'A' - 'a';
		PostMessage(hwnd, WM_KEYUP, passwd[i], 0);
	}

	Sleep(50);
	
	// Enter
	PostMessage(hwnd, WM_KEYDOWN, 0x0d, 0);
	PostMessage(hwnd, WM_KEYUP, 0x0d, 0);
	
	Sleep(50);
}

bool check_ip(int ip)
{
	struct ip_header getip = get_ip();
	return (ip == getip.ip[3]);
}

int MakeLParam(int LoWord, int HiWord)
{
	return (int)((HiWord << 16) | (LoWord & 0xFFFF));
}

void exit_diablo(HWND hwnd)
{
	// ESC
	PostMessage(hwnd, WM_KEYDOWN, 0x1b, 0);
	PostMessage(hwnd, WM_KEYUP, 0x1b, 0);

	Sleep(50);

	SendMessage(hwnd, WM_LBUTTONDOWN, 0x01, MakeLParam(400, 280));

	Sleep(50);

	PostMessage(hwnd, WM_LBUTTONUP, 0x01, MakeLParam(400, 280));

	Sleep(50);
}


void click_create_diablo(HWND hwnd)
{
	RECT rect = { 0 };
	GetWindowRect(hwnd, &rect);

	//SetForegroundWindow(hwnd);
	//SetActiveWindow(hwnd);
	//SetFocus(hwnd);
	//Sleep(300);

	SendMessage(hwnd, WM_LBUTTONDOWN, 0x01, MakeLParam(590, 465));

	Sleep(50);

	PostMessage(hwnd, WM_LBUTTONUP, 0x01, MakeLParam(590, 465));

	Sleep(50);
}

void AppendText(HWND hwnd, LPCTSTR szFormat, ...)
{
	TCHAR szText[4096];
	va_list args;
	int nTxtLen;

	/* Move selection to end of text */
	nTxtLen = GetWindowTextLength(hwnd);
	SendMessage(hwnd, EM_SETSEL, nTxtLen, nTxtLen);

	/* Format the text into the buffer */
	va_start(args, szFormat);
	_vsntprintf_s(szText, sizeof(szText) / sizeof(szText[0]), szFormat, args);
	szText[(sizeof(szText) / sizeof(szText[0])) - 1] = TEXT('\0');
	va_end(args);

	/* Add the text line and scroll it into view */
	SendMessage(hwnd, EM_REPLACESEL, FALSE, (LPARAM)szText);
	SendMessage(hwnd, EM_SCROLLCARET, 0, 0);
}

_int64 Delta(const SYSTEMTIME st1, const SYSTEMTIME st2) {
	union timeunion {
		FILETIME fileTime;
		ULARGE_INTEGER ul;
	};

	timeunion ft1;
	timeunion ft2;

	SystemTimeToFileTime(&st1, &ft1.fileTime);
	SystemTimeToFileTime(&st2, &ft2.fileTime);

	return ft2.ul.QuadPart - ft1.ul.QuadPart;
}

DWORD WINAPI ThreadFunc(void* data) {
	struct threadArg *arg = (struct threadArg *)data;
	AppendText(arg->hEdit, "Starting ...");
	//ips = get_ip();
	//b += std::to_string(ips.ip[3]);
	//fprintf(stdout, "%s\n", a);
	//OutputDebugString(std::to_string(ips.ip[3]).c_str());

	HWND hDia = get_diablo();
	if (!hDia)
	{
		AppendText(arg->hEdit, "\r\nCould not find Diablo II");
		ExitThread(0);
	}
	//if (!SetForegroundWindow(h_wnd)) {
	//	OutputDebugStringA("Couldn't set application to foreground.");
	//_RPT1(0, "%d\n", 1);
	//}
	//click_create_diablo(h_wnd);
	//type_diablo(h_wnd, name, 6, 12, passwd, 3);

	//if (!check_ip(111))
	//	exit_diablo(h_wnd);

	/* Find Room Loop */
	int postfix = 0;		// Postfix of game name
	int state = E_LOBBY;	// Initial State
	SYSTEMTIME prev, now;

	_int64 timeInterval = 1000; // Millis

	int seconds = 0;
	GetSystemTime(&prev);

	bool Exit = true;
	AppendText(arg->hEdit, "\r\n==========================");
	
	while (Exit) {
		Sleep(100);
		GetSystemTime(&now);
		if (Delta(prev, now) < timeInterval * 10000)
		{
			continue;
		}
		seconds++;

		switch (state)
		{
		case E_LOBBY_WAIT:
			// Wait in the Lobby
			if (seconds < arg->lobbyWait)
				break;

			seconds = 0;
			state = E_LOBBY;

			break;
		case E_LOBBY:
			// State: Game Lobby
			postfix++;

			// Make Game
			click_create_diablo(hDia);
			type_diablo(hDia, arg->title, strlen(arg->title), postfix, arg->passwd, strlen(arg->passwd));

			state = E_WAITING_OPEN_GAME;
			break;
		case E_WAITING_OPEN_GAME:
			// State: Wait creating game
			// TODO: Check Game Connected

			break;
		case E_GAME_CONNECTED:
			// State: Door is opening
			// TODO: Check is Timeout
			break;
		case E_GAME:
			// State: In the Game Room
			state = E_GAME_OUT;
			break;
		case E_GAME_SUCCEED:
			// State: Found Uber Room
			Exit = false;
			AppendText(arg->hEdit, "\r\n==========================");
			AppendText(arg->hEdit, "\r\nSUCCEED. Good Luck!");
			continue;
			break;
		case E_GAME_OUT:
			// State: Quit Game
			if (seconds < arg->roomWait)
				break;
			// TODO: Check IP
			// TODO: Quit Game
			exit_diablo(hDia);
			state = E_LOBBY_WAIT;
			seconds = 0;
			break;
		case E_GAME_TIMEOUT:
			// State: Door didn't open
			break;
		case E_IS_BAN:
			// State: Might be 3600...
			break;
		case E_BAN:
			// State: Yes, it is 3600
			Exit = false;
			AppendText(arg->hEdit, "\r\n==========================");
			AppendText(arg->hEdit, "\r\nFAILED");
			continue;
			break;
		}


		GetSystemTime(&prev);
	}

	SendMessage(arg->hWnd, WM_COMMAND, ID_LOG_END, 0);
	ExitThread(0);

	// Do stuff.  This will be the first function called on the new thread.
	// When this function returns, the thread goes away.  See MSDN for more details.
	return 0;
}