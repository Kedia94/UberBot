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

/* get first game room info */
struct ip_header get_ip();
HWND get_diablo();
void type_diablo(HWND hwnd, char* title, int title_len, int postfix, char* passwd, int passwd_len);
bool check_ip(int ip);
void exit_diablo(HWND hwnd);