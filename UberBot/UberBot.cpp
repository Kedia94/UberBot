#include <stdlib.h>
#include <string.h>
#include <string>
#include <Windows.h>

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