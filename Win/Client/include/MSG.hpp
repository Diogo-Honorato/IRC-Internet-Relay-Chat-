#ifndef MSG_HPP
#define MSG_HPP

#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
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
