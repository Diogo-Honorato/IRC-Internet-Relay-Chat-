#ifndef MSG_HPP
#define MSG_HPP

#include <iostream>
#include <cstring>
#include <vector>
#include <string>
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
#define FLAG_NOSIGNAL MSG_NOSIGNAL
#define	FLAG_DONTWAIT MSG_DONTWAIT
#define SLEEP(time) sleep(time)

#elif defined(_WIN32) || defined(WIN32)

#define WIN_OS 

#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>

#define CLOSE(socket) closesocket(socket)
#define CLEAR_SCREEN() std::system("cls")
#define SLEEP(time) Sleep(time *1000)
#define FLAG_NOSIGNAL 0
#define	FLAG_DONTWAIT 0

typedef int socklen_t;
typedef SSIZE_T ssize_t;

#endif



typedef struct{

	int client_fd;
	struct sockaddr_in server_target;
	int run;

}Client;

#endif
