#pragma once
#include <Windows.h>
#define BUFFER_SIZE 100

#define TARGET_IP1 "121"
#define TARGET_IP2 "254"
#define TARGET_IP3 "164"
#define TARGET_PORT 4000

struct ip_header {
	int ip[4];	// ip: ip0.ip1.ip2.ip3
	int port;
};

struct threadArg {
	HWND hWnd;
	HWND hEdit;
	int ipLen;
	int *ip;
	char title[10];
	char passwd[10];
	int lobbyWait;
	int roomWait;
};

enum state {
	E_LOBBY = 0,
	E_LOBBY_WAIT,
	E_WAITING_OPEN_GAME,
	E_GAME_CONNECTED,
	E_GAME,
	E_GAME_SUCCEED,
	E_GAME_OUT,
	E_GAME_TIMEOUT,
	E_IS_BAN,
	E_BAN
};

/* get first game room info */
struct ip_header get_ip();
HWND get_diablo();
void type_diablo(HWND hwnd, char* title, int title_len, int postfix, char* passwd, int passwd_len);
bool check_ip(int ip);
void exit_diablo(HWND hwnd);
void click_create_diablo(HWND hwnd);
void AppendText(HWND hwnd, LPCTSTR szFormat, ...);
_int64 Delta(const SYSTEMTIME st1, const SYSTEMTIME st2);

DWORD WINAPI ThreadFunc(void* data);