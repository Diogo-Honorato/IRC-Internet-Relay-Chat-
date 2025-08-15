#ifndef SERVER_HPP
#define SERVER_HPP

#include <pthread.h>
#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#include "../../Config/config.hpp"

#define END "/end"
#define DOMAIN AF_INET
#define MAX_CTR_SEND (MAX_CTR + 9)

#ifdef _WIN32

#include <windows.h>
#include <winsock.h>

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
	
	int client_fd[MAX_USERS];
	struct sockaddr_in server;
	struct sockaddr_in client;
	int socket_fd;
	int online;
	bool run;

}Server;


#endif
