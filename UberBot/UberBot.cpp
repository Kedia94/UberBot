#include <stdlib.h>
#include <string.h>
#include <string>

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