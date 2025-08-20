#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#include "../../Config/config.hpp"

#define END "/end"
#define DOMAIN AF_INET


#ifdef __linux__

#include <pthread.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

#define CLOSE(socket) close(socket)
#define CLEAR_SCREEN() std::system("clear")
#define DETACH(x) pthread_detach(x);
#define JOIN(x) pthread_join(x,NULL)
#define	FLAG_DONTWAIT MSG_DONTWAIT
#define FLAG_NOSIGNAL MSG_NOSIGNAL

#elif defined(_WIN32) || defined(WIN32)

#define WIN_OS

#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <thread>

#define CLOSE(socket) closesocket(socket)
#define CLEAR_SCREEN() std::system("cls")
#define DETACH(x) x.detach()
#define JOIN(x) x.join()
#define	FLAG_DONTWAIT 0
#define FLAG_NOSIGNAL 0

typedef int socklen_t;
typedef SSIZE_T ssize_t;

#endif


typedef struct{
	
	int client_fd[MAX_USERS];
	struct sockaddr_in server;
	struct sockaddr_in client;
	int socket_fd;
	int online;
	bool run;

}Server;


#endif
