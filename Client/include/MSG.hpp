#ifndef MSG_HPP
#define MSG_HPP

#include <iostream>
#include <cstring>
#include <vector>
#include "../../Config/config.hpp"
#include "../Config/configClient.hpp"

#ifdef __linux__

#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

#define CLOSE(socket) close(socket)
#define CLEAR_SCREEN() std::system("clear")

#elif defined(_WIN32) || defined(WIN32)

#define WIN_OS 

#include <windows.h>
#include <winsock2.h>

#define CLOSE(socket) closesocket(socket)
#define CLEAR_SCREEN() std::system("cls")

#endif



typedef struct{

	int client_fd;
	struct sockaddr_in server_target;
	int run;

}Client;

#endif
