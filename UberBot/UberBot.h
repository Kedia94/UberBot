#pragma once
#define BUFFER_SIZE 100

#define TARGET_IP1 "121"
#define TARGET_IP2 "254"
#define TARGET_IP3 "164"
#define TARGET_PORT 4000

struct ip_header {
	int ip[4];
	int port;
};

struct ip_header get_ip();