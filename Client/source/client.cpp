#include "../include/client.hpp"

int initMSG(){

	std::string cmd = "gnome-terminal -- $SHELL -c 'bin/./MSG'";

	if(std::system(cmd.c_str()) == 0){
	
		std::cout << "START MSG\n";
	}else{
		std::cout << "ERROR TO STARTED MSG\n";
		return -1;
	}
	
	return 0;
}

int initClient(Client *c){

	socklen_t size = sizeof(c->server_target);

	c->client_fd = socket(DOMAIN,SOCK_STREAM,0);

	c->server_target.sin_family = DOMAIN;
	c->server_target.sin_port = htons(PORT_SERVER_HOST);
	c->server_target.sin_addr.s_addr = inet_addr(IP_SERVER_HOST);

	int status = connect(c->client_fd,(struct sockaddr*)&c->server_target,size);

	if(status != 0){
		
		CLOSE(c->client_fd);
		return -1;
	}

	return 0;
}

int initServerLocal(Client  *s){

	socklen_t size = sizeof(s->client_local);
	
	s->socket_fd = socket(DOMAIN,SOCK_STREAM,0);

	s->server_local.sin_port = htons(PORT_SERVER_LOCAL);
	s->server_local.sin_family = DOMAIN;
	s->server_local.sin_addr.s_addr = inet_addr(IP_SERVER_LOCAL);

	if(bind(s->socket_fd,(struct sockaddr*)&s->server_local,sizeof(s->server_local)) < 0){
		
		CLOSE(s->socket_fd);
		std::cerr << "ERROR::bind()::FAILURE \n";
		return -1;
	}

	listen(s->socket_fd, 1);
	
	if(initMSG() == -1){
		
		return -1;
	}
	
	s->client_local_fd = accept(s->socket_fd,(struct sockaddr*)&s->client_local,&size);
	
	return 0;
}

int cmds(std::vector<char> cmd, Client *cli){

	if(strcmp(cmd.data(), END)==0){
		cli->run = 0;
		return 0;
	}
	else if(strcmp(cmd.data(),REC)==0){
	
		CLOSE(cli->client_fd);
		
		for(int i = 1; i < 6; i++){
			
			if(CLEAR_SCREEN() != 0){
			
				std::cerr << "ERROR SYSTEM\n";
			}
			
			std::cout<< "TRYING TO RECONNECT TO HOST SERVER... " << i <<" SEC\n";
			
			if(initClient(cli) == 0){
				
				if(CLEAR_SCREEN() != 0){
					std::cerr << "ERROR SYSTEM\n";
				}
				
				std::cout << "CONNECTED TO HOST SERVER\n\nMESSAGE SCREEN:\n-----------------------------------------------------------------\n";
				return 0;
			}
			
			sleep(1);
		}
		
		std::cout << "SERVER OFFLINE TRY: " << REC << "\n";
		
		return -1;
	}

	return -1;
}


void *sendMSG(void* arg){
	
	Client* cli = (Client*)arg;
	ssize_t msg_len;
	std::vector<char> buffer(MAX_CTR);
		
	while(cli->run){
	
		msg_len = recv(cli->client_local_fd,buffer.data(),MAX_CTR,MSG_DONTWAIT);
		
		if(msg_len > 0){
	
			if(buffer[0] == '/'){
			
				cmds(buffer,cli);
			}
			else{
			
				if(send(cli->client_fd,buffer.data(),msg_len,MSG_NOSIGNAL) == -1){
						
					std::cout << "SERVER OFFLINE TRY: " << REC << "\n";
				}
			}

			buffer.clear();
			buffer.resize(MAX_CTR);
		}
	}

	return NULL;
}

void *recvMSG(void *arg){
	
	ssize_t msg_size;
	Client* cli = (Client*)arg;
	std::vector<char> buffer(MAX_CTR);
	
	while(cli->run){
		
		msg_size = recv(cli->client_fd,buffer.data(),MAX_CTR,MSG_DONTWAIT);

		if(msg_size > 0){
			for(int i =0; i < msg_size; i++){
				std::cout << buffer[i];
			}
			buffer.clear();
			buffer.resize(MAX_CTR);
		}
	}

	return NULL;
}


int main(){
	
	#ifdef _WIN32
	
	WSADATA wsa;
	WSAStartup(MAKEWORD(2,0),&wsa);
	
	#endif
	
	
	Client c;
	pthread_t send_th;
	pthread_t recv_th;
	
	if(CLEAR_SCREEN() != 0){
		std::cerr << "ERROR SYSTEM\n";
	}
	
	if(initServerLocal(&c) < 0){
	
		CLOSE(c.client_local_fd);
		CLOSE(c.socket_fd);
		CLOSE(c.client_fd);
		
		std::cerr << "LOCAL SERVER FAILED TO START\n";
		exit(EXIT_FAILURE);
	}
	
	std::cout << "LOCAL SERVER STARTED\n";

	if(initClient(&c) < 0){
	
		CLOSE(c.client_local_fd);
		CLOSE(c.socket_fd);
		CLOSE(c.client_fd);
		
		std::cout << "FALEID TO CONNECT HOST SERVER\n";
		exit(EXIT_FAILURE);
	}
	
	//start all processes
	c.run =1;
	
	std::cout << "CONNECTED TO HOST SERVER\n\nMESSAGE SCREEN:\n-----------------------------------------------------------------\n";

	pthread_create(&send_th,NULL,sendMSG,&c);
	pthread_create(&recv_th,NULL,recvMSG,&c);

	pthread_join(send_th,NULL);
	pthread_join(recv_th,NULL);

	CLOSE(c.client_local_fd);
	CLOSE(c.socket_fd);
	CLOSE(c.client_fd);

	std::cout << "RELAY CHAT CLOSED\n";

	return 0;
}
