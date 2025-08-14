#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <winsock2.h>
#include <pthread.h>
#include <iostream>
#include <cstring>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include "../../Config/config.hpp"
#include "../Config/configClient.hpp"


typedef struct{

	struct sockaddr_in server_target;
	struct sockaddr_in server_local;
	struct sockaddr_in client_local;
	int client_local_fd;
	int socket_fd;
	int client_fd;
	int run;
}Client;


#endif
