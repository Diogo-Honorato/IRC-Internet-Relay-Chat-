#ifndef MSG_HPP
#define MSG_HPP

#include <winsock2.h>
#include <iostream>
#include <cstring>
#include <vector>
#include <limits>
#include "../../Config/config.hpp"
#include "../Config/configClient.hpp"


typedef struct{

	int client_fd;
	struct sockaddr_in server_target;
	int run;

}Client;

#endif
