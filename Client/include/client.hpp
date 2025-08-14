#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <pthread.h>
#include <iostream>
#include <cstring>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include "../../Config/config.hpp"
#include "../Config/configClient.hpp"



#ifdef _WIN32

#include <windows.h>
#include <winsocke2.h>

#define CLOSE(socket) closesocket(socket)
#define CLEAR_SCREEN() std::system("cls")

#elif defined __unix__

#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

#define CLOSE(socket) close(socket)
#define CLEAR_SCREEN() std::system("clear")

#endif




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
