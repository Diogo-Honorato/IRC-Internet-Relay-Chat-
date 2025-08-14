#ifndef SERVER_HPP
#define SERVER_HPP

#include <winsocke2.h>
#include <pthread.h>
#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#include "../../Config/config.hpp"

#define END "/end"
#define DOMAIN AF_INET
#define MAX_CTR_SEND (MAX_CTR + 9)

typedef struct{
	
	int client_fd[MAX_USERS];
	struct sockaddr_in server;
	struct sockaddr_in client;
	int socket_fd;
	int online;
	bool run;

}Server;


#endif
