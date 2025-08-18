#ifndef CLIENT_HPP
#define CLIENT_HPP


#include <iostream>
#include <cstring>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include "../../Config/config.hpp"
#include "../Config/configClient.hpp"




#ifdef __linux__

#include <pthread.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

#define CLOSE(socket) close(socket)
#define CLEAR_SCREEN() std::system("clear")
#define JOIN(x) pthread_join(x,NULL)
#define FLAG_NOSIGNAL MSG_NOSIGNAL
#define	FLAG_DONTWAIT MSG_DONTWAIT
#define START_TERMINAL "gnome-terminal -- $SHELL -c 'bin/./MSG'"
#define SLEEP(time) sleep(time)

#elif defined(_WIN32) || defined(WIN32)


#define WIN_OS

#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <thread>

#define CLOSE(socket) closesocket(socket)
#define CLEAR_SCREEN() std::system("cls")
#define JOIN(x) x.join()
#define FLAG_NOSIGNAL 0
#define	FLAG_DONTWAIT 0
#define START_TERMINAL "start powershell -NoExit -Command bin\\MSG.exe"
#define SLEEP(time) Sleep(time*1000)

typedef int socklen_t;
typedef SSIZE_T ssize_t;

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
