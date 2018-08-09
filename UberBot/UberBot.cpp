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

DWORD WINAPI ThreadFunc(void* data) {
	_RPT1(0, "THREAD] RUN", 0);
	struct threadArg *arg = (struct threadArg *)data;
	//ips = get_ip();
	//b += std::to_string(ips.ip[3]);
	//fprintf(stdout, "%s\n", a);
	//OutputDebugString(std::to_string(ips.ip[3]).c_str());

	HWND h_wnd = get_diablo();
	//if (!SetForegroundWindow(h_wnd)) {
	//	OutputDebugStringA("Couldn't set application to foreground.");
	//_RPT1(0, "%d\n", 1);
	//}
	char name[10] = "testid";
	char passwd[10] = "123";
	//click_create_diablo(h_wnd);
	//type_diablo(h_wnd, name, 6, 12, passwd, 3);

	//if (!check_ip(111))
	//	exit_diablo(h_wnd);
	int i = 0;
	AppendText(arg->hEdit, "Name: %s\r\n", arg->title);
	AppendText(arg->hEdit, "Passwd: %s\r\n", arg->passwd);
	for (int j = 0; j < arg->ipLen; j++)
	{
		AppendText(arg->hEdit, "ip[%d]: %d\r\n", j, arg->ip[j]);
	}
	AppendText(arg->hEdit, "RoomWait: %d\r\n", arg->roomWait);
	AppendText(arg->hEdit, "LobbyWait: %d\r\n", arg->lobbyWait);
	AppendText(arg->hEdit, "Thread: %d\r\n", i);
	while (1) {
		i++;
		Sleep(1000);
		AppendText(arg->hEdit, "this is %d\r\n", i);
		if (i == 10)
			break;

	}

	AppendText(arg->hEdit, "FINISHED", 0);
	SendMessage(arg->hWnd, WM_COMMAND, ID_LOG_END, 0);
	ExitThread(0);

	// Do stuff.  This will be the first function called on the new thread.
	// When this function returns, the thread goes away.  See MSDN for more details.
	return 0;
}