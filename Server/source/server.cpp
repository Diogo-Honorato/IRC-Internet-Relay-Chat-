#include "../include/server.hpp"


int initServer(Server  *s){
	
	s->socket_fd = socket(DOMAIN,SOCK_STREAM,0);

	s->server.sin_port = htons(PORT_SERVER_HOST);
	s->server.sin_family = DOMAIN;
	s->server.sin_addr.s_addr = inet_addr(IP_SERVER_HOST);

	if(bind(s->socket_fd,(struct sockaddr*)&s->server,sizeof(s->server)) < 0){

		std::cerr << "ERROR::bind()::FAILURE \n";
		return -1;
	}
	
	listen(s->socket_fd, 2);
	
	for(int i =0 ; i < MAX_USERS;i++){
		s->client_fd[i] = -1;
	}

	s->online = 0;
	s->run = true;

	return 0;
}


int insertClient(int* array_fd){
	
	for(int i = 0; i < MAX_USERS;i++){
		
		if(array_fd[i] == -1){
			
			return i;
		}
	}

	return -1;
}

int removeClient(int index, int *array_fd){
	
	CLOSE(array_fd[index]);
	array_fd[index] = -1;
	
	return 0;
}

void removeAll(int *array_fd){
	
	for(int i = 0; i < MAX_USERS; i++){
	
		if(array_fd[i] != -1){
			
			CLOSE(array_fd[i]);
		}		
	}

	std::cout << "ALL CONNECTIONS CLOSED\n";
}

void* waitConnections(void *arg){
	
	int client_fd;
	int index;
	Server *s = (Server*)arg;
	socklen_t size = sizeof(s->client);
	std::string buffer = "FULL SERVER\n";

	while(s->run){
	
		client_fd = accept(s->socket_fd,(struct sockaddr*)&s->client,&size);

		index = insertClient(s->client_fd);

		if(index != -1){
			
			s->client_fd[index] = client_fd;
			s->online+=1;			
			std::cout << "NEW USER CONNECTED: " << client_fd << "\n" << s->online << " \033[32mONLINE\033[0m\n";
 
		}
		else{
			
			std::cout << "FULL SERVER\n";

			send(client_fd,buffer.c_str(),buffer.size(),MSG_NOSIGNAL);
			CLOSE(client_fd);
		}
	}

	return NULL;
}

void *relayChat(void *arg){
	
	std::vector<char> msg_send(MAX_CTR_SEND);
	std::vector<char> msg_recv(MAX_CTR);
	ssize_t msg_len;
	int temp;
	Server *s = (Server*)arg;

	while(s->run){
	
		for(int i= 0 ; i < MAX_USERS; i++){
		
			if(s->client_fd[i] != -1){
				
				msg_len = recv(s->client_fd[i],msg_recv.data(),MAX_CTR,MSG_DONTWAIT);
				
				if(msg_len > -1){
				
					snprintf(msg_send.data(),msg_len + 9,"USER %d: %s\n",s->client_fd[i],msg_recv.data());

					for(int i  = 0; i < MAX_USERS; i++){
					
						if(s->client_fd[i] != -1){
							
							if(send(s->client_fd[i],msg_send.data(),msg_len + 9,MSG_NOSIGNAL) == -1){
								
								temp = s->client_fd[i];
								
								removeClient(i,s->client_fd);
								
								s->online-=1;
								
								std::cout << "USER: " << temp << " OFFLINE\n" << s->online << " \033[32mONLINE\033[0m\n";
								
							}
						}

					}
					
					msg_send.clear();
					msg_recv.clear();
					msg_send.resize(MAX_CTR_SEND);
					msg_recv.resize(MAX_CTR);
				}
			}
		}
	}

	msg_send.clear();
	msg_recv.clear();

	removeAll(s->client_fd);
	CLOSE(s->socket_fd);
	std::cout << "SERVER OFFLINE\n";

	return (void*)0;
}


int main(){
	
	#ifdef WIN_OS
	
	WSADATA wsa;
	WSAStartup(MAKEWORD(2,0),&wsa);
	
	#endif
	
	Server server;
	std::string cmd;

	if(initServer(&server) < 0){
	
		std::cerr << "ERROR INIT SERVER\n";
		exit(EXIT_FAILURE);
	}
	
	if(CLEAR_SCREEN() != 0){
		
		std::cerr << "ERROR SYSTEM\n";
	}
	
	std::cout << "SERVER STARTED\n";
	
	#ifdef WIN_OS
	
	std::thread connection(waitConnections,&server);
	std::thread relay(relayChat,&server);
	
	#else
	
	pthread_t connection;
	pthread_t relay;
	
	pthread_create(&connection,NULL,waitConnections,&server);
	pthread_create(&relay,NULL,relayChat,&server);
	
	#endif
	
	
	while(server.run){

		std::getline(std::cin,cmd);

		if(cmd == END){
			server.run = 0;
			DETACH(connection);
			std::cout << "THE SERVER IS NOT ACCEPTING ANY MORE CONNECTIONS\n";
		}
		
		cmd.clear();
	}
	
	JOIN(relay);

	return 0;
}
